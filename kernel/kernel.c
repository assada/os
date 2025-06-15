#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "arch.h"
#include "sys.h"
#include "shell.h"

void kernel_main(void)
{
    terminal_printf("Kernel start\n");
    terminal_initialize();
    arch_init();
    terminal_printf("Kernel initialized\n");
    
    sys_enable_interrupts();
    terminal_printf("Interrupts enabled\n");

    arch_enter_user_space();
}
