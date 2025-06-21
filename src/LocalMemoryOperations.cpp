#include"../include/LocalMemoryOperations.hpp""

//AllocaNonArrayLLVM
dataType AllocaNonArrayLLVM::getPointedType(){return this->sym->getPointedType();}
PointerSymbol* AllocaNonArrayLLVM::getSymbol(){return this->sym;}

std::string AllocaNonArrayLLVM::out_str() const {}

//AllocaArrayLLVM
dataType AllocaArrayLLVM::getArrayType(){return this->array->getArrayType();}
const std::vector<int>& AllocaArrayLLVM::getDimensions() const{return this->array->getDimensions();}
ArraySymbol* AllocaArrayLLVM::getArray(){return this->array;}

std::string AllocaArrayLLVM::out_str() const {}

//LoadLLVM
dataType LoadLLVM::getDestType(){return this->dest_sym->getDataType();}
dataType LoadLLVM::getSrcPointedType(){return this->src_sym->getPointedType();}
PointerSymbol* LoadLLVM::getSrcSymbol(){return this->src_sym;}
BasicSymbol* LoadLLVM::getDestSymbol(){return this->dest_sym;}

std::string LoadLLVM::out_str() const {}

//StoreLLVM::
dataType StoreLLVM::getDestPointedType(){return this->dest_sym->getPointedType();}
dataType StoreLLVM::getSrcType(){return this->src_sym->getDataType();}
BasicSymbol* StoreLLVM::getSrcSymbol(){return this->src_sym;}
PointerSymbol* StoreLLVM::getDestSymbol(){return this->dest_sym;}

std::string StoreLLVM::out_str() const {}

//GetElementPtrLLVM::
dataType GetElementPtrLLVM::getArrayType(){return this->ptrval->getArrayType();}
const std::vector<int>&GetElementPtrLLVM::getDimensions() const{return this->ptrval->getDimensions();}
ArraySymbol* GetElementPtrLLVM::getSrcSymbol(){return this->ptrval;}
PointerSymbol* GetElementPtrLLVM::getDestSymbol(){return this->dest_sym;}
const std::vector<std::pair<dataType,BasicSymbol*>> GetElementPtrLLVM::getTyAndIdx(){return this->ty_idx;}
dataType GetElementPtrLLVM::getDestPointedType(){return this->dest_sym->getPointedType();}

void GetElementPtrLLVM::addTyIdx(dataType ty,BasicSymbol* idx){}
void GetElementPtrLLVM::addTyIdx(std::vector<dataType>ty,std::vector<BasicSymbol*>idx){}
std::string GetElementPtrLLVM::out_str() const {}