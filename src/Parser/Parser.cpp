#include "Parser.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

ByteCode Parser::parseFile(const std::string& path) {
    std::ifstream file(path);
    std::string line;

    ByteCode chunk;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string instr;
        ss >> instr;

        if (instr == "CONST") {
            double value;
            ss >> value;

            chunk.constants.push_back(value);
            chunk.code.push_back(OP_CONST);
            chunk.code.push_back(chunk.constants.size() - 1);
        }
        else if (instr == "DIV") {
            chunk.code.push_back(OP_DIV);
        }
        else if (instr == "ADD") {
            chunk.code.push_back(OP_ADD);
        }
        else if (instr == "MUL") {
            chunk.code.push_back(OP_MUL);
        }
        else if (instr == "SUB") {
            chunk.code.push_back(OP_SUB);
        }
        else if (instr == "PRINT") {
            chunk.code.push_back(OP_PRINT);
        }
        else if (instr == "HALT") {
            chunk.code.push_back(OP_HALT);
        }
    }

    return chunk;
}
