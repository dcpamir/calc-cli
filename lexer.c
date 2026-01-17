#include "lexer.h"
#include <stdlib.h>

Scanner scanner;

TokensArray scan_tokens(char *line, ErrorCodes *err_code) {
    TokensArray array;
    init_array(&array);
    scanner.start = line;
    scanner.current = scanner.start;
    int pos = scanner.current - scanner.start;
    int unary_expected = 1;
    while (line[pos] != '\n') {
        Token token = tokeniser(line, pos, &unary_expected, err_code);
        pos = scanner.current - scanner.start;
        if (token.type == TOK_EOF) {
            break;
        }
        if (token.type == TOK_ERROR) {
            *err_code = ERR_INVALID_TOK;
            append(&array, &token);
            break;
        }
        if (token.type != TOK_SPACE && token.type != TOK_UPLUS)
            append(&array, &token);
    }
    if (!*err_code) {
        Token eof = create_token(TOK_EOF, '\n', pos);
        append(&array, &eof);
        return array;
    }
    return array;
}

Token tokeniser(char *line, int pos, int *unary_expected, ErrorCodes *err_code) {
    char c = line[pos];
    if (c == '\n' || c == '\0') {
        Token eof;
        eof.type = TOK_EOF;
        eof.value.c = '\0';
        eof.pos = pos;
        return eof;
    }
    switch (c) {
    case '(':
        *unary_expected = 1;
        return create_token(TOK_LPAREN, c, pos);
    case ')':
        *unary_expected = 0;
        return create_token(TOK_RPAREN, c, pos);
    case '+':
        if (*unary_expected) {
            return create_token(TOK_UPLUS, c, pos);
        }
        *unary_expected = 1;
        return create_token(TOK_PLUS, c, pos);
    case '-':
        if (*unary_expected) {
            return create_token(TOK_UMINUS, c, pos);
        }
        *unary_expected = 1;
        return create_token(TOK_MINUS, c, pos);
    case '*':
        *unary_expected = 1;
        return create_token(TOK_STAR, c, pos);
    case '/':
        *unary_expected = 1;
        return create_token(TOK_SLASH, c, pos);
    case '%':
        *unary_expected = 1;
        return create_token(TOK_MOD, c, pos);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        {char *endptr;
        double n = strtod(line + pos, &endptr);
        scanner.current = endptr;
        *unary_expected = 0;
        return create_token_num(TOK_NUMBER, n, pos);}
    case ' ':
    case '\t':
    case '\r':
        return create_token(TOK_SPACE, c, pos);
    default:
        *err_code = ERR_INVALID_TOK;
        return create_token(TOK_ERROR, c, pos);
    }
}

Token create_token(TokenType type, char c, int pos) {
    Token token = {
        .type = type,
        .value.c = c,
        .pos = pos,
    };
    scanner.current += 1;
    return token;
}

Token create_token_num(TokenType type, double value, int pos) {
    Token token = {
        .type = type,
        .value.n = value,
        .pos = pos
    };
    return token;
}
