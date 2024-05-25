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

void kernel_main(void)
{
    gdt_install();

    idt_install();
    isr_install();
    irq_install();

    timer_install();
    keyboard_install();

    syscall_init();
    enter_user_space();
}

void main(void)
{
    terminal_initialize();
    for (int i = 1; i < 4; i++)
    {
        terminal_printf("&cTest &7%d\n", i);
        delay(500);
    }
    terminal_clear();

    terminal_printf("Welcome to &cDeadOS&7.\n");
    terminal_printf("You are now in user space.\n");
    terminal_printf("Type 'help' for a list of available commands.\n");

    shell_init();
}
