#ifndef BUILTINS_H
#define BUILTINS_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "lexer.h"

extern char prev_cwd[PATH_MAX];

int exec_builtin(const TokenStream *stream);

int handle_hop(const Token *args);
int handle_reveal(const Token *args);
int handle_peek(const Token *args);
int handle_locate(const Token *args);



#endif