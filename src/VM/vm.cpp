#include "vm.h"
#include <iostream>


using namespace std;

void run(VM &vm){
    while(true){
      int ins = vm.chunk->code[vm.ip++];
      
      switch(ins){
        case OP_CONST: {
            int index = vm.chunk->code[vm.ip++];
            vm.S.push(vm.chunk->constants[index]);
            break;
        }
        case OP_ADD: {
            Value b = vm.S.top();
            vm.S.pop();
            Value a = vm.S.top();
            vm.S.pop();
            Value result = std::visit([](auto x, auto y) -> Value {
                return x + y;
            },a , b);
            vm.S.push(result);
            break;
        }
        case OP_SUB: {
            Value b = vm.S.top();
            vm.S.pop();
            Value a = vm.S.top();
            vm.S.pop();
            Value result = std::visit([](auto x, auto y) -> Value {
                return x - y;
            },a , b);
            vm.S.push(result);
            break;
        }
        case OP_MUL: {
            Value b = vm.S.top();
            vm.S.pop();
            Value a = vm.S.top();
            vm.S.pop();
            Value result = std::visit([](auto x, auto y) -> Value {
                return x * y;
            },a , b);
            vm.S.push(result);
            break;
        }
        case OP_DIV: {
            Value b = vm.S.top();
            vm.S.pop();
            Value a = vm.S.top();
            vm.S.pop();
            Value result = std::visit([](auto x, auto y) -> Value {
                return x / y;
            },a , b);
            vm.S.push(result);
            break;
        }
        case OP_PRINT: {
            std::visit([](auto x){
                std::cout<<x<<endl;
            },vm.S.top());
            break;
        }
        case OP_HALT:
            return;
      }    
    }
}