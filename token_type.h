#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

typedef enum {
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_NUMBER,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_MOD,
    TOK_UPLUS,
    TOK_UMINUS,
    TOK_EOF,
} TokenType;

#endif