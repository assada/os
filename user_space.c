void enter_user_space(void)
{
    asm volatile("cli;              \
                  mov $0x23, %ax;   \
                  mov %ax, %ds;     \
                  mov %ax, %es;     \
                  mov %ax, %fs;     \
                  mov %ax, %gs;     \
                  mov %esp, %eax;   \
                  pushl $0x23;      \
                  pushl %eax;       \
                  pushf;            \
                  popl %eax;        \
                  orl $0x200, %eax; \
                  pushl %eax;       \
                  pushl $0x1B;      \
                  push $1f;         \
                  iret;             \
                  1:                \
                  ");
}

void enter_user_space_v2()
{
    asm volatile("cli; \
                  mov $0x23, %ax; \
                  mov %ax, %ds; \
                  mov %ax, %es; \
                  mov %ax, %fs; \
                  mov %ax, %gs; \
                  mov %esp, %eax; \
                  push $0x23; \
                  push %eax; \
                  pushf; \
                  pop %eax; \
                  or $0x200, %eax; \
                  push %eax; \
                  push $0x1B; \
                  push $user_code_entry; \
                  iret; \
                  user_code_entry: \
                  call user_main; \
                  ");
}