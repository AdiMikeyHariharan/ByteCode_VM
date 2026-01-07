#pragma once
#include "ByteCode/ByteCode.h"
#include <stack>

using namespace std;

struct VM{
    ByteCode* chunk;
    stack<int> S;
    int ip;
};

void run(VM &vm);