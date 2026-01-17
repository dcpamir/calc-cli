#include "shunting_yard.h"
#include "stack.h"
#include <stdlib.h>

TokensArray infix_to_postfix(TokensArray *array, ErrorCodes *err_code) {
    Stack stack;
    TokensArray rpn_array;
    init_array(&rpn_array);
    init_stack(&stack);
    int i = 0;
    while (array->tokens[i].type != TOK_EOF) {
        if (array->tokens[i].type == TOK_NUMBER) {
            append(&rpn_array, &array->tokens[i]);
        }
        else if (array->tokens[i].type == TOK_LPAREN) {
            push(&stack, &array->tokens[i]);
        }
        else if (array->tokens[i].type == TOK_RPAREN) {
            while (stack.top > 0 && stack.tokens[stack.top - 1].type != TOK_LPAREN) {
                Token op = pop(&stack);
                append(&rpn_array, &op);
            }
            if (stack.top > 0)
                pop(&stack);
            else {
                Token err = {
                    .pos = array->tokens[i].pos,
                    .type = TOK_ERROR,
                    .value.c = ')'
                };
                append(&rpn_array, &err);
                *err_code = ERR_UNMATCHED_PAREN;
                break;
            }
        }
        else if (array->tokens[i].type == TOK_UMINUS) {
            push(&stack, &array->tokens[i]);
        }
        else {
            while (stack.top > 0 && 
                   get_precedence(stack.tokens[stack.top - 1].type) >= get_precedence(array->tokens[i].type)) {
                Token op = pop(&stack);
                append(&rpn_array, &op);
            }
            push(&stack, &array->tokens[i]);
        }
        i++;
    }
    while (stack.top > 0) {
        Token op = pop(&stack);
        if (op.type != TOK_LPAREN)
            append(&rpn_array, &op);
        else {
            Token err = {
                .pos = op.pos,
                .type = TOK_ERROR,
                .value.c = '(',
            };
            append(&rpn_array, &err);
            *err_code = ERR_UNMATCHED_PAREN;
            break;
        }
    }
    free_stack(&stack);
    return rpn_array;
}

int get_precedence(TokenType type) {
    switch (type) {
        case TOK_PLUS:
        case TOK_MINUS:
            return 1;
        case TOK_STAR:
        case TOK_SLASH:
        case TOK_MOD:
            return 2;
        case TOK_UMINUS:
            return 3;
        default:
            return 0;
    }
}