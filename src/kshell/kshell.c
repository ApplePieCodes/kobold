#include <keyboard.h>
#include <stdio.h>
#include <term/term.h>
#include <string.h>

void help() {
    printf("Kobold Kernel v0.1.0\n");
    printf("help - Display this screen\n");
    printf("clear - Clear the screen\n");
}

void runKShell() {
    printf("Kobold Kernel Shell\n");
    printf("Type 'help' for a list of commands.\n");

    char input[256];

    while (1) {
        printf("kshell> ");

        readLine(&input[0]);

        if (strcmp(input, "clear") == 0) {
            clearScreen();
        }
        else if (strcmp(input, "help") == 0) {
            help();
        }
        else {
            printf("\"%s\" is not a valid command\n", input);
        }
    }
}