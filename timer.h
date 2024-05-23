#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define PIT_FREQUENCY 1193182
#define PIT_CHANNEL_0 0x40
#define PIT_COMMAND 0x43

extern void pit_handler_asm(); // defined in pit_handler.s remove this

void pit_handler();
void delay(uint32_t milliseconds);
void pit_set_frequency(uint32_t frequency);
void pic_remap(int offset1, int offset2); // moved to irq_remap
void timer_install(void);

#endif
