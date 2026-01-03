#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include "token_type.h"
#include "tokens_array.h"

typedef struct {
    char *start;
    char *current;
} Scanner;

Token create_token(TokenType type, char c, size_t pos);
Token create_token_num(TokenType type, double n, size_t pos);
Token tokeniser(char *line);
TokensArray scan_tokens(char *line);
void skip_whitespace();

#endif