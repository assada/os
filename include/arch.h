#ifndef ARCH_H
#define ARCH_H

void arch_init(void);
void arch_enter_user_space(void);

int arch_syscall(int num, int a, int b, int c, int d, int e);

#endif
