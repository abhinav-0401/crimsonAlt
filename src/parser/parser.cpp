#include <utility>
#include <memory>
#include <string>
#include <iostream>
#include <cstdlib>

#include "ast.h"
#include "parser.h"
#include "lexer/token.h"

namespace Crimson {

Parser::Parser(std::vector<Token>&& tokens)
    : m_tokens(std::move(tokens)), m_program(std::make_unique<Program>()), m_curr(0)
{
}

void Parser::parse() {
    while (not_eof()) {
        auto stmt = parse_stmt();
        m_program->append_stmt(std::move(stmt));
    }
}

void Parser::print_program() {
    m_program->print_body();
}

std::unique_ptr<Stmt> Parser::parse_stmt() {
    const Token& token = at();
    
    switch (token.kind()) {
    default:
        auto expr = parse_expr();
        return expr;
    }
}

std::unique_ptr<Expr> Parser::parse_expr() {
    auto left = parse_term();

    while (at().kind() == TokenKind::Plus || at().kind() == TokenKind::Minus) {
        const Token& op = advance();
        auto right = parse_term();
        auto binary_expr = std::make_unique<BinaryExpr>(std::move(left), std::move(right), op);
        left = std::move(binary_expr);
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_term() {    
    auto left = parse_factor();

    while (at().kind() == TokenKind::Star || at().kind() == TokenKind::Slash) {
        const Token& op = advance();
        auto right = parse_factor();
        auto binary_expr = std::make_unique<BinaryExpr>(std::move(left), std::move(right), op);
        left = std::move(binary_expr);
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_factor() {
    if (at().kind() == TokenKind::Lparen) {
        advance();
        std::cout << "in here\n";
        auto expr = parse_expr();
        expect(TokenKind::Rparen);
        return expr;
    }

    auto factor = parse_num_lit();
    return factor;
}

std::unique_ptr<Expr> Parser::parse_num_lit() {
    const Token& token = at();
    std::cout << "token: " << token.literal() << "\n";
    auto num_lit = std::make_unique<NumLiteral>(std::stod(token.literal()));
    advance();
    return num_lit;
}

bool Parser::not_eof() {
    return m_tokens[m_curr].kind() != TokenKind::Eof;
}

const Token& Parser::at() {
    if (m_tokens[m_curr].kind() == TokenKind::Eof) {

    }
    return m_tokens[m_curr];
}

const Token& Parser::advance() {
    const Token& prev = m_tokens[m_curr];
    ++m_curr;
    return prev;
}

void Parser::expect(TokenKind kind) {
    if (at().kind() != kind) {
        std::cerr << "Error: Unexpected token\n";
        std::exit(1);
    }
    advance();
}

} // Crimson
