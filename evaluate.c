#include "evaluate.h"
#include "stack.h"
#include "lexer.h"

double evaluate_rpn(TokensArray *rpn_array) {
    Stack stack;
    init_stack(&stack);
    for (size_t i = 0; i < rpn_array->end; i++) {
        Token token = rpn_array->tokens[i];
        if (token.type == TOK_NUMBER) {
            push(&stack, &token);
        }
        else {
            Token b = pop(&stack);
            Token a = pop(&stack);
            double result = 0.0;
            switch (token.type) {
            case TOK_PLUS:
                result = a.value.n + b.value.n;
                break;
            case TOK_MINUS:
                result = a.value.n - b.value.n;
                break;
            case TOK_STAR:
                result = a.value.n * b.value.n;
                break;
            case TOK_SLASH:
                result = a.value.n / b.value.n;
                break;
            case TOK_MOD:
                result = (int)a.value.n % (int)b.value.n;
                break;
            default:
                break;
            }
            Token res_token = create_token_num(TOK_NUMBER, result, token.pos);
            push(&stack, &res_token);
        }
    }
    Token final_result = pop(&stack);
    double ans = final_result.value.n;
    free_stack(&stack);
    return ans;
}