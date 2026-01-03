#ifndef TOKEN_ARRAY_H
#define TOKEN_ARRAY_H

#include <stdlib.h>
#include "token.h"

typedef struct {
    Token *tokens;
    size_t end;
    size_t cap;
} TokensArray;

void append(TokensArray *array, Token *token);
void free_all(TokensArray *array);
void init_array(TokensArray *array);

#endif