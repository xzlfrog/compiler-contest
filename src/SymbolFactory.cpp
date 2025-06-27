#include"../include/SymbolFactory.hpp"
#include<string>

extern int tmp_var_cnt;
extern int tmp_label_cnt;

std::string generate_tmp_var_name(){
    return std::to_string(tmp_var_cnt++);
}

std::string generate_tmp_label_name(){
    return "label."+std::to_string(tmp_label_cnt++);
}

VarSymbol* SymbolFactory::createVarSymbol(std::string name,Data*data=nullptr){
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    varSymbol->data=data;
    return varSymbol;
}

ConstVarSymbol* SymbolFactory::createConstVarSymbol(std::string name,Data* data=nullptr){
    ConstVarSymbol *constVarSymbol=new ConstVarSymbol();
    constVarSymbol->name=name;
    constVarSymbol->data=data;
    return constVarSymbol;
}

VarSymbol* SymbolFactory::createTmpVarSymbol(Data*data=nullptr){
    std::string name=generate_tmp_var_name();
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    varSymbol->data=data;
    return varSymbol;
}

ConstSymbol* SymbolFactory::createConstSymbol(Data*data=nullptr){
    ConstSymbol* constSymbol=new ConstSymbol();
    constSymbol->data=data;
    return constSymbol;
}

PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,dataType pointedType=dataType::data_undefined){
    PointerSymbol* pointerSymbol=new PointerSymbol();
    pointerSymbol->name=name;
    pointerSymbol->allocateMemory(pointedType,0);
    return pointerSymbol;
}

PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,ValueVariant value,dataType pointedType=dataType::data_undefined){
    PointerSymbol* pointerSymbol=new PointerSymbol();
    pointerSymbol->name=name;
    pointerSymbol->allocateMemory(pointedType,value);
    return pointerSymbol;
}

ArraySymbol* SymbolFactory::createArraySymbol(std::string name,dataType type=dataType::data_undefined){
    ArraySymbol* arraySymbol=new ArraySymbol();
    arraySymbol->name=name;
    std::vector<int> dim=std::vector<int>(0);
    arraySymbol->allocateMemory(type,dim);
    return arraySymbol;
}

ArraySymbol* SymbolFactory::createArraySymbol(std::string name,std::vector<int>&dimensions,dataType type=dataType::data_undefined){
    ArraySymbol* arraySymbol=new ArraySymbol();
    arraySymbol->name=name;
    arraySymbol->allocateMemory(type,dimensions);
    return arraySymbol;
}

LabelSymbol* SymbolFactory::createLabelSymbol(std::string name){
    LabelSymbol* labelSymbol=new LabelSymbol();
    labelSymbol->name=name;
    return labelSymbol;
}

LabelSymbol* SymbolFactory::createTmpLabelSymbol(){
    std::string name=generate_tmp_label_name();
    return SymbolFactory::createLabelSymbol(name);
}

FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,std::vector<dataType>& paramTypes,dataType returnType=dataType::data_undefined){
    FuncSymbol* funcSymbol=new FuncSymbol();
    funcSymbol->name=name;
    funcSymbol->paramTypes=paramTypes;
    funcSymbol->returnType=returnType;
    return funcSymbol;
}

FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,dataType returnType=dataType::data_undefined){
    FuncSymbol* funcSymbol=new FuncSymbol();
    std::vector<dataType> paramTypes=std::vector<dataType>(0);
    funcSymbol->name=name;
    funcSymbol->paramTypes=paramTypes;
    funcSymbol->returnType=returnType;
    return funcSymbol;
}