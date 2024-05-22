#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "lexer.h"
#include "token.h"
#include "using.h"

namespace Crimson {

Lexer::Lexer(std::string&& src)
    : m_src(std::move(src)),
    m_curr(0), m_next(1), m_ch(m_src[0]), m_tokens() 
{
}

const std::vector<Token>& Lexer::lex() {
    for (Token token = lex_token(); token.kind() != TokenKind::Eof; token = lex_token()) {
        m_tokens.push_back(std::move(token));
    }
    m_tokens.push_back(Token("EOF", TokenKind::Eof));
    
    return m_tokens;
}

std::vector<Token> Lexer::tokens() {
    return m_tokens;
}

Token Lexer::lex_token() { 
    Token token;

    skip_whitespace();

    switch (m_ch) {
    case '+':
        token = new_token(m_ch, TokenKind::Plus);
        break;
    case '-':
        token = new_token(m_ch, TokenKind::Minus);
        break;
    case '*':
        token = new_token(m_ch, TokenKind::Star);
        break;
    case '/':
        token = new_token(m_ch, TokenKind::Slash);
        break;
    case ':':
        token = new_token(m_ch, TokenKind::Colon);
        break;
    case '\0':
        token = new_token(m_ch, TokenKind::Eof);
        break;
    default: {
        if (is_letter(m_ch)) {
            std::string literal = read_ident();
            TokenKind kind = lookup_ident(literal);
            token = Token(std::move(literal), kind);
        } else if (is_digit(m_ch)) {
            std::string literal = read_number();
            token = Token(std::move(literal), TokenKind::NumLiteral);
        } else {
            token = new_token(m_ch, TokenKind::Err);
        }
        break;
    }
    }

    return token;
}

Token Lexer::new_token(char ch, TokenKind kind) {
    Token token(std::string(1, ch), kind);
    advance();
    return token;
}

void Lexer::advance() {
    if (m_next >= m_src.size()) {
        m_ch = '\0';
        return;
    }

    ++m_curr;
    ++m_next;
    m_ch = m_src[m_curr];
}

bool Lexer::is_letter(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_') { return true; }
    return false;
}

bool Lexer::is_digit(char ch) {
    if (ch >= '1' && ch <= '9') { return true; }
    return false;
}

std::string Lexer::read_ident() {
    std::string ident;
    ident += m_ch;
    advance();

    while (is_letter(m_ch)) {
        ident  += m_ch;
        advance();
    }

    return ident;
}

std::string Lexer::read_number() {
    std::string num;
    num += m_ch;
    advance();
    
    uint8_t dots = 0;
    while (is_digit(m_ch) || m_ch == '.') {
        if (dots < 1 && m_ch == '.') {
            ++dots;
            num += m_ch;
            advance();
        } else if (is_digit(m_ch)) {
            num += m_ch;
            advance();
        } else {
            break;
        }
    }

    return num;
}

TokenKind Lexer::lookup_ident(const std::string& literal) {
    TokenKind kind = TokenKind::Ident;
    try {
        kind = m_keywords.at(literal);
        return kind;
    } catch (std::out_of_range& e) {
    }
    return kind;
}

void Lexer::skip_whitespace() {
    while (is_whitespace(m_ch)) { advance(); }
}

bool Lexer::is_whitespace(char ch) {
    if (ch == '\n' || ch == ' ' || ch == '\t' || ch == '\r') { return true; }
    return false;
}

} // Crimson
