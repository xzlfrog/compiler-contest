#include"../include/BasicOperations.hpp"
#include"../include/LLVMFactory.hpp"
#include<iostream>

int main(){
    BasicSymbol* a=SymbolFactory::createTmpVarSymbol(dataType::i32);
    BasicSymbol* b=SymbolFactory::createConstSymbol(createData(dataType::i32,1));
    BasicSymbol* c=SymbolFactory::createConstSymbol(createData(dataType::i32,1));
    ArithmeticOperationLLVM* bsollvm=LLVMfactory::createBasicOperationLLVM(LLVMtype::add,a,b,c);
    std::cout<<bsollvm->out_str()<<std::endl;
}