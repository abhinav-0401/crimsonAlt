#include <memory>
#include <iostream>
#include <type_traits>

#include "ast.h"

namespace Crimson {

NumLiteral::NumLiteral(double value)
    : m_value(value) 
{
}

double NumLiteral::value() { return m_value; }

VarType NumLiteral::var_type() { return m_var_type; }

NodeType NumLiteral::stmt_type() { return m_node_kind; }

void NumLiteral::print_info() {
    std::cout << "NumLiteral: " << m_value;
}


BoolLiteral::BoolLiteral(bool value)
    : m_value(value) 
{
}

bool BoolLiteral::value() { return m_value; }

VarType BoolLiteral::var_type() { return m_var_type; }

NodeType BoolLiteral::stmt_type() { return m_node_kind; }

void BoolLiteral::print_info() {
    std::cout << "BoolLiteral: " << m_value;
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


VarDeclStmt::VarDeclStmt(Token ident, VarType var_type, std::unique_ptr<Expr> value)
    : m_ident(std::move(ident)), m_var_type(var_type), m_value(std::move(value))
{
}

VarType VarDeclStmt::var_type() { return m_var_type; }

NodeType VarDeclStmt::stmt_type() { return m_node_kind; }

void VarDeclStmt::print_info() {
    std::cout << "VarDeclStmt: \n";
    std::cout << "\tIdent: " << m_ident.literal() << "\n";
    std::cout << "\tType: " << static_cast<std::underlying_type<VarType>::type>(m_var_type) << "\n";
    std::cout << "\tValue: \n";
    m_value->print_info();
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

void Program::print_info() {
}

} // Crimson
