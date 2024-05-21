#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

extern void pit_handler_asm();

void pit_handler();
void delay(uint32_t milliseconds);
void pit_set_frequency(uint32_t frequency);
void pic_remap(int offset1, int offset2);
void timer_install(void);

#endif