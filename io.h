#ifndef IO_H
#define IO_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);

void outb_wait(uint16_t port, uint8_t val);
uint8_t inb_wait(uint16_t port);

#endif