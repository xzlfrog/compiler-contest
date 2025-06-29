#include"../include/BasicOperations.hpp"
#include"../include/LLVMFactory.hpp"
#include"../include/data.hpp"
#include<iostream>

int main(){
    BasicSymbol* a=SymbolFactory::createTmpVarSymbol(dataType::i32);
    std::cout<<a->getType()<<std::endl;
    BasicSymbol* b=SymbolFactory::createConstSymbol(createData(dataType::i32,1));
    std::cout<<b->getType()<<std::endl;
    BasicSymbol* c=SymbolFactory::createConstSymbol(createData(dataType::i32,1));
    std::cout<<c->getType()<<std::endl;
    ArithmeticOperationLLVM* bsollvm=LLVMfactory::createBasicOperationLLVM(LLVMtype::add,a,b,c);
    std::cout<<bsollvm->out_str()<<std::endl;
}