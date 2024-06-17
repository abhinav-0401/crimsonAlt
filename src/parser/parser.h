#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "using.h"
#include "lexer/token.h"
#include "parser/ast.h"

namespace Crimson {

class Parser {
public:
    Parser(std::vector<Token>&& tokens);
    void parse();
    void print_program();
    Program& program();
private:
    std::unique_ptr<Stmt> parse_stmt();
    std::unique_ptr<Stmt> parse_var_decl();
    std::unique_ptr<Expr> parse_expr();
    std::unique_ptr<Expr> parse_comparison();
    std::unique_ptr<Expr> parse_term();
    std::unique_ptr<Expr> parse_factor();
    std::unique_ptr<Expr> parse_primary();
    std::unique_ptr<Expr> parse_num_lit();
    bool not_eof();
    const Token& at();
    const Token& advance();
    void expect(TokenKind kind);
    TokenKind expect_either(TokenKind first, TokenKind second);
    VarType get_var_type(const Token& token);

    std::vector<Token> m_tokens;
    std::unique_ptr<Program> m_program;
    size_t m_curr;

    std::unordered_map<TokenKind, VarType> m_var_types = {
        {TokenKind::Number, VarType::Number},
        {TokenKind::Bool, VarType::Bool},
    };
};

} // Crimson
