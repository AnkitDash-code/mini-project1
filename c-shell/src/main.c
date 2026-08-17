#include "shell.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    char *code = NULL;
    size_t len = 0;

    capture_prompt();

    while(1) {
        show_prompt();

        if (getline(&code, &len, stdin) == -1) {
            printf("\n");
            break;
        }

        code[strcspn(code, "\n")] = '\0';

        if (code[0] == '\0'){
            continue;
        }
    }

    free (code);
    return 0;
}