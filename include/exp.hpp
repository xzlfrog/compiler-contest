#pragma once
#include"sym.hpp"
#include"llvm.hpp"

class Expression{
public:
    Expression* next;
    LLVM* llvm; 
    Symbol* sym;

    Expression(Expression* next,LLVM*llvm,Symbol*sym):
    next(next),llvm(llvm),sym(sym){}
    ;
};

