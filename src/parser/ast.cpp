#include <memory>
#include <iostream>

#include "ast.h"

namespace Crimson {

NumLiteral::NumLiteral(double value)
    : m_value(value) 
{
}

double NumLiteral::value() { return m_value; }

NodeType NumLiteral::stmt_type() { return m_node_kind; }

void NumLiteral::print_info() {
    std::cout << "NumLiteral: " << m_value;
}

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, std::unique_ptr<Expr> right, Token op)
    : m_left(std::move(left)), m_right(std::move(right)), m_op(op)
{
}

NodeType BinaryExpr::stmt_type() { return m_node_kind; }

void BinaryExpr::print_info() {
    std::cout << "BinaryExpr: \n";
    std::cout << "\tleft: ";
    m_left->print_info();
    std::cout << "\n";
    std::cout << "\tright: ";
    m_right->print_info();
    std::cout << "\n";
    std::cout << "\toperator: " << m_op.literal() << "\n";
}

void Program::append_stmt(std::unique_ptr<Stmt>&& stmt) {
    m_body.push_back(std::move(stmt));
}

void Program::print_body() {
    for (const auto& stmt : m_body) {
        stmt->print_info();
    }
}

NodeType Program::stmt_type() { return m_node_kind; }

void Program::print_info() {}

} // Crimson
