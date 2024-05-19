#pragma once

#include "lexer/token.h"

namespace Crimson {

enum class NodeType {
    NumLiteral,
};

class Stmt {
public:
    virtual NodeType stmt_type() = 0;
};

class Expr : public Stmt {
public:
    virtual NodeType expr_type() = 0;
};

class NumLiteral : public Expr {
public:
    NumLiteral() = default;
    NumLiteral(double value);
    double value();
private:
    double m_value;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr() = delete;
    BinaryExpr(Expr&& left, Expr&& right, Token op);
private:
    Expr* m_left;
    Expr* m_right;
    Token op;
};

} // Crimson
