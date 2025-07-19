#include"../include/LocalMemoryOperations.hpp"
#include"../include/SymbolFactory.hpp"

//AllocaNonArrayLLVM
dataType AllocaNonArrayLLVM::getPointedType(){return this->sym->getPointedType();}
PointerSymbol* AllocaNonArrayLLVM::getSymbol(){return this->sym;}

std::string AllocaNonArrayLLVM::out_str() const {
    if (sym == nullptr) {
        throw std::invalid_argument("; <invalid alloca non-array>");
    }
    std::string result =this->sym->getName() +" = "+"alloca " + Data::getTypeStr(sym->getPointedType()) + ", align 8";
    return result;
}

//AllocaArrayLLVM
dataType AllocaArrayLLVM::getArrayType(){return this->array->getArrayType();}
const std::vector<int>& AllocaArrayLLVM::getDimensions() const{return this->array->getDimensions();}
ArraySymbol* AllocaArrayLLVM::getArray(){return this->array;}

std::string AllocaArrayLLVM::out_str() const {
    if (array == nullptr) {
        throw std::invalid_argument("; <invalid alloca array>");
    }
    int cnt=1;
    std::string result = this->array->getName() + " = "+"alloca [" + std::to_string(array->getDimensions()[0]);
    for (size_t i = 1; i < array->getDimensions().size(); ++i) {
        result += " x [" + std::to_string(array->getDimensions()[i]);
        cnt++;
    }
    result+=" x ";
    
    result += Data::getTypeStr(array->getArrayType()) ;
    for(int i=0;i<cnt;i++){
        result+="]";
    }
    result += ", align 8";
    return result;
}

//LoadLLVM
dataType LoadLLVM::getDestType(){return this->dest_sym->getDataType();}
dataType LoadLLVM::getSrcPointedType(){return this->src_sym->getPointedType();}
PointerSymbol* LoadLLVM::getSrcSymbol(){return this->src_sym;}
BasicSymbol* LoadLLVM::getDestSymbol(){return this->dest_sym;}

std::string LoadLLVM::out_str() const {
    if (src_sym == nullptr || dest_sym == nullptr) {
        throw std::invalid_argument("; <invalid load instruction>");
    }
    std::string result = dest_sym->getName() + " = load " + Data::getTypeStr(dest_sym->getDataType()) + ", ";
    result += Data::getTypeStr(src_sym->getPointedType()) + "* " + src_sym->getName();
    return result;
}

//StoreLLVM
dataType StoreLLVM::getDestPointedType(){return this->dest_sym->getPointedType();}
dataType StoreLLVM::getSrcType(){return this->src_sym->getDataType();}
BasicSymbol* StoreLLVM::getSrcSymbol(){return this->src_sym;}
PointerSymbol* StoreLLVM::getDestSymbol(){return this->dest_sym;}

std::string StoreLLVM::out_str() const {
    if (src_sym == nullptr || dest_sym == nullptr) {
        throw std::invalid_argument("; <invalid store instruction>");
    }
    std::string result = "store " + Data::getTypeStr(src_sym->getDataType()) + " " +getSymOut(src_sym) + ", ";
    result += Data::getTypeStr(dest_sym->getPointedType()) + "* " + dest_sym->getName();
    return result;
}

//GetElementPtrLLVM
dataType GetElementPtrLLVM::getArrayType(){return this->ptrval->getArrayType();}
const std::vector<int>&GetElementPtrLLVM::getDimensions() const{return this->ptrval->getDimensions();}
ArraySymbol* GetElementPtrLLVM::getSrcSymbol(){return this->ptrval;}
PointerSymbol* GetElementPtrLLVM::getDestSymbol(){return this->dest_sym;}
const std::vector<std::pair<dataType,BasicSymbol*>> GetElementPtrLLVM::getTyAndIdx(){return this->ty_idx;}
dataType GetElementPtrLLVM::getDestPointedType(){return this->dest_sym->getPointedType();}

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
    std::string result = dest_sym->getName() + " = getelementptr ";
    if(ptrval->getDimensions().size()!=0){
        result += "[" + std::to_string(ptrval->getDimensions()[0]);
        int cnt=1;
        for (size_t i = 1; i < ptrval->getDimensions().size(); ++i) {
            result += " x [" + std::to_string(ptrval->getDimensions()[i]);
            cnt++;
        }
        result+=" x ";
    
        result += Data::getTypeStr(ptrval->getArrayType()) ;
        for(int i=0;i<cnt;i++){
            result+="]";
        }

        result += ", [" + std::to_string(ptrval->getDimensions()[0]);
        cnt=1;
        for (size_t i = 1; i < ptrval->getDimensions().size(); ++i) {
            result += " x [" + std::to_string(ptrval->getDimensions()[i]);
            cnt++;
        }
        result+=" x ";
    
        result += Data::getTypeStr(ptrval->getArrayType()) ;
        for(int i=0;i<cnt;i++){
            result+="]";
        }

        result+="*";
    
        result += " "+ptrval->getName();
        //result += ", " + Data::getTypeStr(dataType::i32) + " " + getSymOut(SymbolFactory::createConstSymbol(createData(dataType::i32,0)));
        for (const auto& pair : ty_idx) {
            result += ", " + Data::getTypeStr(pair.first) + " " + getSymOut(pair.second);
        }
    }
    else{
        throw std::runtime_error("the src_sym's dimension is 0");
    }
    return result;
}

dataType GetElementPtrLLVM_PointerToVar::getArrayType(){return this->src_sym->getArrayType();}
std::string GetElementPtrLLVM_PointerToVar::out_str() const{
    std::string result;
    if(this->src_sym->getDimensions().size()==0){
        result+=dest_sym->getName()+" = getelementptr "+Data::getTypeStr(this->src_sym->getArrayType())+" "+Data::getTypeStr(this->src_sym->getArrayType());
        result+="* "+this->src_sym->getName()+", i32 "+getSymOut(this->idx);
    }
    else{
        throw std::runtime_error("the src_sym's dimension is not 0");
    }
    return result;
}