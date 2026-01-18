#pragma once
#include <string>

enum class TokenType {
    // Keywords
    KW_INT, KW_FLOAT, KW_DOUBLE, KW_CHAR, KW_VOID,
    KW_IF, KW_ELSE, KW_WHILE, KW_FOR, KW_RETURN,

    // Identifiers & literals
    IDENTIFIER,
    INT_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,

    // Operators
    PLUS, MINUS, STAR, SLASH, MOD,
    ASSIGN,
    EQ, NEQ,
    LT, GT, LE, GE,
    AND, OR, NOT,

    // Delimiters
    LPAREN, RPAREN,
    LBRACE, RBRACE,
    SEMICOLON, COMMA,

    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType t, std::string lx, int ln)
        : type(t), lexeme(std::move(lx)), line(ln) {}
};
