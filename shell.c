#include <stdbool.h>
#include "keyboard.h"
#include "shell.h"
#include "tty.h"
#include "string.h"

void shell_init(void)
{
    char input_buffer[SHELL_BUFFER_SIZE + 1];
    size_t i;
    char c;

    while (true)
    {
        terminal_printf("&7dead@&croot&7: /> ");

        i = 0;
        c = 0;

        while (i < SHELL_BUFFER_SIZE)
        {
            c = keyboard_getchar();

            if (c == '\b')
            {
                if (i > 0)
                {
                    terminal_printf("\b \b");
                    --i;
                }
            }
            else
            {
                terminal_putchar(c);
                input_buffer[i] = c;
                ++i;

                if (c == '\n')
                    break;
            }
        }

        input_buffer[i] = '\0';
        keyboard_clear_buffer();
        shell_parse_input(input_buffer);
    }
}

void shell_help_command(void)
{
    terminal_printf("List of commands:\n");
    terminal_printf("help - Print out the list of commands.\n");
    terminal_printf("exit - Exit the shell.\n");
    terminal_printf("echo - Print out the message. &eWITH colors!&7\n");
    terminal_printf("clear - Clear the terminal.\n");
}

void shell_exit_command(void)
{
    terminal_printf("Exiting shell...\n");
    terminal_printf("Goodbye!\n");
    while (1)
        ;
}

void shell_echo_command(char *input)
{
    char *message = input;

    while (*message == ' ')
    {
        message++;
    }

    terminal_printf(message);
    terminal_printf("\n");
}

void shell_parse_input(char *input)
{
    char *command = strtok(input, " \n");
    char *args = input + strlen(command) + 1;

    if (command == NULL || *command == '\0')
    {
        return;
    }

    if (strcmp(command, "help") == 0)
    {
        shell_help_command();
    }
    else if (strcmp(command, "echo") == 0)
    {
        shell_echo_command(args);
    }
    else if (strcmp(command, "exit") == 0)
    {
        shell_exit_command();
    }
    else if (strcmp(command, "clear") == 0)
    {
        terminal_clear();
    }
    else
    {
        terminal_printf("Unknown command: '");
        terminal_print(command);
        terminal_printf("'\n");
        terminal_printf("Type 'help' to print out the list of commands.\n");
    }
}
