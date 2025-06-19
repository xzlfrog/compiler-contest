#pragma once

#include"llvm.hpp"
#include"function.hpp"

//src_ty src_sym->dest_ty dest_sym
class TypeConversionOperation:public LLVM{
public:
    BasicSymbol* src_sym;
    BasicSymbol* dest_sym;

    std::string out_str() const override;
    BasicSymbol* getSrcSymbol(){return this->src_sym;}
    BasicSymbol* getDestSymbol(){return this->dest_sym;}
    dataType getSrcType(){return this->src_sym->getDataType();}
    dataType getDestType(){return this->dest_sym->getDataType();}
};
