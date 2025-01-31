#include <stdint.h>

#include "interrupts.h"
#include "keyboard.h"
#include "sys.h"
#include "syscall.h"
#include "tty.h"
#include "timer.h"
#include "rtc.h"
#include "shell.h"
#define NB_SYSCALL 7

void *syscalls[NB_SYSCALL] = {
    keyboard_getchar,
    get_rtc_time,
    sys_halt,
    terminal_printf,
    delay,
    terminal_clear,
    shell_init
    };

void syscall_handler(Stack *registers)
{
    if ((registers->cs & 0x3) != 0x3) return;
    
    int sys_index = registers->eax;
    if (sys_index >= NB_SYSCALL) return;

    void *function = syscalls[sys_index];

   int ret;
   asm volatile("sti");
   asm volatile ("   push %1;   \
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
                     " : "=a" (ret) : 
                     "r" (registers->edi), "r" (registers->esi),
                     "r" (registers->edx), "r" (registers->ecx), 
                     "r" (registers->ebx), "r" (function));

    asm volatile("cli");

   registers->eax = ret;
}

void syscall_init(void)
{
    isr_install_handler(128, syscall_handler);
}