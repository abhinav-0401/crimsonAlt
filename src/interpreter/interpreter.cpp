#include <memory>

#include "object.h"
#include "interpreter.h"
#include "parser/ast.h"

namespace Crimson {

std::unique_ptr<Object> Interpreter::visit_num_literal(NumLiteral& num_lit) {
    return std::make_unique<NumObject>(num_lit.value());
}

std::unique_ptr<Object> Interpreter::visit_bool_literal(BoolLiteral& bool_lit) {
    return std::make_unique<BoolObject>(bool_lit.value());
}

std::unique_ptr<Object> Interpreter::visit_binary_expr(BinaryExpr& expr) {
    return std::make_unique<NumObject>(0);
}

std::unique_ptr<Object> Interpreter::visit_var_decl(VarDeclStmt& stmt) {
    return std::make_unique<NumObject>(2);
}

std::unique_ptr<Object> Interpreter::visit_program(Program& program) {
    const auto& program_body = program.body();
    std::unique_ptr<Object> last_eval;
    for (auto& stmt : program_body) {
        last_eval = stmt->accept(*this);
        last_eval->print_info();
    }
    return last_eval;
}

} // Crimson
