#include"../include/SymbolFactory.hpp"
#include<string>

int tmp_var_cnt;
int tmp_label_cnt;

std::string generate_tmp_var_name(){
    return std::to_string(tmp_var_cnt++);
}

std::string generate_tmp_label_name(){
    return "tmp_label."+std::to_string(tmp_label_cnt++);
}

VarSymbol* SymbolFactory::createVarSymbolWithScope(std::string name,int scope,Data*data){
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    if(scope>=0)
        varSymbol->setScope(scope);
    varSymbol->ssa_name=varSymbol->name;
    varSymbol->data=data;
    varSymbol->type=symType::variable;
    return varSymbol;
}

VarSymbol* SymbolFactory::createVarSymbolWithScope(std::string name,dataType type,int scope){
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    if(scope>=0)
        varSymbol->setScope(scope);
    varSymbol->ssa_name=varSymbol->name;
    varSymbol->data=createInitialedData(type);
    varSymbol->type=symType::variable;
    return varSymbol;
}

ConstVarSymbol* SymbolFactory::createConstVarSymbolWithScope(std::string name,int scope,Data* data){
    ConstVarSymbol *constVarSymbol=new ConstVarSymbol();
    constVarSymbol->name=name;
    if(scope>=0)
        constVarSymbol->setScope(scope);
    constVarSymbol->ssa_name=constVarSymbol->name;
    constVarSymbol->data=data;
    constVarSymbol->type=symType::constant_var;
    return constVarSymbol;
}

VarSymbol* SymbolFactory::createTmpVarSymbolWithScope(dataType type,int scope){
    std::string name=generate_tmp_var_name();
    VarSymbol *varSymbol=new VarSymbol();
    varSymbol->name=name;
    if(scope>=0)
        varSymbol->setScope(scope);
    varSymbol->ssa_name=varSymbol->name;
    varSymbol->data=createNonInitialedData(type);
    varSymbol->type=symType::variable;
    return varSymbol;
}

ConstSymbol* SymbolFactory::createConstSymbolWithScope(Data*data,int scope){
    ConstSymbol* constSymbol=new ConstSymbol();
    if(scope>=0)
        constSymbol->setScope(scope);
    constSymbol->data=data;
    constSymbol->type=symType::constant_nonvar;
    return constSymbol;
}

PointerSymbol* SymbolFactory::createPointerSymbolWithScope(std::string name,int scope,dataType pointedType){
    PointerSymbol* pointerSymbol=new PointerSymbol();
    pointerSymbol->name=name;
    if(scope>=0)
        pointerSymbol->setScope(scope);
    pointerSymbol->allocateMemory(pointedType);
    pointerSymbol->pointedData->setInitMode(initializer::assignment);
    pointerSymbol->type=symType::pointer;
    return pointerSymbol;
}

ArraySymbol* SymbolFactory::createArraySymbolWithScope(std::string name,int scope,dataType type){
    ArraySymbol* arraySymbol=new ArraySymbol();
    arraySymbol->name=name;
    if(scope>=0)
        arraySymbol->setScope(scope);
    std::vector<int> dim=std::vector<int>(0);
    arraySymbol->allocateMemory(type,dim);
    arraySymbol->type=symType::array;
    return arraySymbol;
}

ArraySymbol* SymbolFactory::createArraySymbolWithScope(std::string name,std::vector<int>&dimensions,int scope,dataType type){
    ArraySymbol* arraySymbol=new ArraySymbol();
    arraySymbol->name=name;
    if(scope>=0)
        arraySymbol->setScope(scope);
    arraySymbol->type=symType::array;
    arraySymbol->allocateMemory(type,dimensions);
    return arraySymbol;
}

LabelSymbol* SymbolFactory::createLabelSymbolWithScope(std::string name,int scope){
    LabelSymbol* labelSymbol=new LabelSymbol();
    labelSymbol->name="label."+name;
    if(scope>=0)
        labelSymbol->setScope(scope);
    labelSymbol->type=symType::sym_label;
    return labelSymbol;
}

LabelSymbol* SymbolFactory::createTmpLabelSymbolWithScope(int scope){
    std::string name=generate_tmp_label_name();
    return SymbolFactory::createLabelSymbolWithScope(name,scope);
}

FuncSymbol* SymbolFactory::createFuncSymbolWithScope(std::string name,std::vector<dataType>& paramTypes,int scope,dataType returnType){
    FuncSymbol* funcSymbol=new FuncSymbol();
    funcSymbol->name="func."+name;
    if(scope>=0)
        funcSymbol->setScope(scope);
    funcSymbol->paramTypes=paramTypes;
    funcSymbol->returnType=returnType;
    funcSymbol->type=symType::function;
    return funcSymbol;
}

FuncSymbol* SymbolFactory::createFuncSymbolWithScope(std::string name,int scope,dataType returnType){
    FuncSymbol* funcSymbol=new FuncSymbol();
    std::vector<dataType> paramTypes=std::vector<dataType>(0);
    funcSymbol->name="func."+name;
    if(scope>=0)
        funcSymbol->setScope(scope);
    funcSymbol->paramTypes=paramTypes;
    funcSymbol->type=symType::function;
    funcSymbol->returnType=returnType;
    return funcSymbol;
}

//----------------------------------------------------

VarSymbol* SymbolFactory::createVarSymbol(std::string name,Data*data){
    return SymbolFactory::createVarSymbolWithScope(name,-1,data);
}

VarSymbol* SymbolFactory::createVarSymbol(std::string name,dataType type){
    return SymbolFactory::createVarSymbolWithScope(name,type,-1);
}

ConstVarSymbol* SymbolFactory::createConstVarSymbol(std::string name,Data* data){
    return SymbolFactory::createConstVarSymbolWithScope(name,-1,data);
}

VarSymbol* SymbolFactory::createTmpVarSymbol(dataType type){
    return SymbolFactory::createTmpVarSymbolWithScope(type,-1);
}

ConstSymbol* SymbolFactory::createConstSymbol(Data*data){
    return SymbolFactory::createConstSymbolWithScope(data,-1);
}

PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,dataType pointedType){
    return createPointerSymbolWithScope(name,-1,pointedType);
}

ArraySymbol* SymbolFactory::createArraySymbol(std::string name,dataType type){
    return SymbolFactory::createArraySymbolWithScope(name,-1,type);
}

ArraySymbol* SymbolFactory::createArraySymbol(std::string name,std::vector<int>&dimensions,dataType type){
    return SymbolFactory::createArraySymbolWithScope(name,dimensions,-1,type);
}

LabelSymbol* SymbolFactory::createLabelSymbol(std::string name){
    return SymbolFactory::createLabelSymbolWithScope(name,-1);
}

LabelSymbol* SymbolFactory::createTmpLabelSymbol(){
    std::string name=generate_tmp_label_name();
    return SymbolFactory::createLabelSymbolWithScope(name,-1);
}

FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,std::vector<dataType>& paramTypes,dataType returnType){
    return SymbolFactory::createFuncSymbolWithScope(name,paramTypes,-1,returnType);
}

FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,dataType returnType){
    return SymbolFactory::createFuncSymbolWithScope(name,-1,returnType);
}