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
    case TokenKind::Var: {
        auto stmt = parse_var_decl();
        return stmt;
    }
    default:
        auto expr = parse_expr();
        return expr;
    }
}

std::unique_ptr<Stmt> Parser::parse_var_decl() {
    advance();
    const Token& ident = advance();
    expect(TokenKind::Colon);
    const Token& var_type_tok = advance();
    VarType var_type = get_var_type(var_type_tok);
    expect(TokenKind::Equal);
    auto value_expr = parse_expr();
    expect(TokenKind::Semicolon);
    return std::make_unique<VarDeclStmt>(ident, var_type, std::move(value_expr));
}

std::unique_ptr<Expr> Parser::parse_expr() {
    auto left = parse_term();

    while (at().kind() == TokenKind::Greater || at().kind() == TokenKind::Less) {
        const Token& op = advance();
        auto right = parse_factor();
        auto binary_expr = std::make_unique<BinaryExpr>(std::move(left), std::move(right), op);
        left = std::move(binary_expr);
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_term() {
    auto left = parse_factor();

    while (at().kind() == TokenKind::Plus || at().kind() == TokenKind::Minus) {
        const Token& op = advance();
        auto right = parse_factor();
        auto binary_expr = std::make_unique<BinaryExpr>(std::move(left), std::move(right), op);
        left = std::move(binary_expr);
    }
    return left;
}


std::unique_ptr<Expr> Parser::parse_factor() {    
    auto left = parse_primary();

    while (at().kind() == TokenKind::Star || at().kind() == TokenKind::Slash) {
        const Token& op = advance();
        auto right = parse_primary();
        auto binary_expr = std::make_unique<BinaryExpr>(std::move(left), std::move(right), op);
        left = std::move(binary_expr);
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_primary() {
    switch (at().kind()) {
    case TokenKind::Lparen: { 
        advance();
        std::cout << "in here\n";
        auto expr = parse_expr();
        expect(TokenKind::Rparen);
        return expr;
    }
    case TokenKind::NumLiteral: {
        auto factor = parse_num_lit();
        return factor;
    }
    case TokenKind::True: {
        std::cout << "inside primary\n";
        auto bool_lit = std::make_unique<BoolLiteral>(true);
        advance();
        return bool_lit;
    }
    case TokenKind::False: {
        auto bool_lit = std::make_unique<BoolLiteral>(true);
        advance();
        return bool_lit;
    }
    }
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
        std::cout << at().literal() << "\n";
        std::cerr << "Error: Unexpected token\n";
        std::exit(1);
    }
    advance();
}

VarType Parser::get_var_type(const Token& token) {
    return m_var_types[token.kind()];
}

} // Crimson
