#include <stdint.h>

#include "interrupts.h"
#include "keyboard.h"
#include "sys.h"
#include "syscall.h"
#include "tty.h"
#include "timer.h"
#include "rtc.h"

#define NB_SYSCALL 3

void *syscalls[NB_SYSCALL] = {
    keyboard_getchar,
    get_rtc_time,

    sys_halt};

void syscall_handler(Stack *registers)
{
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