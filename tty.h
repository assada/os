#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_printf(const char *data, ...);
void terminal_print(const char *data);
void terminal_clear(void);
void terminal_putchar(char c);

#endif