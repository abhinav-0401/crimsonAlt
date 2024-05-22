#include <memory>

#include "ast.h"

namespace Crimson {

NumLiteral::NumLiteral(double value)
    : m_value(value) 
{
}

double NumLiteral::value() { return m_value; }

NodeType NumLiteral::stmt_type() { return m_node_kind; }


BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, std::unique_ptr<Expr> right, Token op)
    : m_left(std::move(left)), m_right(std::move(right)), m_op(op)
{
}

NodeType BinaryExpr::stmt_type() { return m_node_kind; }


Program::Program()
    : m_body()
{
}

void Program::append_stmt(std::unique_ptr<Stmt>&& stmt) {
    m_body.push_back(std::move(stmt));
}

NodeType Program::stmt_type() { return m_node_kind; }

} // Crimson
