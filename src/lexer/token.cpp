#include <utility>
#include <iostream>

#include "token.h"

namespace Crimson {

Token::Token(std::string&& literal, TokenKind kind)
    :m_literal(std::move(literal)), m_kind(kind)
{
}

Token::Token(Token&& other) noexcept
    : m_literal(std::move(other.m_literal)), m_kind(other.m_kind)
{
}

Token::Token(const Token& other)
    : m_literal(other.m_literal), m_kind(other.m_kind)
{
}

Token& Token::operator=(Token&& other) noexcept {
    m_literal = std::move(other.m_literal);
    m_kind = other.m_kind;
    return *this;
}

TokenKind Token::kind() const {
    return m_kind;
}

const std::string& Token::literal() const {
    return m_literal;
}

} // Crimson
