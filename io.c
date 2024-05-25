#include "io.h"

void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void io_wait(void)
{
    asm volatile("jmp 1f\n\t"
                 "1:jmp 2f\n\t"
                 "2:");
}

void outb_wait(uint16_t port, uint8_t val)
{
    outb(port, val);
    io_wait();
}

uint8_t inb_wait(uint16_t port)
{
    uint8_t ret;
    ret = inb(port);
    io_wait();
    return ret;
}