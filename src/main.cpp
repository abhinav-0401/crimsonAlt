#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

#include "lexer/token.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    std::cout << "This is blasphemy\n";

    std::string src = "23";
    Crimson::Lexer lexer(std::move(src));

    // const std::vector<Crimson::Token>& tokens = lexer.lex();
    lexer.lex();
    Crimson::Parser parser(lexer.tokens());
    parser.parse();
    parser.print_program();

    // for (const auto& token : tokens) {
    //     std::cout << "main token: " << token.literal() << " "
    //         << static_cast<std::underlying_type<Crimson::TokenKind>::type>(token.kind()) << "\n";
    // }
}
