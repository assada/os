#include <stdarg.h>
#include "arch.h"
#include "syscall_numbers.h"
#include "syscalls.h"

static int invoke(int num, int a, int b, int c, int d, int e)
{
    return arch_syscall(num, a, b, c, d, e);
}

int printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int a = va_arg(args, int);
    int b = va_arg(args, int);
    int c = va_arg(args, int);
    int d = va_arg(args, int);
    va_end(args);
    return invoke(SYS_PRINTF, (int)fmt, a, b, c, d);
}

void sleep_ms(int ms)
{
    invoke(SYS_DELAY, ms, 0, 0, 0, 0);
}

void clear(void)
{
    invoke(SYS_CLEAR, 0, 0, 0, 0, 0);
}

void start_shell(void)
{
    invoke(SYS_SHELL_INIT, 0, 0, 0, 0, 0);
}

int getchar(void)
{
    return invoke(SYS_GETCHAR, 0, 0, 0, 0, 0);
}
