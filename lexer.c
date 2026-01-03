#include "token.h"
#include "lexer.h"
#include <stdlib.h>
#include "tokens_array.h"

Scanner scanner;

TokensArray scan_tokens(char *line) {
    TokensArray array;
    init_array(&array);
    scanner.start = line;
    scanner.current = scanner.start;
    size_t pos = scanner.current - scanner.start;
    while (line[pos] != '\n') {
        Token token = tokeniser(line);
        pos = scanner.current - scanner.start;
        if (token.type == TOK_EOF) {
            break;
        }
        append(&array, &token);
    }
    Token eof = create_token(TOK_EOF, '\n', pos);
    append(&array, &eof);
    return array;
}

Token tokeniser(char *line) {
    skip_whitespace();
    size_t pos = scanner.current - scanner.start;
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
        return create_token(TOK_LPAREN, c, pos);
    case ')':
        return create_token(TOK_RPAREN, c, pos);
    case '+':
        return create_token(TOK_PLUS, c, pos);
    case '-':
        return create_token(TOK_MINUS, c, pos);
    case '*':
        return create_token(TOK_STAR, c, pos);
    case '/':
        return create_token(TOK_SLASH, c, pos);
    case '%':
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
        return create_token_num(TOK_NUMBER, n, pos);}
    default:
        scanner.current += 1;
        return tokeniser(line);
    }
}

Token create_token(TokenType type, char c, size_t pos) {
    Token token;
    token.type = type;
    token.value.c = c;
    token.pos = pos;
    scanner.current += 1;
    return token;
}

Token create_token_num(TokenType type, double value, size_t pos) {
    Token token;
    token.type = type;
    token.value.n = value;
    token.pos = pos;
    return token;
}

void skip_whitespace() {
    size_t pos = scanner.current - scanner.start;
    while (scanner.start[pos] == ' ' || scanner.start[pos] == '\t' || scanner.start[pos] == '\r') {
        scanner.current++;
        pos = scanner.current - scanner.start;
    }
}