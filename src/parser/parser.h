#pragma once

#include <vector>
#include <memory>

#include "using.h"
#include "lexer/token.h"
#include "parser/ast.h"

namespace Crimson {

class Parser {
public:
    Parser(std::vector<Token>&& tokens);
    void parse();
    void print_program();
private:
    std::unique_ptr<Stmt> parse_stmt();
    bool not_eof();
    const Token& at();
    const Token& advance();

    std::vector<Token> m_tokens;
    std::unique_ptr<Program> m_program;
    size_t m_curr;
};

} // Crimson
