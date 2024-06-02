#include <iostream>

#include "typechecker.h"
#include "parser/ast.h"

namespace Crimson {

void typecheck_program(const Program& program) {
    for (const std::unique_ptr<Stmt>& stmt : program.body()) {
        if (!typecheck_stmt(*stmt)) {
            print_type_err(*stmt, "Invalid types\n");
            break;
        }
    }
}

bool typecheck_stmt(const Stmt& stmt) {
    switch (stmt.stmt_type()) {
    case NodeType::VarDeclStmt: {
        return typecheck_vardecl(dynamic_cast<const VarDeclStmt&>(stmt));
    }
    }
}

bool typecheck_vardecl(const VarDeclStmt& stmt) {
    if (stmt.var_type() == stmt.value().var_type()) {
        return true;
    }
    return false;
}

void print_type_err(const Stmt& stmt, std::string msg) {
    std::cout << msg;
}

} // Crimson
