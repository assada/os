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
        terminal_printc("\n");
        terminal_printc("&7dead@&croot&7: /> ");

        i = 0;
        c = 0;

        while (i < SHELL_BUFFER_SIZE)
        {
            c = keyboard_getchar();

            if (c == '\b')
            {
                if (i > 0)
                {
                    terminal_printc("\b \b");
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
    terminal_printc("List of commands:\n");
    terminal_printc("help - Print out the list of commands.\n");
    terminal_printc("exit - Exit the shell.\n");
    terminal_printc("echo - Print out the message. &eWITH colors!&7\n");
    terminal_printc("clear - Clear the terminal.\n");
}

void shell_exit_command(void)
{
    terminal_printc("Exiting shell...\n");
    terminal_printc("Goodbye!\n");
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

    terminal_printc(message);
    terminal_printc("\n");
}

void shell_parse_input(char *input)
{
    char *command = strtok(input, " \n");
    char *first_param = strtok(NULL, " \n");

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
        shell_echo_command(first_param);
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
        terminal_printc("Unknown command: '");
        terminal_writestring(command);
        terminal_printc("'\n");
        terminal_printc("Type 'help' to print out the list of commands.\n");
    }
}
