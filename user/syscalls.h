#ifndef USER_SYSCALLS_H
#define USER_SYSCALLS_H

int printf(const char *fmt, ...);
void sleep_ms(int ms);
void clear(void);
void start_shell(void);
int getchar(void);

#endif /* USER_SYSCALLS_H */
