#include <stdint.h>
#include "interrupts.h"
#include "syscall.h"
#include "tty.h"

void test_syscall()
{
    terminal_printc("Test syscall called\n");
}

void syscall_handler(Stack *registers)
{
    int sys_index = registers->eax;

    if (sys_index != 0)
    {
        return;
    }

    test_syscall();
}

void syscall_init(void)
{
    isr_install_handler(128, syscall_handler);
}