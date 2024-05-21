#include <stdint.h>

#include "interrupts.h"
#include "keyboard.h"
#include "sys.h"
#include "syscall.h"
#include "tty.h"

#define NB_SYSCALL 8

void *syscalls[NB_SYSCALL] = {
    terminal_writestring,
    keyboard_getchar,
    terminal_printc,
    terminal_clear,
    terminal_putchar,
    terminal_putentryat,
    keyboard_clear_buffer,

    sys_halt};

void syscall_handler(Stack *registers)
{
    terminal_writestring("Syscall\n");

    int sys_index = registers->eax;

    if (sys_index >= NB_SYSCALL)
        return;

    void *function = syscalls[sys_index];

    int ret;
    asm volatile("   push %1;   \
                     push %2;   \
                     push %3;   \
                     push %4;   \
                     push %5;   \
                     call *%6;  \
                     pop %%ebx; \
                     pop %%ebx; \
                     pop %%ebx; \
                     pop %%ebx; \
                     pop %%ebx; \
                     " : "=a"(ret) : "r"(registers->edi), "r"(registers->esi),
                                     "r"(registers->edx), "r"(registers->ecx),
                                     "r"(registers->ebx), "r"(function));
    registers->eax = ret;
}

void syscall_init(void)
{
    isr_install_handler(128, syscall_handler);
}