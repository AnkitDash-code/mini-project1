#include "builtins.h"
#include <string.h>


int exec_builtin(const TokenStream *stream){
    if (!stream || !stream->head || !stream->head->value) {
        return -1; // To check that the stream consists of data
    }

    char* command = stream->head->value;
    Token *args = stream->head->next;

    if (strcmp(command, "hop") == 0) {
        return handle_hop(args);
    } 
    else if (strcmp(command, "reveal") == 0) {
        return handle_reveal(args);
    } 
    else if (strcmp(command, "peek") == 0) {
        return handle_peek(args);
    } 
    else if (strcmp(command, "locate") == 0) {
        return handle_locate(args);
    }

    return -1;

}