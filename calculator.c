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
    printf("> ");
    while ((linelen = get_line(&line, stdin)) > 1) {
        array = scan_tokens(line);
        rpn_array = infix_to_postfix(&array);
        free_all(&array);
        ans = evaluate_rpn(&rpn_array);
        printf("%g\n", ans);
        free_all(&rpn_array);
        printf("> ");
    }
    free(line);
    return 0;
}