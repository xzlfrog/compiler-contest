#include"../include/SymbolFactory.hpp"
#include<string>

int tmp_var_cnt;
int tmp_label_cnt;

std::string generate_tmp_var_name(){
    return std::to_string(tmp_var_cnt++);
}

std::string generate_tmp_label_name(){
    return "label."+std::to_string(tmp_label_cnt++);
}

VarSymbol* SymbolFactory::createVarSymbol(std::string name,Data*data){
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    varSymbol->data=data;
    return varSymbol;
}

ConstVarSymbol* SymbolFactory::createConstVarSymbol(std::string name,Data* data){
    ConstVarSymbol *constVarSymbol=new ConstVarSymbol();
    constVarSymbol->name=name;
    constVarSymbol->data=data;
    return constVarSymbol;
}

VarSymbol* SymbolFactory::createTmpVarSymbol(dataType type){
    std::string name=generate_tmp_var_name();
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    varSymbol->data=createNonInitialedData(type);
    return varSymbol;
}

ConstSymbol* SymbolFactory::createConstSymbol(Data*data){
    ConstSymbol* constSymbol=new ConstSymbol();
    constSymbol->data=data;
    return constSymbol;
}

PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,dataType pointedType){
    PointerSymbol* pointerSymbol=new PointerSymbol();
    pointerSymbol->name=name;
    pointerSymbol->allocateMemory(pointedType,0);
    return pointerSymbol;
}

PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,ValueVariant value,dataType pointedType){
    PointerSymbol* pointerSymbol=new PointerSymbol();
    pointerSymbol->name=name;
    pointerSymbol->allocateMemory(pointedType,value);
    return pointerSymbol;
}

ArraySymbol* SymbolFactory::createArraySymbol(std::string name,dataType type){
    ArraySymbol* arraySymbol=new ArraySymbol();
    arraySymbol->name=name;
    std::vector<int> dim=std::vector<int>(0);
    arraySymbol->allocateMemory(type,dim);
    return arraySymbol;
}

ArraySymbol* SymbolFactory::createArraySymbol(std::string name,std::vector<int>&dimensions,dataType type){
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

FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,std::vector<dataType>& paramTypes,dataType returnType){
    FuncSymbol* funcSymbol=new FuncSymbol();
    funcSymbol->name=name;
    funcSymbol->paramTypes=paramTypes;
    funcSymbol->returnType=returnType;
    return funcSymbol;
}

FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,dataType returnType){
    FuncSymbol* funcSymbol=new FuncSymbol();
    std::vector<dataType> paramTypes=std::vector<dataType>(0);
    funcSymbol->name=name;
    funcSymbol->paramTypes=paramTypes;
    funcSymbol->returnType=returnType;
    return funcSymbol;
}