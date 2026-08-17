#include "parser.h"
#include <stddef.h>


// DFA to validate the grammar of the input to the shell
int validate_grammar(const TokenStream *stream) {
    ParserState state = STATE_LINE;
    Token *curr = stream->head;

    while (curr) {
        switch (state) {
            case STATE_LINE:
                if (curr->type == TOKEN_EOF) return 0;
                if (curr->type == TOKEN_WORD) state = STATE_ARG;
                else return -1;
                break;

            case STATE_ARG:
                if (curr->type == TOKEN_EOF) return 0;
                if (curr->type == TOKEN_WORD) state = STATE_ARG;
                else if (curr->type == TOKEN_LT || curr->type == TOKEN_GT || curr->type == TOKEN_GTGT) state = STATE_TGT;
                else if (curr->type == TOKEN_PIPE || curr->type == TOKEN_SEMI) state = STATE_CMD;
                else if (curr->type == TOKEN_AMP) state = STATE_BG;
                break;

            case STATE_CMD:
                if (curr->type == TOKEN_WORD) state = STATE_ARG;
                else return -1;
                break;

            case STATE_TGT:
                if (curr->type == TOKEN_WORD) state = STATE_ARG;
                else return -1;
                break;

            case STATE_BG:
                if (curr->type == TOKEN_EOF) return 0;
                if (curr->type == TOKEN_WORD) state = STATE_ARG;
                else return -1;
                break;
        }
        curr = curr->next;
    }

    return 0;
}