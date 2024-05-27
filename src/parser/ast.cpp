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

VarType NumLiteral::var_type() const { return m_var_type; }

NodeType NumLiteral::stmt_type() const { return m_node_kind; }

void NumLiteral::print_info() const {
    std::cout << "NumLiteral: " << m_value;
}


BoolLiteral::BoolLiteral(bool value)
    : m_value(value) 
{
}

bool BoolLiteral::value() { return m_value; }

VarType BoolLiteral::var_type() const { return m_var_type; }

NodeType BoolLiteral::stmt_type() const { return m_node_kind; }

void BoolLiteral::print_info() const {
    std::cout << "BoolLiteral: " << m_value;
}


BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, std::unique_ptr<Expr> right, Token op)
    : m_left(std::move(left)), m_right(std::move(right)), m_op(op)
{
}

NodeType BinaryExpr::stmt_type() const { return m_node_kind; }

void BinaryExpr::print_info() const {
    std::cout << "BinaryExpr: \n";
    std::cout << "\tleft: ";
    m_left->print_info();
    std::cout << "\n";
    std::cout << "\tright: ";
    m_right->print_info();
    std::cout << "\n";
    std::cout << "\toperator: " << m_op.literal() << "\n";
}

static VarType numeric_var_type(VarType left_type, VarType right_type) {
    if ((left_type == VarType::Number) && (right_type == VarType::Number)) {
        return VarType::Number;
    }
    return VarType::Invalid;
}

VarType BinaryExpr::var_type() const {
    auto left_type = m_left->var_type();
    auto right_type = m_right->var_type();

    switch (m_op.kind()) {
    case TokenKind::Plus:
    case TokenKind::Minus:
    case TokenKind::Star:
    case TokenKind::Greater:
    case TokenKind::Less:
    case TokenKind::Slash: {
        return numeric_var_type(left_type, right_type);
    }
    }
}


VarDeclStmt::VarDeclStmt(Token ident, VarType var_type, std::unique_ptr<Expr> value)
    : m_ident(std::move(ident)), m_var_type(var_type), m_value(std::move(value))
{
}

const Expr& VarDeclStmt::value() { return *m_value; }

VarType VarDeclStmt::var_type() const { return m_var_type; }

NodeType VarDeclStmt::stmt_type() const { return m_node_kind; }

void VarDeclStmt::print_info() const {
    std::cout << "VarDeclStmt: \n";
    std::cout << "\tIdent: " << m_ident.literal() << "\n";
    std::cout << "\tType: " << static_cast<std::underlying_type<VarType>::type>(m_var_type) << "\n";
    std::cout << "\tValue: \n";
    m_value->print_info();
}


std::vector<std::unique_ptr<Stmt>>& Program::body() { return m_body; }

void Program::append_stmt(std::unique_ptr<Stmt>&& stmt) {
    m_body.push_back(std::move(stmt));
}

void Program::print_body() {
    for (const auto& stmt : m_body) {
        stmt->print_info();
    }
}

NodeType Program::stmt_type() const { return m_node_kind; }

void Program::print_info() const {
}

} // Crimson
