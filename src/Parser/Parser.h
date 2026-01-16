#pragma once
#include <string>
#include "ByteCode/ByteCode.h"

class Parser {
public:
    static ByteCode parseFile(const std::string& path);
};
