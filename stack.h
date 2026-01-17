#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "tokens_array.h"

typedef struct {
    Token *tokens;
    int top, cap;
} Stack;

void init_stack(Stack *stack);
void push(Stack *stack, Token *token);
Token pop(Stack *stack);
void free_stack(Stack *stack);

#endif