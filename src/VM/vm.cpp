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
            int b = vm.S.top();
            vm.S.pop();
            int a = vm.S.top();
            vm.S.pop();
            vm.S.push(a+b);
            break;
        }
        case OP_PRINT: {
            cout<<vm.S.top()<<endl;
            break;
        }
        case OP_HALT:
            return;
      }    
    }
}