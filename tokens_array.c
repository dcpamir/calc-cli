#include <stdlib.h>
#include "tokens_array.h"

void init_array(TokensArray *array) {
    array->tokens = NULL;
    array->end = 0;
    array->cap = 0;
}

void append(TokensArray *array, Token *token) {
    if (array->end == array->cap) {
        size_t new_cap = array->cap ? array->cap * 2 : 16;
        Token *new_tokens = realloc(array->tokens, new_cap * sizeof(Token));
        if (new_tokens == NULL) {
            return; // allocation failure leaves array unchanged
        }
        array->tokens = new_tokens;
        array->cap = new_cap;
    }
    array->tokens[array->end++] = *token;
}

void free_all(TokensArray *array) {
    free(array->tokens);
    array->tokens = NULL;
    array->end = 0;
    array->cap = 0;
}