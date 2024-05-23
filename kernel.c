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
    terminal_initialize();
    gdt_install();

    idt_install();
    isr_install();
    irq_install();

    timer_install();
    keyboard_install();

    syscall_init();
    for (int i = 0; i < 3; i++)
    {
        terminal_printc("&cDead &7");
        terminal_putchar('0' + (i / 10));
        terminal_putchar('0' + (i % 10));
        terminal_printc("\n");
        delay(100);
    }

    enter_user_space_v2();
}

void user_main(void)
{
    terminal_printc("Welcome to &cDeadOS&7.\n");

    for (int i = 0; i < 3; i++)
    {
        terminal_printc("&cDead2 &7");
        terminal_putchar('0' + (i / 10));
        terminal_putchar('0' + (i % 10));
        terminal_printc("\n");
        delay(100);
    }

    shell_init();
}