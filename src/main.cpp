#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

#include "lexer/token.h"
#include "lexer/lexer.h"

int main() {
    std::cout << "This is blasphemy\n";

    // Crimson::Token token("hello there", Crimson::TokenKind::And);
    std::string src = "2 + 3";
    // std::string src = "let x : int = 123.34;";
    Crimson::Lexer lexer(std::move(src));

    const std::vector<Crimson::Token>& tokens = lexer.lex();

    for (const auto& token : tokens) {
        std::cout << "main token: " << token.literal() << " "
            << static_cast<std::underlying_type<Crimson::TokenKind>::type>(token.kind()) << "\n";
    }
}
