#ifndef TOKEN_ARRAY_H
#define TOKEN_ARRAY_H

#include <stdlib.h>

typedef enum {
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_NUMBER,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_MOD,
    TOK_UMINUS,
    TOK_UPLUS,
    TOK_SPACE,
    TOK_ERROR,
    TOK_EOF,
} TokenType;

typedef enum {
    ERR_NO_ERROR,
    ERR_INVALID_TOK,
    ERR_INVALID_OP,
    ERR_UNMATCHED_PAREN,
    ERR_DIVISION_BY_ZERO,
} ErrorCodes;

typedef struct {
    TokenType type;
    union {
        double n;
        char c;
    }value;
    int pos;
} Token;

typedef struct {
    Token *tokens;
    int end;
    int cap;
} TokensArray;

void append(TokensArray *array, Token *token);
void free_all(TokensArray *array);
void init_array(TokensArray *array);

#endif