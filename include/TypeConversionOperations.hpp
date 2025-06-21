#pragma once

#include"llvm.hpp"
#include"function.hpp"

//src_ty src_sym->dest_ty dest_sym
class TypeConversionOperation:public LLVM{
public:
    BasicSymbol* src_sym;
    BasicSymbol* dest_sym;

    std::string out_str() const override;
    BasicSymbol* getSrcSymbol();
    BasicSymbol* getDestSymbol();
    dataType getSrcType();
    dataType getDestType();
};