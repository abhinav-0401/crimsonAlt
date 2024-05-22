#pragma once

#include <memory>
#include <vector>

#include "lexer/token.h"

namespace Crimson {

enum class NodeType {
    Program,
    NumLiteral,
    BinaryExpr,
};

class Stmt {
public:
    virtual NodeType stmt_type() = 0;
    virtual void print_info() = 0;
};

class Expr : public Stmt {
public:
    virtual NodeType stmt_type() = 0;
    virtual void print_info() = 0;
};

class NumLiteral : public Expr {
public:
    NumLiteral() = default;
    NumLiteral(double value);
    double value();
    NodeType stmt_type() override;
    void print_info() override;
private:
    double m_value;
    NodeType m_node_kind = NodeType::NumLiteral;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr() = default;
    BinaryExpr(std::unique_ptr<Expr>, std::unique_ptr<Expr>, Token op);
    NodeType stmt_type() override;
    void print_info() override;
private:
    std::unique_ptr<Expr> m_left;
    std::unique_ptr<Expr> m_right;
    Token m_op;
    NodeType m_node_kind = NodeType::BinaryExpr;
};

class Program : public Stmt {
public:
    Program() = default;
    void append_stmt(std::unique_ptr<Stmt>&& stmt);
    void print_body();
    NodeType stmt_type() override;
    void print_info() override;
private:
    std::vector<std::unique_ptr<Stmt>> m_body;
    NodeType m_node_kind = NodeType::Program;
};

} // Crimson
