#pragma once
#include <vector>
#include "VM/value.h"
#include "Instructions/Instructions.h"

using namespace std;

struct ByteCode{
    vector<Value> constants;
    vector<int> code;

};