#include "shell.h"
#include "prompt.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
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

        TokenStream stream = {NULL, NULL};

        if (tokenize_line(code, &stream) != 0 || validate_grammar(&stream) != 0) {
            printf("cshell: invalid syntax\n");
            free_tokens(&stream);
            continue;
        }
        else {

           int check =  exec_builtin(&stream);
           if ( check == -1) {
            printf("Command Not implemented Yet\n");
           }
        }
        free_tokens(&stream);
    }

    free (code);
    return 0;
}