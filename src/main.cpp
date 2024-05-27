#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

#include "lexer/token.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "typechecker/typechecker.h"

int main() {
    std::cout << "This is blasphemy\n";

    // std::string src = "var x : int = (5 + 3) < (3 * 3);";
    std::string src = "var x : int = 3 + 3;";
    Crimson::Lexer lexer(std::move(src));

    // const std::vector<Crimson::Token>& tokens = lexer.lex();
    const std::vector<Crimson::Token>& tokens = lexer.lex();
    Crimson::Parser parser(lexer.tokens());

    for (const auto& token : tokens) {
        std::cout << "main token: " << token.literal() << " "
            << static_cast<std::underlying_type<Crimson::TokenKind>::type>(token.kind()) << "\n";
    }
    parser.parse();
    parser.print_program();

    Crimson::typecheck_program(parser.program());
}
