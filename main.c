#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "input.h"
#include "tokens_array.h"
#include "lexer.h"
#include "shunting_yard.h"
#include "evaluate.h"

int main() {
    char *line = NULL;
    ssize_t linelen;
    double ans;
    TokensArray array, rpn_array;
    ErrorCodes err_code = ERR_NO_ERROR;
    printf("> ");
    while ((linelen = get_line(&line, stdin)) > 1) {
        array = scan_tokens(line, &err_code);
        if (err_code == ERR_INVALID_TOK) {
            printf("%s", line);
            printf("%*c\n", array.tokens[array.end - 1].pos+1, '^');
            printf("Syntax Error: Invalid Character ' %c '\n", array.tokens[array.end - 1].value.c);
            printf("> ");
            free_all(&array);
            err_code = ERR_NO_ERROR;
            continue;
        }
        rpn_array = infix_to_postfix(&array, &err_code);
        if (err_code == ERR_UNMATCHED_PAREN) {
            printf("%s", line);
            printf("%*c\n", rpn_array.tokens[rpn_array.end - 1].pos+1, '^');
            printf("Syntax Error: Unmatched Parenthesis\n");
            printf("> ");
            free_all(&rpn_array);
            err_code = ERR_NO_ERROR;
            continue;
        }
        free_all(&array);
        ans = evaluate_rpn(&rpn_array, &err_code);
        if (err_code == ERR_DIVISION_BY_ZERO) {
            printf("%s", line);
            printf("Syntax Error: Division by Zero\n");
            printf("> ");
            free_all(&rpn_array);
            err_code = ERR_NO_ERROR;
            continue;
        }
        if (err_code == ERR_INVALID_OP) {
            printf("%s", line);
            printf("Syntax Error: Invalid Operation\n");
            printf("> ");
            free_all(&rpn_array);
            err_code = ERR_NO_ERROR;
            continue;
        }
        printf("%g\n", ans);
        free_all(&rpn_array);
        printf("> ");
    }
    free(line);
    return 0;
}