// #include "Parser.h"

// Parser::Parser(const std::vector<Token>& tokens)
//     : tokens(tokens) {}

// std::vector<std::unique_ptr<Decl>> Parser::parse() {
//     std::vector<std::unique_ptr<Decl>> declarations;

//     while (!match(TokenType::END_OF_FILE)) {
//         declarations.push_back(declaration());
//     }

//     return declarations;
// }
#include "Parser.h"
#include <stdexcept>

/* ---------------- CONSTRUCTOR ---------------- */

Parser::Parser(const std::vector<Token>& toks)
    : tokens(toks) {}

/* ---------------- ENTRY POINT ---------------- */

std::vector<std::unique_ptr<Decl>> Parser::parse() {
    std::vector<std::unique_ptr<Decl>> declarations;

    while (!isAtEnd()) {
        declarations.push_back(declaration());
    }

    return declarations;
}

/* ---------------- CORE PARSER STUBS ---------------- */

std::unique_ptr<Decl> Parser::declaration() {
    throw std::runtime_error("Parser::declaration() not implemented yet");
}

/* ---------------- TOKEN UTILITIES ---------------- */

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const {
    return tokens[current - 1];
}
