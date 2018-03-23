// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "thread.h"

void yield(); //This the yield function called by the exception handler which
void fork();               //calls a thread yield
void exxit(); 
void exec(); 
void kill(); 

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if ((which == SyscallException) && (type == SC_Halt)) {
	     DEBUG('a', "Shutdown, initiated by user program.\n");
   	   interrupt->Halt();
    }

    else if ((which == SyscallException) && (type == SC_Yield)) {
      DEBUG('a', "Yield, initiated by user program.\n");
      yield();
      machine->WriteRegister(PCReg, 4); //we must update the registers or we
    }                                   //will end up in an endless loop 

    else if ((which == SyscallException) && (type == SC_Fork)) {
      DEBUG('a', "Fork, initiated by user program.\n");
      fork();
      machine->WriteRegister(PCReg, 4); 
    }    

    else if ((which == SyscallException) && (type == SC_Exit)) {
      DEBUG('a', "Exit, initiated by user program.\n");
      exxit();
      machine->WriteRegister(PCReg, 4); 
    }                                   
                               
    else if ((which == SyscallException) && (type == SC_Exec)) {
      DEBUG('a', "Exec, initiated by user program.\n");
      exec(); 
      machine->WriteRegister(PCReg, 4); 
    }    

    else if ((which == SyscallException) && (type == SC_Kill)) {
      DEBUG('a', "Kill, initiated by user program.\n");
      kill(); 
      machine->WriteRegister(PCReg, 4); 
    }    

    else if ((which == SyscallException) && (type == SC_Join)) {
      DEBUG('a', "Join, initiated by user program.\n");
      join(); 
      machine->WriteRegister(PCReg, 4); 
    }    



    else {
      printf("Unexpected user mode exception %d %d\n", which, type);
      ASSERT(FALSE);
    }

}


void yield(){
  currentThread->Yield();
  printf("the current process yielded\n");
}

void fork(){
  printf("right now fork does nothing\n");
}

void exxit(){
  printf("right now exxit does nothing\n");
}

void exec(){
  printf("right now exec does nothing\n");
}

void kill(){
  printf("right now kill does nothing\n");
}

void join(){
  printf("right now join does nothing\n");
}
