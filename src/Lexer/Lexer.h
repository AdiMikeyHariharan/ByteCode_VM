#pragma once
#include "Token.h"
#include <vector>
#include <string>

class Lexer {
public:
    explicit Lexer(const std::string& src);
    std::vector<Token> tokenize();

private:
    char peek() const;
    char advance();
    bool match(char expected);

    void skipWhitespace();
    Token identifier();
    Token number();
    Token stringLiteral();
    Token charLiteral();

    const std::string& source;
    size_t current = 0;
    int line = 1;
};
