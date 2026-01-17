#include "evaluate.h"
#include "stack.h"
#include "lexer.h"

double evaluate_rpn(TokensArray *rpn_array, ErrorCodes *err_code) {
    Stack stack;
    init_stack(&stack);
    for (int i = 0; i < rpn_array->end; i++) {
        Token token = rpn_array->tokens[i];
        if (*err_code) {
            break;
        }
        if (token.type == TOK_NUMBER) {
            push(&stack, &token);
        }
        else if (token.type == TOK_UMINUS) {
            Token a = pop(&stack);
            double result = -1 * a.value.n;
            Token res_token = create_token_num(TOK_NUMBER, result, token.pos);
            push(&stack, &res_token);
        }
        else {
            Token b = pop(&stack);
            Token a = pop(&stack);
            if (b.type != TOK_NUMBER || a.type != TOK_NUMBER) {
                *err_code = ERR_INVALID_OP;
                break;
            }
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
                if (b.value.n == 0) {
                    *err_code = ERR_DIVISION_BY_ZERO;
                    break;
                }
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