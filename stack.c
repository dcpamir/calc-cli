#include <stdlib.h>
#include "stack.h"

void init_stack(Stack *stack) {
    stack->tokens = NULL;
    stack->top = 0;
    stack->cap = 0;
}

void push(Stack *stack, Token *token) {
    if (stack->top == stack->cap) {
        int new_cap = stack->cap ? stack->cap * 2 : 16;
        Token *new_tokens = realloc(stack->tokens, new_cap * sizeof(Token));
        if (new_tokens == NULL) {
            return;
        }
        stack->tokens = new_tokens;
        stack->cap = new_cap;
    }
    stack->tokens[stack->top++] = *token;
}

Token pop(Stack *stack) {
    if (stack->top != 0) {
        return stack->tokens[--stack->top];
    }
    Token empty = {.type = TOK_EOF};
    return empty;
}

void free_stack(Stack *stack) {
    free(stack->tokens);
    stack->tokens = NULL;
    stack->top = 0;
    stack->cap = 0;
}