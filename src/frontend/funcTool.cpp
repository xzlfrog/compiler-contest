#include "../include/frontend/funcTool.hpp"



dataType stringToDatatyoe(std::string returnDataTypeString){
    if(returnDataTypeString == "int") {
        return dataType::i32;
    } else if(returnDataTypeString == "float") {
        return dataType::f32;
    } else if(returnDataTypeString == "void") {
        return dataType::void_;
    } else if(returnDataTypeString == "bool") {
        return dataType::i1;
    } else {
        throw std::runtime_error("Unknown data type: " + returnDataTypeString);
    }
}

FuncDefination* create_func_def(std::string returnDataTypeString, std::string name, std::vector<Symbol*> params, LLVM* blocks) {
    
    dataType returnDataType = stringToDatatyoe(returnDataTypeString);
    FuncSymbol* func = SymbolFactory::createFuncSymbolWithScope(name, scope, returnDataType);
    FuncDefination* funcDef = LLVMfactory::createFuncDefination(func, params);
    llvmList->LLVM::InsertTail(funcDef);
    
    params.clear();
    
    return funcDef;
}

std::vector<BasicSymbol*> addToParams(BasicSymbol* param, std::vector<BasicSymbol*> params_table) {
    params_table.push_back(param);
    return params_table;
}

VarSymbol* create_param_nonarray(std::string paraType, std::sting name){
    VarSymbol* var = SymbolFactory::createVarSymbolWithScope(name, stringToDatatyoe(paraType), scope);
    return var;
}

ArraySymbol* create_param_array(std::string paraType, std::string name, std::vector<int> dimensions) {
    ArraySymbol* array = SymbolFactory::createArraySymbolWithScope(name, dimensions, scope, stringToDatatyoe(paraType));
    return array;
}