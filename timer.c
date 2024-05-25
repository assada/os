#include <stdint.h>

#include "interrupts.h"
#include "io.h"
#include "timer.h"

volatile uint32_t timer_ticks = 0;

void delay(const uint32_t ticks)
{
    uint32_t total_ticks = timer_ticks + ticks;
    while (timer_ticks < total_ticks)
        ;
}

void timer_handler(Stack *registers)
{
    ++timer_ticks;
}

static void timer_phase(const uint32_t hz)
{
    uint32_t divisor = PIT_FREQUENCY / hz;

    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL_0, divisor & 0xFF);
    outb(PIT_CHANNEL_0, divisor >> 8);
}

void timer_install(void)
{
    irq_install_handler(0, timer_handler);

    timer_phase(1000);
}
