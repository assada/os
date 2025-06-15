#include "arch.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "sys.h"
#include "interrupts.h"
#include "keyboard.h"
#include "rtc.h"
#include "syscall.h"
#include "user_space.h"

void arch_init(void)
{
    gdt_install();
    idt_install();
    isr_install();
    irq_install();
    timer_install();
    keyboard_install();
    rtc_init();
    syscall_init();
}

void arch_enter_user_space(void)
{
    enter_user_space();
}
