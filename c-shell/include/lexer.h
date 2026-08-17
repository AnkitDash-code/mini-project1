#ifndef LEXER_H // throws error if missing dont touch might add for all header files
#define LEXER_H

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,  // |
    TOKEN_AMP,   // &
    TOKEN_SEMI,  // ;
    TOKEN_LT,    // <
    TOKEN_GT,    // >
    TOKEN_GTGT,  // >>
    TOKEN_EOF
} TokenType;

typedef struct Token {
    TokenType type;
    char *value;         
    struct Token *next;
} Token;

typedef struct TokenStream {
    Token *head;
    Token *tail;
} TokenStream;

int tokenize_line(const char *input, TokenStream *stream);

void free_tokens(TokenStream *stream);

#endif