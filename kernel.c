#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "sys.h"
#include "interrupts.h"
#include "keyboard.h"
#include "shell.h"
#include "user_space.h"
#include "syscall.h"
#include "rtc.h"

void kernel_main(void)
{
    terminal_printf("Kernel start\n");
    terminal_initialize();
    gdt_install();

    idt_install();
    isr_install();
    irq_install();

    timer_install();
    keyboard_install();

    rtc_init();

    terminal_printf("Kernel initialized\n");
    
    syscall_init();
    terminal_printf("Syscall initialized\n");
    
    sys_enable_interrupts();
    terminal_printf("Interrupts enabled\n");

    enter_user_space();
}

enum SYSCALLS {
    SYS_GETCHAR = 0,
    SYS_GET_TIME,
    SYS_HALT,
    SYS_PRINTF,
    SYS_DELAY,
    SYS_CLEAR,
    SYS_SHELL_INIT
};

void main(void)
{ //TODO: Rework user space calls
    int ret;
    for (int i = 1; i < 4; i++)
    {
        asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_PRINTF), "b"("&cTest &7%d\n"), "c"(i));
        
        asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_DELAY), "b"(1000));
    }

    asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_CLEAR));

    asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_PRINTF), "b"("Welcome to &cDeadOS&7.\n"));
    asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_PRINTF), "b"("You are now in user space.\n"));
    asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_PRINTF), "b"("Type 'help' for a list of available commands.\n"));

    asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_SHELL_INIT));
}
