#pragma once

#include <string>

// x: int = 123 
// x : int : 123

namespace Crimson {

enum class TokenKind {
    Err,
    Eof,

    Plus,
    Minus,
    Star,
    Slash,
    Mod,
    Caret,
    Hash,
    Ampersand,
    Tilde,
    Bar,
    Lparen,
    Rparen,
    Lbrace,
    Rbrace,
    LBracket,
    Rbracket,
    Colon,
    Semicolon,
    Comma,
    Equal,
    EqualEqual,
    Greater,
    Less,

    // Keywords
    And,
    Break,
    Else,
    False,
    For,
    Ident,
    Int,
    NumLiteral,
    NumType,
    Proc,
    If,
    Return,
    True,
    Var,
    While,
};

class Token {
public:
    Token() = default;
    Token(std::string&& literal, TokenKind kind);
    Token(Token&& other) noexcept;
    Token(const Token& other);
    Token& operator=(const Token& other) = default;
    Token& operator=(Token&& other) noexcept;
    const std::string& literal() const;
    TokenKind kind() const ;
private:
    std::string m_literal;
    TokenKind m_kind;
};

} // Crimson
