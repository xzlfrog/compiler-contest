#include"../include/BasicOperations.hpp"
#include"../include/LLVMFactory.hpp"
#include"../include/data.hpp"
#include<iostream>

int main(){
    BasicSymbol* a=SymbolFactory::createVarSymbol("a",dataType::f32);
    a->setScope(1);
    BasicSymbol* b=SymbolFactory::createConstVarSymbol("b",createData(dataType::f32,3.0f));
    BasicSymbol* c=SymbolFactory::createConstSymbol(createData(dataType::f32,1.0f));

    ArithmeticOperationLLVM* bsollvm=LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_fadd,a,b,c);
    std::cout<<bsollvm->out_str()<<std::endl;
}