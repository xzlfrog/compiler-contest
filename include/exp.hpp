#pragma once
#include"sym.hpp"
#include"llvm.hpp"

class Expression{
public:
    Expression* next;//下一个expression
    LLVMList* llvmlist; //对应的llvm ir
    BasicSymbol* sym;//这个需要用中间变量来存储

    Expression(Expression* next,LLVMList*llvmlist,BasicSymbol*sym):
    next(next),llvmlist(llvmlist),sym(sym){}
    ;

    Expression(LLVMList*llvmlist,BasicSymbol*sym):
    llvmlist(llvmlist),sym(sym){}
    ;
};

