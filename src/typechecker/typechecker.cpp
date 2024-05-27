#include <iostream>

#include "typechecker.h"
#include "parser/ast.h"

namespace Crimson {

void typecheck_program(Program& program) {
    for (std::unique_ptr<Stmt>& stmt : program.body()) {
        if (!typecheck_stmt(*stmt)) {
            print_type_err(*stmt, "Invalid types\n");
            break;
        }
    }
}

bool typecheck_stmt(Stmt& stmt) {
    switch (stmt.stmt_type()) {
    case NodeType::VarDeclStmt: {
        return typecheck_vardecl(dynamic_cast<VarDeclStmt&>(stmt));
    }
    }
}

bool typecheck_vardecl(VarDeclStmt& stmt) {
    if (stmt.var_type() == stmt.value().var_type()) {
        return true;
    }
    return false;
}

void print_type_err(Stmt& stmt, std::string msg) {
    std::cout << msg;
}

} // Crimson
