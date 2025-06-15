#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define PIT_FREQUENCY 1193182
#define PIT_CHANNEL_0 0x40
#define PIT_COMMAND 0x43

void delay(uint32_t milliseconds);
void timer_install(void);

#endif