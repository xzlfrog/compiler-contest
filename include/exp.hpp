#pragma once
#include"sym.hpp"
#include"llvm.hpp"

class Expression{
public:
    Expression* next;//下一个expression
    LLVM* llvm; //对应的llvm ir
    Symbol* sym;//这个需要用中间变量来存储

    Expression(Expression* next,LLVM*llvm,Symbol*sym):
    next(next),llvm(llvm),sym(sym){}
    ;
};

