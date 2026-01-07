#include "VM/vm.h"

int main() {
    ByteCode chunk;
    chunk.constants = {10, 20};
    chunk.code = {
        OP_CONST, 0,
        OP_CONST, 1,
        OP_ADD,
        OP_PRINT,
        OP_HALT
    };

    VM vm { &chunk, {}, 0 };
    run(vm);
}