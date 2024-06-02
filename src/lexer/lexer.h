#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "token.h"

namespace Crimson {

class Lexer {
public:
    Lexer(std::string&& src);
    const std::vector<Token>& lex();
    std::vector<Token> tokens();
private:
    Token lex_token();
    void advance();
    Token new_token(char ch, TokenKind kind);
    bool is_letter(char ch);
    bool is_digit(char ch);
    TokenKind lookup_ident(const std::string& literal);
    std::string read_ident();
    std::string read_number();
    void skip_whitespace();
    bool is_whitespace(char ch);

    std::string m_src;
    size_t m_curr;
    size_t m_next;
    char m_ch;
    std::vector<Token> m_tokens;

    std::unordered_map<std::string, TokenKind> m_keywords = {
        {"and", TokenKind::And},
        {"break", TokenKind::Break},
        {"bool", TokenKind::Bool},
        {"else", TokenKind::Else},
        {"false", TokenKind::False},
        {"for", TokenKind::For},
        {"num", TokenKind::NumType},
        {"var", TokenKind::Var},
        {"number", TokenKind::Number},
        {"proc", TokenKind::Proc},
        {"if", TokenKind::If},
        {"return", TokenKind::Return},
        {"true", TokenKind::True},
        {"while", TokenKind::While},
    };
};

} // Crimson
