#ifndef _KERNEL_SHELL_H
#define _KERNEL_SHELL_H

#define SHELL_BUFFER_SIZE 256

void shell_init(void);
void shell_parse_input(char *input);

#endif