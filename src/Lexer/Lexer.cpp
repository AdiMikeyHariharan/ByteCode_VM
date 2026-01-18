#include "Lexer.h"
#include <cctype>
#include <unordered_map>
#include <stdexcept>

/* ---------------- KEYWORDS ---------------- */

static const std::unordered_map<std::string, TokenType> keywords = {
    {"int",    TokenType::KW_INT},
    {"float",  TokenType::KW_FLOAT},
    {"double", TokenType::KW_DOUBLE},
    {"char",   TokenType::KW_CHAR},
    {"void",   TokenType::KW_VOID},
    {"if",     TokenType::KW_IF},
    {"else",   TokenType::KW_ELSE},
    {"while",  TokenType::KW_WHILE},
    {"for",    TokenType::KW_FOR},
    {"return", TokenType::KW_RETURN}
};

/* ---------------- CONSTRUCTOR ---------------- */

Lexer::Lexer(const std::string& src)
    : source(src) {}

/* ---------------- CORE DRIVER ---------------- */

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (current < source.size()) {
        skipWhitespace();
        if (current >= source.size()) break;

        char c = advance();

        switch (c) {
            case '+': tokens.emplace_back(TokenType::PLUS, "+", line); break;
            case '-': tokens.emplace_back(TokenType::MINUS, "-", line); break;
            case '*': tokens.emplace_back(TokenType::STAR, "*", line); break;
            case '/': tokens.emplace_back(TokenType::SLASH, "/", line); break;
            case '%': tokens.emplace_back(TokenType::MOD, "%", line); break;

            case '=':
                tokens.emplace_back(match('=') ? TokenType::EQ : TokenType::ASSIGN, "=", line);
                break;

            case '!':
                tokens.emplace_back(match('=') ? TokenType::NEQ : TokenType::NOT, "!", line);
                break;

            case '<':
                tokens.emplace_back(match('=') ? TokenType::LE : TokenType::LT, "<", line);
                break;

            case '>':
                tokens.emplace_back(match('=') ? TokenType::GE : TokenType::GT, ">", line);
                break;

            case '&':
                if (match('&')) tokens.emplace_back(TokenType::AND, "&&", line);
                else throw std::runtime_error("Unexpected '&'");
                break;

            case '|':
                if (match('|')) tokens.emplace_back(TokenType::OR, "||", line);
                else throw std::runtime_error("Unexpected '|'");
                break;

            case '(':
                tokens.emplace_back(TokenType::LPAREN, "(", line); break;
            case ')':
                tokens.emplace_back(TokenType::RPAREN, ")", line); break;
            case '{':
                tokens.emplace_back(TokenType::LBRACE, "{", line); break;
            case '}':
                tokens.emplace_back(TokenType::RBRACE, "}", line); break;
            case ';':
                tokens.emplace_back(TokenType::SEMICOLON, ";", line); break;
            case ',':
                tokens.emplace_back(TokenType::COMMA, ",", line); break;

            case '"':
                tokens.push_back(stringLiteral());
                break;

            case '\'':
                tokens.push_back(charLiteral());
                break;

            default:
                if (std::isdigit(c)) {
                    current--;               // step back
                    tokens.push_back(number());
                }
                else if (std::isalpha(c) || c == '_') {
                    current--;
                    tokens.push_back(identifier());
                }
                else {
                    throw std::runtime_error("Unexpected character");
                }
        }
    }

    tokens.emplace_back(TokenType::EOF_TOKEN, "", line);
    return tokens;
}

char Lexer::peek() const {
    if (current >= source.size()) return '\0';
    return source[current];
}

char Lexer::advance() {
    return source[current++];
}

bool Lexer::match(char expected) {
    if (peek() != expected) return false;
    current++;
    return true;
}

void Lexer::skipWhitespace() {
    while (true) {
        char c = peek();

        switch (c) {
            case ' ':
            case '\t':
            case '\r':
                advance();
                break;

            case '\n':
                line++;
                advance();
                break;

            default:
                return;
        }
    }
}

Token Lexer::identifier() {
    size_t start = current;

    while (std::isalnum(peek()) || peek() == '_')
        advance();

    std::string text = source.substr(start, current - start);

    auto it = keywords.find(text);
    if (it != keywords.end())
        return Token(it->second, text, line);

    return Token(TokenType::IDENTIFIER, text, line);
}

Token Lexer::number() {
    size_t start = current;

    while (std::isdigit(peek()))
        advance();

    bool isFloat = false;
    if (peek() == '.') {
        isFloat = true;
        advance();
        while (std::isdigit(peek()))
            advance();
    }

    std::string num = source.substr(start, current - start);

    return Token(isFloat ? TokenType::FLOAT_LITERAL
                         : TokenType::INT_LITERAL,
                 num,
                 line);
}

Token Lexer::stringLiteral() {
    size_t start = current;

    while (peek() != '"' && peek() != '\0') {
        if (peek() == '\n') line++;
        advance();
    }

    if (peek() == '\0')
        throw std::runtime_error("Unterminated string");

    advance(); // closing "

    std::string value = source.substr(start, current - start - 1);
    return Token(TokenType::STRING_LITERAL, value, line);
}

Token Lexer::charLiteral() {
    char value = advance();

    if (advance() != '\'')
        throw std::runtime_error("Invalid char literal");

    return Token(TokenType::CHAR_LITERAL, std::string(1, value), line);
}
