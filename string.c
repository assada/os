#include "string.h"
#include <stddef.h>

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

char *strchr(const char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == c)
        {
            return (char *)str;
        }
        str++;
    }
    return NULL;
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
