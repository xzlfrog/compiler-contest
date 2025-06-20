#include"../include/sym.hpp"

//PointerSymbol
symType PointerSymbol::getType() const {return symType::pointer;}
dataType PointerSymbol::getPointedType() const {return this->PointedType;}
void PointerSymbol::allocateMemory(dataType elementType,ValueVariant value){
    this->PointedType = elementType;
    Data_pointer* data_pointer = new Data_pointer();
    Data* data=createData(elementType,value);
    this->data=new Data_pointer();
    this->data->setValue(data);
    this->pointedData=std::get<Data*>(this->data->getValue());
}

//BasicSymbol
symType BasicSymbol::getType() const {return this->type;}
dataType BasicSymbol::getDataType()const{return this->data->getType();}
void BasicSymbol::setData(dataType dtype,ValueVariant v=nullptr){this->data=createData(dtype,v);}
void BasicSymbol::setType(symType type) {
    if(type<symType::variable||type>symType::constant_f64)
        throw std::invalid_argument("basic symbol type is wrong");
    this->type=type;
}

//ArraySymbol
symType ArraySymbol::getType() const {return symType::array;}
void ArraySymbol::allocateMemory(dataType type,std::vector<int>&dims){
    this->arrayType=type;
    this->dimensions=dims;
    int size=1;
    for(auto dim:this->dimensions)
        size=dim*size;
    this->elementNums.push_back(size);
    for(auto dim:this->dimensions)
        size=size/dim,this->elementNums.push_back(size);
}
std::vector<int>ArraySymbol::getDimensions()const{return this->dimensions;}
dataType ArraySymbol::getArrayType()const{return this->arrayType;}

//LabelSymbol
symType LabelSymbol::getType() const{return symType::label;}

//FuncSymbol
symType FuncSymbol::getType() const {return symType::function;}
const std::vector<dataType> FuncSymbol::getParamTypes()const{return this->paramTypes;}
dataType FuncSymbol::getReturnType()const{return this->returnType;}

void FuncSymbol::addArguments(std::vector<dataType> arguments){}
void FuncSymbol::addArgument(dataType argument){}


