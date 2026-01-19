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

    // Handle variable declaration: int x = 10;
    if (match(TokenType::KW_INT) ||
        match(TokenType::KW_FLOAT) ||
        match(TokenType::KW_DOUBLE) ||
        match(TokenType::KW_CHAR)) {

        std::string type = previous().lexeme;

        // Expect variable name
        Token name = advance();
        if (name.type != TokenType::IDENTIFIER)
            throw std::runtime_error("Expected variable name");

        std::unique_ptr<Expr> initializer = nullptr;

        // Optional initializer
        if (match(TokenType::ASSIGN)) {
            // TEMPORARY: skip expression parsing for now
            // Just read one literal or identifier
            Token value = advance();

            if (value.type == TokenType::INT_LITERAL ||
                value.type == TokenType::FLOAT_LITERAL) {
                initializer = std::make_unique<LiteralExpr>(value.lexeme);
            }
            else if (value.type == TokenType::IDENTIFIER) {
                initializer = std::make_unique<VariableExpr>(value.lexeme);
            }
            else {
                throw std::runtime_error("Invalid initializer");
            }
        }

        if (!match(TokenType::SEMICOLON))
            throw std::runtime_error("Expected ';' after declaration");

        auto decl = std::make_unique<VarDecl>();
        decl->type = type;
        decl->name = name.lexeme;
        decl->initializer = std::move(initializer);

        return decl;
    }

    // If not a declaration → error for now
    throw std::runtime_error("Only variable declarations supported for now");
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
