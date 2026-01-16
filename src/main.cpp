#include "VM/vm.h"
#include "Parser/Parser.h"

void compileToBC(const std::string&, const std::string&);

int main() {
    compileToBC("src/test/program.src", "src/test/program.bc");
    ByteCode chunk = Parser::parseFile("src/test/program.bc");

    VM vm { &chunk, {}, 0 };
    run(vm);
}

