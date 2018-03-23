#include "syscall.h"

void fork();

main()
{
    Exec("foo");
    Exit(9);
    Join(3);
    Fork(fork);
    Yield();
    Halt();
}

void fork(){

}
