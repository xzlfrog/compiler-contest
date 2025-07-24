#pragma once

#include"llvm.hpp"
#include"function.hpp"

//src_ty src_sym->dest_ty dest_sym
class TypeConversionOperation:public LLVM{
public:
    BasicSymbol* src_sym;
    BasicSymbol* dest_sym;

    std::string out_str() const override;
    void out_arm_str() override;
    BasicSymbol* getSrcSymbol();
    BasicSymbol* getDestSymbol();
    dataType getSrcType();
    dataType getDestType();
    ~TypeConversionOperation()=default;
};