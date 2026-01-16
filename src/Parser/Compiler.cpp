#include <fstream>
#include <sstream>
#include "Instructions/Instructions.h"

void compileToBC(const std::string& src, const std::string& out) {
    std::ifstream in(src);
    std::ofstream bc(out);

    std::string word;
    in >> word;  // print

    double lhs, rhs;
    char op;

    in >> lhs >> op >> rhs;

    bc << "CONST " << lhs << "\n";
    bc << "CONST " << rhs << "\n";

    switch (op) {
        case '+': bc << "ADD\n"; break;
        case '-': bc << "SUB\n"; break;
        case '*': bc << "MUL\n"; break;
        case '/': bc << "DIV\n"; break;
    }

    bc << "PRINT\n";
    bc << "HALT\n";
}
