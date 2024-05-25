#ifndef STRING_H
#define STRING_H

#include <stddef.h>

char *strchr(const char *str, int c);
char *strtok(char *str, const char *delim);
int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);
void itoa(int value, char *str, int base);

void *memset(void *ptr, int value, size_t size);
void memcpy(void *vd, const void *vs, unsigned length);

#endif