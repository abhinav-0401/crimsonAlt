#include <memory>

#include "object.h"
#include "interpreter.h"
#include "parser/ast.h"
#include "lexer/token.h"

namespace Crimson {

std::unique_ptr<Object> Interpreter::visit_num_literal(const NumLiteral& num_lit) {
    return std::make_unique<NumObject>(num_lit.value());
}

std::unique_ptr<Object> Interpreter::visit_bool_literal(const BoolLiteral& bool_lit) {
    return std::make_unique<BoolObject>(bool_lit.value());
}

std::unique_ptr<Object> Interpreter::visit_binary_expr(const BinaryExpr& expr) {
    auto left_val = expr.left().accept(*this);
    auto right_val = expr.right().accept(*this);

    switch (expr.op().kind()) {
    case TokenKind::Plus: {
        auto left_num_val = dynamic_cast<NumObject&>(*left_val);
        auto right_num_val = dynamic_cast<NumObject&>(*right_val);
        return std::make_unique<NumObject>(left_num_val.value() + right_num_val.value());
    }
    case TokenKind::Minus: {
        auto left_num_val = dynamic_cast<NumObject&>(*left_val);
        auto right_num_val = dynamic_cast<NumObject&>(*right_val);
        return std::make_unique<NumObject>(left_num_val.value() - right_num_val.value());
    }
    case TokenKind::Star: {
        auto left_num_val = dynamic_cast<NumObject&>(*left_val);
        auto right_num_val = dynamic_cast<NumObject&>(*right_val);
        return std::make_unique<NumObject>(left_num_val.value() * right_num_val.value());
    }
    case TokenKind::Slash: {
        auto left_num_val = dynamic_cast<NumObject&>(*left_val);
        auto right_num_val = dynamic_cast<NumObject&>(*right_val);
        return std::make_unique<NumObject>(left_num_val.value() / right_num_val.value());
    }
    }

    return std::make_unique<NumObject>(0);
}

std::unique_ptr<Object> Interpreter::visit_var_decl(const VarDeclStmt& stmt) {
    auto val = stmt.value().accept(*this);
    return val;
}

std::unique_ptr<Object> Interpreter::visit_program(const Program& program) {
    const auto& program_body = program.body();
    std::unique_ptr<Object> last_eval;
    for (auto& stmt : program_body) {
        last_eval = stmt->accept(*this);
        last_eval->print_info();
    }
    return last_eval;
}

} // Crimson
