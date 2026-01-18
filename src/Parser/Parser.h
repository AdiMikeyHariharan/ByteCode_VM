#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "AST.h"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::vector<std::unique_ptr<Decl>> parse();

private:
    // Core grammar
    std::unique_ptr<Decl> declaration();

    // Token utilities
    bool match(TokenType type);
    bool check(TokenType type) const;
    bool isAtEnd() const;

    Token advance();
    Token peek() const;
    Token previous() const;

private:
    const std::vector<Token>& tokens;
    size_t current = 0;
};
