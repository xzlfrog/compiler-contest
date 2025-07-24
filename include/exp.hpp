#pragma once
#include"sym.hpp"
#include"llvm.hpp"

class Expression{
public:
    Expression* next=nullptr;//下一个expression
    LLVMList* llvmlist; //对应的llvm ir
    Symbol* sym;//这个需要用中间变量来存储

    Expression(Expression* next,LLVMList*llvmlist,Symbol*sym):
    next(next),llvmlist(llvmlist),sym(sym){}
    ;

    Expression(LLVMList*llvmlist,Symbol*sym):
    llvmlist(llvmlist),sym(sym){this->next=nullptr;}
    ;
};

