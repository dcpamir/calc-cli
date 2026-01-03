#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"
#include <stdlib.h>

typedef struct {
    TokenType type;
    union {
        double n;
        char c;
    }value;
    size_t pos;
} Token;

#endif