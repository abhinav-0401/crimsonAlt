#pragma once

#include "parser/ast.h"

namespace Crimson {

void typecheck_program(Program& program);
bool typecheck_stmt(Stmt& stmt);
bool typecheck_vardecl(VarDeclStmt& stmt);
void print_type_err(Stmt& stmt, std::string msg);
bool typecheck_expr(Expr& expr);

} // Crimson
