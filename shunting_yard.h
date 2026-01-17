#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "tokens_array.h"

TokensArray infix_to_postfix(TokensArray *array, ErrorCodes *err_code);
int get_precedence(TokenType type);

#endif