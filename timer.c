#include "timer.h"
#include "io.h"
#include "sys.h"
#include "idt.h"

#define PIT_FREQUENCY 1193182
#define PIT_CHANNEL_0 0x40
#define PIT_COMMAND 0x43

volatile uint32_t tick = 0;

void pit_handler()
{
    tick++;
    outb(0x20, 0x20);
}

void pic_remap(int offset1, int offset2)
{
    unsigned char a1, a2;

    a1 = inb(0x21);
    a2 = inb(0xA1);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, offset1);
    outb(0xA1, offset2);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, a1);
    outb(0xA1, a2);
}

void delay(uint32_t milliseconds)
{
    uint32_t end = tick + milliseconds;
    while (tick < end)
    {
        sys_halt();
    }
}

void pit_set_frequency(uint32_t frequency)
{
    uint32_t divisor = PIT_FREQUENCY / frequency;
    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL_0, divisor & 0xFF);
    outb(PIT_CHANNEL_0, (divisor >> 8) & 0xFF);
}

void timer_install(void)
{
    pic_remap(0x20, 0x28);
    pit_set_frequency(1000);
    idt_set_gate(32, (uint32_t)pit_handler_asm, 0x08, 0x8E);
}