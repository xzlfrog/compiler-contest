#include"../include/LocalMemoryOperations.hpp"

//AllocaNonArrayLLVM
dataType AllocaNonArrayLLVM::getPointedType(){return this->sym->getPointedType();}
PointerSymbol* AllocaNonArrayLLVM::getSymbol(){return this->sym;}
std::string AllocaNonArrayLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

std::string AllocaNonArrayLLVM::out_str() const {
    if (sym == nullptr) {
        throw std::invalid_argument("; <invalid alloca non-array>");
    }
    std::string result = "alloca " + getTypeStr(sym->getPointedType()) + ", align 8";
    if (!sym->name.empty()) {
        result += " %" + sym->name;
    }
    return result;
}

//AllocaArrayLLVM
dataType AllocaArrayLLVM::getArrayType(){return this->array->getArrayType();}
const std::vector<int>& AllocaArrayLLVM::getDimensions() const{return this->array->getDimensions();}
ArraySymbol* AllocaArrayLLVM::getArray(){return this->array;}
std::string AllocaArrayLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

std::string AllocaArrayLLVM::out_str() const {
    if (array == nullptr) {
        throw std::invalid_argument("; <invalid alloca array>");
    }
    std::string result = "alloca [" + std::to_string(array->getDimensions()[0]);
    for (size_t i = 1; i < array->getDimensions().size(); ++i) {
        result += " x " + std::to_string(array->getDimensions()[i]);
    }
    result += "] " + getTypeStr(array->getArrayType()) + ", align 8";
    if (!array->name.empty()) {
        result += " %" + array->name;
    }
    return result;
}

//LoadLLVM
dataType LoadLLVM::getDestType(){return this->dest_sym->getDataType();}
dataType LoadLLVM::getSrcPointedType(){return this->src_sym->getPointedType();}
PointerSymbol* LoadLLVM::getSrcSymbol(){return this->src_sym;}
BasicSymbol* LoadLLVM::getDestSymbol(){return this->dest_sym;}
std::string LoadLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

std::string LoadLLVM::out_str() const {
    if (src_sym == nullptr || dest_sym == nullptr) {
        throw std::invalid_argument("; <invalid load instruction>");
    }
    std::string result = "%" + dest_sym->name + " = load " + getTypeStr(dest_sym->getDataType()) + ", ";
    result += getTypeStr(src_sym->getPointedType()) + "* %" + src_sym->name;
    return result;
}

//StoreLLVM::
dataType StoreLLVM::getDestPointedType(){return this->dest_sym->getPointedType();}
dataType StoreLLVM::getSrcType(){return this->src_sym->getDataType();}
BasicSymbol* StoreLLVM::getSrcSymbol(){return this->src_sym;}
PointerSymbol* StoreLLVM::getDestSymbol(){return this->dest_sym;}
std::string StoreLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

std::string StoreLLVM::out_str() const {
    if (src_sym == nullptr || dest_sym == nullptr) {
        throw std::invalid_argument("; <invalid store instruction>");
    }
    std::string result = "store " + getTypeStr(src_sym->getDataType()) + " %" + src_sym->name + ", ";
    result += getTypeStr(dest_sym->getPointedType()) + "* %" + dest_sym->name;
    return result;
}

//GetElementPtrLLVM::
dataType GetElementPtrLLVM::getArrayType(){return this->ptrval->getArrayType();}
const std::vector<int>&GetElementPtrLLVM::getDimensions() const{return this->ptrval->getDimensions();}
ArraySymbol* GetElementPtrLLVM::getSrcSymbol(){return this->ptrval;}
PointerSymbol* GetElementPtrLLVM::getDestSymbol(){return this->dest_sym;}
const std::vector<std::pair<dataType,BasicSymbol*>> GetElementPtrLLVM::getTyAndIdx(){return this->ty_idx;}
dataType GetElementPtrLLVM::getDestPointedType(){return this->dest_sym->getPointedType();}
std::string GetElementPtrLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

void GetElementPtrLLVM::addTyIdx(dataType ty,BasicSymbol* idx){
    this->ty_idx.push_back({ty,idx});
}
void GetElementPtrLLVM::addTyIdx(std::vector<dataType>ty,std::vector<BasicSymbol*>idx){
    if(ty.size()!=idx.size()){
        throw std::invalid_argument("the size of the argument not match");
    }
    for(int i=0;i<ty.size();i++){
        this->addTyIdx(ty[i],idx[i]);
    }
}
std::string GetElementPtrLLVM::out_str() const {
    if (ptrval == nullptr || dest_sym == nullptr) {
        throw std::invalid_argument("; <invalid getelementptr instruction>");
    }
    std::string result = "%" + dest_sym->name + " = getelementptr ";
    result += "[" + std::to_string(ptrval->getDimensions()[0]);
    for (size_t i = 1; i < ptrval->getDimensions().size(); ++i) {
        result += " x " + std::to_string(ptrval->getDimensions()[i]);
    }
    result += "] " + getTypeStr(ptrval->getArrayType()) + ", ";
    
    result += "%" + ptrval->name;
    
    for (const auto& pair : ty_idx) {
        result += ", " + getTypeStr(pair.first) + " %" + pair.second->name;
    }
    
    return result;
}