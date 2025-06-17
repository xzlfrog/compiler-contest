#include"sym.hpp"
#include"llvm.hpp"

class Expression{
public:
    Expression* next;
    LLVM* llvm; 
    Symbol* sym;
};