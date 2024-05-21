#ifndef IDT_H
#define IDT_H

#include <stdint.h>

extern void idt_load();

void idt_install();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif