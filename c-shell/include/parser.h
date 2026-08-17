#define PARSER_H

#include "lexer.h"

typedef enum {
    STATE_LINE,
    STATE_ARG,
    STATE_CMD,
    STATE_TGT,
    STATE_BG
} ParserState;

int validate_grammar(const TokenStream *stream);