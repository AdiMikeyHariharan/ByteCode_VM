#pragma once
#include "ByteCode/ByteCode.h"
#include <stack>

using namespace std;

struct VM{
    ByteCode* chunk;
    stack<Value> S;
    int ip;
};

void run(VM &vm);