#include "timer.h"
#include "io.h"
#include "sys.h"
#include "interrupts.h"

volatile uint32_t tick = 0;

void pit_handler(Stack *registers)
{
    ++tick;
}

void delay(uint32_t milliseconds)
{
    uint32_t end = tick + milliseconds;
    while (tick < end)
        ;
}

void pit_set_frequency(uint32_t frequency)
{
    uint32_t divisor = PIT_FREQUENCY / frequency;
    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL_0, divisor & 0xFF);
    outb(PIT_CHANNEL_0, divisor >> 8);
}

void timer_install(void)
{
    irq_install_handler(0, pit_handler);
    pit_set_frequency(1000);
}
