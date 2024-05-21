#include "string.h"
#include <stddef.h>

size_t strlen(const char *str)
{
    size_t len = 0;

    while (str[len])
        ++len;

    return len;
}

void *memset(void *ptr, int value, size_t size)
{
    unsigned char *buf = (unsigned char *)ptr;

    for (size_t i = 0; i < size; ++i)
        buf[i] = (unsigned char)value;

    return ptr;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

char *strchr(const char *str, int character)
{
    size_t i = 0;
    while (str[i] != (char)character)
    {
        if (str[i] == '\0')
            return NULL;
        ++i;
    }

    return (char *)(str + i);
}

char *strtok(char *str, const char *delim)
{
    static char *last_token = NULL;
    char *token_start;
    char *current;

    if (str != NULL)
    {
        current = str;
    }
    else
    {
        current = last_token;
    }

    if (current == NULL)
    {
        return NULL;
    }

    while (*current != '\0' && strchr(delim, *current) != NULL)
    {
        current++;
    }

    if (*current == '\0')
    {
        last_token = NULL;
        return NULL;
    }

    token_start = current;

    while (*current != '\0' && strchr(delim, *current) == NULL)
    {
        current++;
    }

    if (*current != '\0')
    {
        *current = '\0';
        last_token = current + 1;
    }
    else
    {
        last_token = NULL;
    }

    return token_start;
}
