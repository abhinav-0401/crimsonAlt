#include <memory>
#include <iostream>
#include <type_traits>

#include "interpreter/object.h"
#include "ast.h"

namespace Crimson {

NumLiteral::NumLiteral(double value)
    : m_value(value) 
{
}

double NumLiteral::value() const { return m_value; }

VarType NumLiteral::var_type() const { return m_var_type; }

NodeType NumLiteral::stmt_type() const { return m_node_kind; }

void NumLiteral::print_info() const {
    std::cout << "NumLiteral: " << m_value;
}

std::unique_ptr<Object> NumLiteral::accept(Interpreter& visitor) const {
    return visitor.visit_num_literal(*this);
}


BoolLiteral::BoolLiteral(bool value)
    : m_value(value) 
{
}

bool BoolLiteral::value() const { return m_value; }

VarType BoolLiteral::var_type() const { return m_var_type; }

NodeType BoolLiteral::stmt_type() const { return m_node_kind; }

void BoolLiteral::print_info() const {
    std::cout << "BoolLiteral: " << m_value;
}

std::unique_ptr<Object> BoolLiteral::accept(Interpreter& visitor) const {
    return visitor.visit_bool_literal(*this);
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

static VarType bool_var_type(VarType left_type, VarType right_type) {
    if ((left_type == VarType::Number) && (right_type == VarType::Number)) {
        return VarType::Bool;
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
    case TokenKind::Slash: {
        return numeric_var_type(left_type, right_type);
    }
    case TokenKind::Greater:
    case TokenKind::Less: {
        return bool_var_type(left_type, right_type);
    }
    }
}

std::unique_ptr<Object> BinaryExpr::accept(Interpreter& visitor) const {
    return visitor.visit_binary_expr(*this);
}

const Expr& BinaryExpr::left() const { return *m_left; }

const Expr& BinaryExpr::right() const { return *m_right; }

const Token& BinaryExpr::op() const { return m_op; }

VarDeclStmt::VarDeclStmt(Token ident, VarType var_type, bool is_const, std::unique_ptr<Expr> value)
    : m_ident(std::move(ident)), m_var_type(var_type), m_is_const(is_const), m_value(std::move(value))
{
}

const Expr& VarDeclStmt::value() const { return *m_value; }

VarType VarDeclStmt::var_type() const { return m_var_type; }

NodeType VarDeclStmt::stmt_type() const { return m_node_kind; }

void VarDeclStmt::print_info() const {
    std::cout << "VarDeclStmt: \n";
    std::cout << "\tIdent: " << m_ident.literal() << "\n";
    std::cout << "\tType: " << static_cast<std::underlying_type<VarType>::type>(m_var_type) << "\n";
    std::cout << "\tValue: \n";
    std::cout << "\tIsConst: " << m_is_const << "\n";
    m_value->print_info();
}

std::unique_ptr<Object> VarDeclStmt::accept(Interpreter& visitor) const {
    return visitor.visit_var_decl(*this);
}


const std::vector<std::unique_ptr<Stmt>>& Program::body() const { return m_body; }

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

std::unique_ptr<Object> Program::accept(Interpreter& visitor) const {
    return visitor.visit_program(*this);
}

} // Crimson
