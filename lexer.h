#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include "tokens_array.h"

typedef struct {
    char *start;
    char *current;
} Scanner;

Token create_token(TokenType type, char c, int pos);
Token create_token_num(TokenType type, double n, int pos);
Token tokeniser(char *line, int po, int *unary_expected, ErrorCodes *err_code);
TokensArray scan_tokens(char *line, ErrorCodes *err_code);

#endif