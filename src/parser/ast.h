#pragma once

#include <memory>
#include <vector>

#include "lexer/token.h"

namespace Crimson {

enum class NodeType {
    Program,
    NumLiteral,
    BoolLiteral,
    BinaryExpr,
    VarDeclStmt,
};

enum class VarType {
    Number,
    Bool,
    Invalid,
};

class Stmt {
public:
    virtual NodeType stmt_type() const = 0;
    virtual void print_info() const = 0;
};

class Expr : public Stmt {
public:
    virtual NodeType stmt_type() const = 0;
    virtual void print_info() const = 0;
    virtual VarType var_type() const = 0;
};

class NumLiteral : public Expr {
public:
    NumLiteral() = default;
    NumLiteral(double value);
    double value();
    VarType var_type() const override;
    NodeType stmt_type() const override;
    void print_info() const override;

private:
    double m_value;
    VarType m_var_type = VarType::Number;
    NodeType m_node_kind = NodeType::NumLiteral;
};

class BoolLiteral : public Expr {
public:
    BoolLiteral() = default;
    BoolLiteral(bool value);
    bool value();
    VarType var_type() const override;
    NodeType stmt_type() const override;
    void print_info() const override;

private:
    double m_value;
    VarType m_var_type = VarType::Bool;
    NodeType m_node_kind = NodeType::NumLiteral;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr() = default;
    BinaryExpr(std::unique_ptr<Expr>, std::unique_ptr<Expr>, Token op);
    NodeType stmt_type() const override;
    void print_info() const override;
    VarType var_type() const override;

private:
    std::unique_ptr<Expr> m_left;
    std::unique_ptr<Expr> m_right;
    Token m_op;
    NodeType m_node_kind = NodeType::BinaryExpr;
};

class VarDeclStmt : public Stmt {
public:
    VarDeclStmt() = default;
    VarDeclStmt(Token ident, VarType var_type, std::unique_ptr<Expr> m_value);
    const Expr& value();
    VarType var_type() const;
    NodeType stmt_type() const override;
    void print_info() const override;

private:
    Token m_ident;
    VarType m_var_type;
    std::unique_ptr<Expr> m_value;
    NodeType m_node_kind = NodeType::VarDeclStmt;
};

class Program : public Stmt {
public:
    Program() = default;
    std::vector<std::unique_ptr<Stmt>>& body();
    void append_stmt(std::unique_ptr<Stmt>&& stmt);
    void print_body();
    NodeType stmt_type() const override;
    void print_info() const override;

private:
    std::vector<std::unique_ptr<Stmt>> m_body;
    NodeType m_node_kind = NodeType::Program;
};

} // namespace Crimson
