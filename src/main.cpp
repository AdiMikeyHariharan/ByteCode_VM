#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM/vm.h"

int main() {
    std::string source = R"(
    int x = 10;
    int y = 20;
)";
    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // (Optional) Debug tokens
    // for (const auto& t : tokens)
    //     std::cout << t.lexeme << " (" << t.line << ")\n
    Parser parser(tokens);
    auto ast = parser.parse();

    // 3 Compile AST → ByteCode
    Compiler compiler;
    ByteCode chunk = compiler.compile(ast);

    // 4️Execute
    VM vm{ &chunk, {}, 0 };
    run(vm);

    return 0;
}
