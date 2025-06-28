#pragma once

#include"sym.hpp"

std::string generate_tmp_var_name();
std::string generate_tmp_label_name();

class SymbolFactory{
public:
    static VarSymbol* createVarSymbol(std::string name,Data*data=nullptr);

    static ConstVarSymbol* createConstVarSymbol(std::string name,Data* data=nullptr);

    static VarSymbol* createTmpVarSymbol(dataType type);

    static ConstSymbol* createConstSymbol(Data*data=nullptr);

    static PointerSymbol* createPointerSymbol(std::string name,
        dataType pointedType=dataType::data_undefined);

    static PointerSymbol* createPointerSymbol(std::string name,ValueVariant value,
        dataType pointedType=dataType::data_undefined);

    static ArraySymbol* createArraySymbol(std::string name,
        dataType type=dataType::data_undefined);
        
    static ArraySymbol* createArraySymbol(std::string name,
        std::vector<int>&dimensions,dataType type=dataType::data_undefined);

    static LabelSymbol* createLabelSymbol(std::string name);

    static LabelSymbol* createTmpLabelSymbol();

    static FuncSymbol* createFuncSymbol(std::string name,
        std::vector<dataType>& paramTypes,dataType returnType=dataType::data_undefined);

    static FuncSymbol* createFuncSymbol(std::string name,
        dataType returnType=dataType::data_undefined);
};