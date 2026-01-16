#include "VM/vm.h"
#include "Parser/Parser.h"
int main() {
    ByteCode chunk = Parser::parseFile("src/test/program.bc");

    VM vm { &chunk, {}, 0 };
    run(vm);
}