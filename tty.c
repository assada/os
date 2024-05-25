#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "tty.h"
#include "vga.h"
#include "io.h"
#include "string.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        terminal_buffer[i] = vga_entry(' ', terminal_color);
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

static uint16_t terminal_pos(uint8_t x, uint8_t y)
{
    return y * VGA_WIDTH + x;
}

void terminal_scroll(void)
{
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
    }
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_update_cursor(void)
{
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

static void terminal_backspace(void)
{
    if (terminal_column == 0)
    {
        terminal_column = VGA_WIDTH - 1;
        if (terminal_row > 0)
        {
            --terminal_row;
        }
    }
    else
    {
        --terminal_column;
    }
    terminal_buffer[terminal_pos(terminal_column, terminal_row)] = vga_entry(' ', terminal_color);
}

void terminal_putchar(char c)
{
    if (c == '\n')
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_scroll();
        }
    }
    else if (c == '\b')
    {
        terminal_backspace();
    }
    else
    {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
            {
                terminal_scroll();
            }
        }
    }
    terminal_update_cursor();
}

void terminal_write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        terminal_putchar(data[i]);
    }
}

void terminal_print(const char *data)
{
    terminal_write(data, strlen(data));
}

void terminal_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    const char *p = format;
    while (*p)
    {
        if (*p == '%' && (*(p + 1) == 's' || *(p + 1) == 'd' || *(p + 1) == 'x'))
        {
            p++;
            if (*p == 's')
            {
                terminal_print(va_arg(args, const char *));
            }
            else if (*p == 'd')
            {
                char buffer[12];
                itoa(va_arg(args, int), buffer, 10);
                terminal_print(buffer);
            }
            else if (*p == 'x')
            {
                char buffer[12];
                itoa(va_arg(args, unsigned int), buffer, 16);
                terminal_print(buffer);
            }
        }
        else if (*p == '&' && ((*(p + 1) >= '0' && *(p + 1) <= '9') || (*(p + 1) >= 'a' && *(p + 1) <= 'f')))
        {
            terminal_setcolor(vga_entry_color(vga_color_from_char(*(p + 1)), VGA_COLOR_BLACK));
            p++;
        }
        else
        {
            terminal_putchar(*p);
        }
        p++;
    }

    va_end(args);
}

void terminal_clear(void)
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        terminal_buffer[i] = vga_entry(' ', terminal_color);
    }
    terminal_column = 0;
    terminal_row = 0;
    terminal_update_cursor();
}
