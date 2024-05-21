#include "tty.h"
#include "vga.h"
#include "io.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

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
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
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

static void terminal_backspace(void)
{
    if (terminal_column == 0)
    {
        terminal_column = VGA_WIDTH - 1;
        if (terminal_row == 0)
        {
            terminal_column = 0;
        }
        else
        {
            --terminal_row;
        }
        uint16_t empty = vga_entry(' ', terminal_color);
        uint16_t index = terminal_pos(terminal_column, terminal_row);
        while (terminal_column > 0 && terminal_buffer[index] == empty)
        {
            --terminal_column;
            index = terminal_pos(terminal_column, terminal_row);
        }
        if (terminal_buffer[index] != empty && terminal_column + 1 < VGA_WIDTH)
        {
            ++terminal_column;
        }
    }
    else
    {
        --terminal_column;
    }
    uint16_t index = terminal_pos(terminal_column, terminal_row);
    terminal_buffer[index] = vga_entry(' ', terminal_color);
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
        uint16_t index = terminal_pos(terminal_column, terminal_row);
        terminal_buffer[index] = vga_entry(c, terminal_color);
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

void terminal_writestring(const char *data)
{
    terminal_write(data, strlen(data));
}

void terminal_printc(const char *data)
{
    while (*data)
    {
        if (*data == '&' && ((*(data + 1) >= '0' && *(data + 1) <= '9') ||
                             (*(data + 1) >= 'a' && *(data + 1) <= 'f')))
        {
            terminal_setcolor(vga_entry_color(vga_color_from_char(*(data + 1)), VGA_COLOR_BLACK));
            data += 2;
        }
        else
        {
            terminal_putchar(*data);
            data++;
        }
    }
}

void terminal_update_cursor(void)
{
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

void terminal_clear(void)
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }

    terminal_column = 0;
    terminal_row = 0;
    terminal_update_cursor();
}