#include "syscalls.h"

void user_main(void)
{
    for (int i = 1; i < 4; i++)
    {
        printf("&cTest &7%d\n", i);
        sleep_ms(1000);
    }

    clear();

    printf("Welcome to &cDeadOS&7.\n");
    printf("You are now in user space.\n");
    printf("Type 'help' for a list of available commands.\n");

    start_shell();
}
