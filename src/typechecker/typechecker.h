#pragma once

#include "parser/ast.h"

namespace Crimson {

void typecheck_program(const Program& program);
bool typecheck_stmt(const Stmt& stmt);
bool typecheck_vardecl(const VarDeclStmt& stmt);
void print_type_err(const Stmt& stmt, std::string msg);
bool typecheck_expr(const Expr& expr);

} // Crimson
