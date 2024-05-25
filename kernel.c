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
    terminal_initialize();
    gdt_install();

    idt_install();
    isr_install();
    irq_install();

    timer_install();
    keyboard_install();

    rtc_init();

    syscall_init();
    enter_user_space();
}

void main(void)
{
    for (int i = 1; i < 4; i++)
    {
        terminal_printf("&cTest &7%d\n", i);
        delay(200);
    }
    terminal_clear();

    terminal_printf("Welcome to &cDeadOS&7.\n");
    terminal_printf("You are now in user space.\n");
    terminal_printf("Type 'help' for a list of available commands.\n");

    shell_init();
}
