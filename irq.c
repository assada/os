#include <stdint.h>

#include "interrupts.h"
#include "io.h"
#include "sys.h"
#include "idt.h"

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

void *irq_routines[NB_IRQ_ROUTINES] = {0};

void irq_install_handler(uint8_t irq, void (*handler)(Stack *registers))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(uint8_t irq)
{
    irq_routines[irq] = 0;
}

void irq_call_handler(Stack *registers)
{
    void (*handler)(Stack *registers);
    handler = irq_routines[registers->id - 32];
    if (handler)
    {
        handler(registers);
    }
}

static void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

void irq_install(void)
{
    irq_remap();

    idt_set_gate(32, (uint32_t)irq0, 0x08, 0xEE);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0xEE);
    idt_set_gate(34, (uint32_t)irq2, 0x08, 0xEE);
    idt_set_gate(35, (uint32_t)irq3, 0x08, 0xEE);
    idt_set_gate(36, (uint32_t)irq4, 0x08, 0xEE);
    idt_set_gate(37, (uint32_t)irq5, 0x08, 0xEE);
    idt_set_gate(38, (uint32_t)irq6, 0x08, 0xEE);
    idt_set_gate(39, (uint32_t)irq7, 0x08, 0xEE);
    idt_set_gate(40, (uint32_t)irq8, 0x08, 0xEE);
    idt_set_gate(41, (uint32_t)irq9, 0x08, 0xEE);
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0xEE);
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0xEE);
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0xEE);
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0xEE);
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0xEE);
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0xEE);

    sys_enable_interrupts();
}

void irq_handler(Stack *registers)
{
    irq_call_handler(registers);

    if (registers->id >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}
