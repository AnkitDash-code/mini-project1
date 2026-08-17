#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int is_special(char c) {
    return c == '|' || c == '&' || c == ';' || c == '<' || c == '>';
}

static void add_token(TokenStream *stream, TokenType type, const char *val) {
    Token *t = malloc(sizeof(Token));
    t->type = type;
    t->value = val ? strdup(val) : NULL;
    t->next = NULL;

    if (!stream->head) {
        stream->head = t;
        stream->tail = t;
    } else {
        stream->tail->next = t;
        stream->tail = t;
    }
}


int tokenize_line(const char *input, TokenStream *stream) {
    int i = 0;

    while (input[i] != '\0') {
        if (is_space(input[i])) {
            i++;
            continue;
        }

        
        if (is_special(input[i])) {
            if (input[i] == '|') add_token(stream, TOKEN_PIPE, NULL);
            else if (input[i] == '&') add_token(stream, TOKEN_AMP, NULL);
            else if (input[i] == ';') add_token(stream, TOKEN_SEMI, NULL);
            else if (input[i] == '<') add_token(stream, TOKEN_LT, NULL);
            else if (input[i] == '>') {
                if (input[i + 1] == '>') {
                    add_token(stream, TOKEN_GTGT, NULL);
                    i++;
                } else {
                    add_token(stream, TOKEN_GT, NULL);
                }
            }
            i++;
            continue;
        }

        
        char buf[4096];
        int buf_idx = 0;

        while (input[i] != '\0' && !is_space(input[i]) && !is_special(input[i])) {
            if (input[i] == '\'') {
                
                i++;
                while (input[i] != '\0' && input[i] != '\'') {
                    buf[buf_idx++] = input[i++];
                }
                if (input[i] == '\0') return -1; 
                i++;
            } else if (input[i] == '"') {
                
                i++;
                while (input[i] != '\0' && input[i] != '"') {
                    if (input[i] == '\\') {
                        if (input[i + 1] == '"' || input[i + 1] == '\\') {
                            buf[buf_idx++] = input[i + 1];
                            i += 2;
                        } else if (input[i + 1] == '\0') {
                            return -1; 
                        } else {
                            buf[buf_idx++] = input[i++];
                            buf[buf_idx++] = input[i++];
                        }
                    } else {
                        buf[buf_idx++] = input[i++];
                    }
                }
                if (input[i] == '\0') return -1; 
                i++;
            } else if (input[i] == '\\') {
                
                if (input[i + 1] == '\0') return -1; 
                buf[buf_idx++] = input[i + 1];
                i += 2;
            } else {
                buf[buf_idx++] = input[i++];
            }
        }

        buf[buf_idx] = '\0';
        add_token(stream, TOKEN_WORD, buf);
    }

    add_token(stream, TOKEN_EOF, NULL);
    return 0;
}

void free_tokens(TokenStream *stream) {
    Token *curr = stream->head;
    while (curr) {
        Token *next = curr->next;
        if (curr->value) free(curr->value);
        free(curr);
        curr = next;
    }
    stream->head = NULL;
    stream->tail = NULL;
} //wsl crashed without this because memory ran out and thus I added