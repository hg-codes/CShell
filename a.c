#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

void display_prompt() {
    printf("myshell> ");
    fflush(stdout);
}

char* read_input() {
    char *input = malloc(MAX_INPUT);
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        perror("fgets failed");
        exit(EXIT_FAILURE);
    }
    input[strcspn(input, "\n")] = 0; // Remove newline
    return input;
}

char** parse_input(char *input) {
    char **args = malloc(MAX_ARGS * sizeof(char*));
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}

int execute_command(char **args) {
    if (args[0] == NULL) return 1;  // Empty command

    // Built-in command: exit
    if (strcmp(args[0], "exit") == 0)
        return 0;

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork failed");
    }

    return 1;
}

int main() {
    while (1) {
        display_prompt();

        char *input = read_input();
        char **args = parse_input(input);

        int status = execute_command(args);

        free(input);
        free(args);

        if (status == 0) break;
    }

    return 0;
}
