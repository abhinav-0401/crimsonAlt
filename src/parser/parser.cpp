#include <utility>
#include <memory>
#include <string>

#include "ast.h"
#include "parser.h"
#include "lexer/token.h"

namespace Crimson {

Parser::Parser(std::vector<Token>&& tokens)
    : m_tokens(std::move(tokens)), m_program(std::make_unique<Program>()), m_curr(0)
{
}

void Parser::parse() {
    // 2
    while (not_eof()) {
        auto stmt = parse_stmt();
        m_program->append_stmt(std::move(stmt));
    }
}

std::unique_ptr<Stmt> Parser::parse_stmt() {
    const Token& token = at();
    
    switch (token.kind()) {
    case TokenKind::NumLiteral:
        auto num_lit = std::make_unique<NumLiteral>(std::stod(token.literal()));
        return num_lit;
    }
}

bool Parser::not_eof() {
    return m_tokens[m_curr].kind() != TokenKind::Eof;
}

const Token& Parser::at() {
    return m_tokens[m_curr];
}

const Token& Parser::advance() {
    const Token& prev = m_tokens[m_curr];
    ++m_curr;
    return prev;
}

} // Crimson
