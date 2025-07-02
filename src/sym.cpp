#include"../include/sym.hpp"
#include<iostream>

//PointerSymbol
symType PointerSymbol::getType() {this->type=symType::pointer;return this->type;}
dataType PointerSymbol::getPointedType() const {return this->PointedType;}
void PointerSymbol::allocateMemory(dataType elementType){
    this->PointedType = elementType;
    Data_pointer* data_pointer = new Data_pointer();
    Data* data=createNonInitialedData(elementType);
    this->data=new Data_pointer();
    this->data->setValue(data);
    this->pointedData=std::get<Data*>(this->data->getValue());
}
void PointerSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//BasicSymbol
symType BasicSymbol::getType() {return this->type;}
dataType BasicSymbol::getDataType()const{return this->data->getType();}
void BasicSymbol::setData(dataType dtype,ValueVariant v){this->data=createData(dtype,v);}

void BasicSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//ArraySymbol
symType ArraySymbol::getType(){this->type=symType::array; return this->type;}
void ArraySymbol::allocateMemory(dataType type,std::vector<int>&dims){
    this->arrayType=type;
    this->dimensions=dims;
}

const std::vector<int>&ArraySymbol::getDimensions()const{return this->dimensions;}
dataType ArraySymbol::getArrayType()const{return this->arrayType;}

const std::vector<std::pair<std::vector<int>,Data*>>& ArraySymbol::getInitializedData(){
    if(this->isInitialed==false){
        std::vector<std::pair<std::vector<int>,Data*>>ret;
        return ret;
    }
    return this->initialedData->getInitializedData();
}

void ArraySymbol::setInitialedData(ArrayInitial* arrayInitial){
    this->initialedData=arrayInitial;
    for(auto a:arrayInitial->getInitializedData()){
        for(int i=0;i<a.first.size();i++){
            if(a.first[i]>=this->dimensions[i])
                throw std::runtime_error("the index is out of the range of the array");
        }
    }
}

void ArraySymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//LabelSymbol
symType LabelSymbol::getType(){this->type=symType::sym_label; return this->type;}
void LabelSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//FuncSymbol
symType FuncSymbol::getType() {this->type=symType::function; return this->type;}
const std::vector<dataType>& FuncSymbol::getParamTypes()const{return this->paramTypes;}
dataType FuncSymbol::getReturnType()const{return this->returnType;}

void FuncSymbol::addParams(std::vector<dataType>& paramTypes){
    for(auto paramType: paramTypes){
        this->addParam(paramType);
    }
}
void FuncSymbol::addParam(dataType paramType){
    this->paramTypes.push_back(paramType);
}
void FuncSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//VarSymbol
symType VarSymbol::getType() {this->type=symType::variable; return this->type;}
dataType VarSymbol::getDataType()const{return this->data->getType();}
void VarSymbol::setData(dataType dtype,ValueVariant v){
    if(dtype==dataType::data_undefined){
        return;
    }
    Data* d=createData(dtype,v);
    if(this->data!=nullptr&&this->data->getType()!=dataType::data_undefined&&dtype!=dataType::data_undefined&&this->data->getType()!=dtype)
        throw std::runtime_error("the var already has a type");
    else
        this->data=createData(dtype,v);
}
void VarSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//ConstSymbol
symType ConstSymbol::getType() {this->type=symType::constant_nonvar; return this->type;}
dataType ConstSymbol::getDataType()const{return this->data->getType();}
void ConstSymbol::setData(dataType dtype,ValueVariant v){
    if(dtype==dataType::data_undefined){
        return;
    }
    Data* d=createData(dtype,v);
    if(this->data!=nullptr)
        throw std::runtime_error("trying to assign to a constant");
    else
        this->data=createData(dtype,v);
}
void ConstSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

//ConstVarSymbol
symType ConstVarSymbol::getType() {this->type=symType::constant_var; return this->type;}
dataType ConstVarSymbol::getDataType()const{return this->data->getType();}
void ConstVarSymbol::setData(dataType dtype,ValueVariant v){
    if(dtype==dataType::data_undefined){
        return;
    }
    Data* d=createData(dtype,v);
    if(this->data!=nullptr)
        throw std::runtime_error("trying to assign to a constant var");
    else
        this->data=createData(dtype,v);
}
void ConstVarSymbol::setScope(int scope){
    this->scope=scope;
    if(this->scope==GLOBAL_SCOPE){
        this->name="@"+this->name;
    }
    else{
        this->name="%"+this->name;
    }
}

std::string getSymOut(BasicSymbol* basicSymbol){
    switch (basicSymbol->getType())
    {
    case symType::constant_var:
    case symType::variable:
        return basicSymbol->getName();
    case symType::constant_nonvar:
        return my_to_string(basicSymbol->data);
    default:
        throw std::runtime_error("the type of b is wrong");
    }
}