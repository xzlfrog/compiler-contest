#pragma once

#include"sym.hpp"

class SymbolFactory{
public:
    static BasicSymbol* createBasicSymbol(std::string name,symType type=symType::sym_undefined,Data*data=nullptr);
    static BasicSymbol* createTmpBasicSymbol(symType type=symType::sym_undefined,Data*data=nullptr);
    static PointerSymbol* createPointerSymbol(std::string name,dataType pointedType=dataType::data_undefined);
    static PointerSymbol* createPointerSymbol(std::string name,ValueVariant value,dataType pointedType=dataType::data_undefined);
    static ArraySymbol* createArraySymbol(std::string name,dataType type=dataType::data_undefined);
    static ArraySymbol* createArraySymbol(std::string name,std::vector<int>&dimensions,dataType type=dataType::data_undefined);
    static LabelSymbol* createLabelSymbol(std::string name);
    static LabelSymbol* createTmpLabelSymbol();
    static FuncSymbol* createFuncSymbol(std::string name,std::vector<dataType>& paramTypes,dataType returnType=dataType::data_undefined);
    static FuncSymbol* createFuncSymbol(std::string name,dataType returnType=dataType::data_undefined);
};
