#pragma once

#include <memory>

#include "parser/ast.h"
#include "object.h"

namespace Crimson {

class NumLiteral;
class BoolLiteral;
class BinaryExpr;
class VarDeclStmt;
class Program;

class Interpreter {
public:
    Interpreter() = default;
    std::unique_ptr<Object> visit_num_literal(const NumLiteral& num_lit);
    std::unique_ptr<Object> visit_bool_literal(const BoolLiteral& bool_lit);
    std::unique_ptr<Object> visit_binary_expr(const BinaryExpr& binary_expr);
    std::unique_ptr<Object> visit_var_decl(const VarDeclStmt& var_decl);
    std::unique_ptr<Object> visit_program(const Program& prorgam);
};

} // Crimson
