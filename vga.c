#include "vga.h"

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

uint8_t vga_color_from_char(char color_code) {
    switch (color_code) {
        case '0': return VGA_COLOR_BLACK;
        case '1': return VGA_COLOR_BLUE;
        case '2': return VGA_COLOR_GREEN;
        case '3': return VGA_COLOR_CYAN;
        case '4': return VGA_COLOR_RED;
        case '5': return VGA_COLOR_MAGENTA;
        case '6': return VGA_COLOR_BROWN;
        case '7': return VGA_COLOR_LIGHT_GREY;
        case '8': return VGA_COLOR_DARK_GREY;
        case '9': return VGA_COLOR_LIGHT_BLUE;
        case 'a': return VGA_COLOR_LIGHT_GREEN;
        case 'b': return VGA_COLOR_LIGHT_CYAN;
        case 'c': return VGA_COLOR_LIGHT_RED;
        case 'd': return VGA_COLOR_LIGHT_MAGENTA;
        case 'e': return VGA_COLOR_LIGHT_BROWN;
        case 'f': return VGA_COLOR_WHITE;
        default: return VGA_COLOR_LIGHT_GREY;
    }
}