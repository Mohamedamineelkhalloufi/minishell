#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

char **split_input(char *input)
{
    char **commands = malloc(256 * sizeof(char *));
    int i = 0, start = 0, end = 0;

    while (input[end]) {
        if (input[end] == '|') {
            int len = end - start;
            commands[i] = malloc(len + 1);
            for (int j = 0; j < len; j++)
                commands[i][j] = input[start + j];
            commands[i][len] = '\0';
            i++;
            end++;
            while (input[end] == ' ') end++;
            start = end;
        } else {
            end++;
        }
    }
    if (end > start) {
        int len = end - start;
        commands[i] = malloc(len + 1);
        for (int j = 0; j < len; j++)
            commands[i][j] = input[start + j];
        commands[i][len] = '\0';
        i++;
    }

    commands[i] = NULL;
    return commands;
}


char **split_args(char *command)
{
    char **args = malloc(64 * sizeof(char *));
    int i = 0, start = 0, end = 0;

    while (command[end]) {
        if (command[end] == ' ') {
            if (start != end) {
                int len = end - start;
                args[i] = malloc(len + 1);
                for (int j = 0; j < len; j++)
                    args[i][j] = command[start + j];
                args[i][len] = '\0';
                i++;
            }
            while (command[end] == ' ') end++;
            start = end;
        } else {
            end++;
        }
    }
    if (end > start) {
        int len = end - start;
        args[i] = malloc(len + 1);
        for (int j = 0; j < len; j++)
            args[i][j] = command[start + j];
        args[i][len] = '\0';
        i++;
    }

    args[i] = NULL;
    return args;
}


int main(void)
{
    char *input;
    char **commands;
    char **args;
    int pipefds[2];
    pid_t pid;
    int i = 0;

    while (1) {
        input = readline("minishell> ");
        if (input == NULL) {
            break;
        }
        commands = split_input(input);
        
        int num_commands = 0;
        while (commands[num_commands] != NULL) num_commands++;

        int prev_pipe = 0;
        for (i = 0; i < num_commands; i++) {
            pipe(pipefds);

            pid = fork();
            if (pid == 0) {
                if (prev_pipe) {
                    dup2(prev_pipe, STDIN_FILENO);
                    close(prev_pipe);
                }
                if (i < num_commands - 1) {
                    dup2(pipefds[1], STDOUT_FILENO);
                }
                close(pipefds[0]);
                close(pipefds[1]);
                args = split_args(commands[i]);
                execvp(args[0], args);
                error_exit("execvp failed");
            }
            else {
                close(pipefds[1]);
                prev_pipe = pipefds[0];
            }
        }
        close(prev_pipe);
        for (i = 0; i < num_commands; i++)
            wait(NULL);
        free(input);
        free(commands);
    }

    return 0;
}
