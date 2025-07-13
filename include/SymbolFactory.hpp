#pragma once

#include"sym.hpp"

std::string generate_tmp_var_name();
std::string generate_tmp_label_name();
std::string addScopeToName(std::string name);

extern int scope;
extern std::vector<std::unordered_map<std::string,int>> variable_rename_table;

class SymbolFactory{
public:
    static VarSymbol* createVarSymbolWithScope(std::string name,int scope=-1,Data*data=nullptr);

    static VarSymbol* createVarSymbolWithScope(std::string name,dataType type,int scope=-1);

    static ConstVarSymbol* createConstVarSymbolWithScope(std::string name,int scope=-1,Data* data=nullptr);

    static VarSymbol* createTmpVarSymbolWithScope(dataType type,int scope=-1);

    static ConstSymbol* createConstSymbolWithScope(Data*data=nullptr,int scope=-1);

    static PointerSymbol* createPointerSymbolWithScope(std::string name,int scope=-1,
        dataType pointedType=dataType::data_undefined);

    static ArraySymbol* createArraySymbolWithScope(std::string name,int scope=-1,
        dataType type=dataType::data_undefined);
        
    static ArraySymbol* createArraySymbolWithScope(std::string name,
        std::vector<int>&dimensions,int scope=-1,dataType type=dataType::data_undefined);

    static LabelSymbol* createLabelSymbolWithScope(std::string name,int scope=-1);

    static LabelSymbol* createTmpLabelSymbolWithScope(int scope=-1);

    static FuncSymbol* createFuncSymbolWithScope(std::string name,
        std::vector<dataType>& paramTypes,int scope=-1,dataType returnType=dataType::data_undefined);

    static FuncSymbol* createFuncSymbolWithScope(std::string name,int scope=-1,
        dataType returnType=dataType::data_undefined);

    static VarSymbol* createVarSymbol(std::string name,Data*data=nullptr);

    static VarSymbol* createVarSymbol(std::string name,dataType type);

    static ConstVarSymbol* createConstVarSymbol(std::string name,Data* data=nullptr);

    static VarSymbol* createTmpVarSymbol(dataType type);

    static ConstSymbol* createConstSymbol(Data*data=nullptr);

    static PointerSymbol* createPointerSymbol(std::string name,
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

    static PointerSymbol* createTmpPointerSymbolWithScope(dataType type,int scope);
};