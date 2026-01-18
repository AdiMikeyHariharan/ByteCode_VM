// #include "VM/vm.h"
// #include "Parser/Parser.h"

// void compileToBC(const std::string&, const std::string&);

// int main() {
//     compileToBC("src/test/program.src", "src/test/program.bc");
//     ByteCode chunk = Parser::parseFile("src/test/program.bc");

//     VM vm { &chunk, {}, 0 };
//     run(vm);
// }

#include "Lexer.h"
#include <iostream>

int main() {
    std::string source = R"(
int add(int a, int b) {
    int result = a + b;
    return result;
}

int main() {
    int x = 10;
    int y = 20;
    int z = add(x, y);

    if (z > 20) {
        print(z);
    } else {
        print(0);
    }

    while (x < y) {
        x = x + 1;
    }

    return 0;
}
)";

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << token.lexeme << "  (line " << token.line << ")\n";
    }
}
