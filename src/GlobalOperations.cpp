#include"../include/GlobalOperations.hpp"
#include<iostream>

void array_def_recursion(std::vector<int>&dim,int i,dataType& type,std::string& s,bool flag,ArrayInitial* arrayInit,std::vector<int>&pos);

//GlobalNonArrayVarDefination
dataType GlobalNonArrayVarDefination::getPointedType(){return this->dest_sym->getPointedType();}
PointerSymbol* GlobalNonArrayVarDefination::getDestSymbol(){return this->dest_sym;}
BasicSymbol* GlobalNonArrayVarDefination::getSrcSymbol(){return this->src_sym;}
initializer GlobalNonArrayVarDefination::getInitMode(){return this->dest_sym->pointedData->getInitMode();}

std::string GlobalNonArrayVarDefination::out_str()const{
    if(dest_sym->scope>0){
        throw std::runtime_error("the variable is not a global variable");
    }
    std::string res =  dest_sym->getName() + " = global ";
    res += Data::getTypeStr(this->dest_sym->getPointedType()) + " ";
    switch (this->dest_sym->pointedData->getInitMode())
    {
    case initializer::zeroinitializer:
        res+="zeroinitializer";
        break;
    case initializer::undef:
        res+="undef";
        break;
    case initializer::assignment:
        res+=getSymOut(this->src_sym);
        break;
    default:
        throw std::runtime_error("the global variable initializer is wrong");
        break;
    }
    return res;
}

//ConstantNonArrayVarDefination
dataType ConstantNonArrayVarDefination::getConstType(){return this->dest_sym->getDataType();}
BasicSymbol* ConstantNonArrayVarDefination::getDestSymbol(){return this->dest_sym;}
BasicSymbol* ConstantNonArrayVarDefination::getSrcSymbol(){return this->src_sym;}
initializer ConstantNonArrayVarDefination::getInitMode(){return this->dest_sym->data->getInitMode();}

std::string ConstantNonArrayVarDefination::out_str()const{
    if(dest_sym->scope>0){
        throw std::runtime_error("the variable is not a global variable");
    }
    std::string res =  dest_sym->getName() + " = constant ";
    res += Data::getTypeStr(this->dest_sym->data->getType()) + " ";
    switch (this->dest_sym->data->getInitMode())
    {
    case initializer::zeroinitializer:
        res+="zeroinitializer";
        break;
    case initializer::undef:
        res+="undef";
        break;
    case initializer::assignment:
        res+=getSymOut(this->src_sym);
        break;
    default:
        throw std::runtime_error("the global variable initializer is wrong");
        break;
    }
    return res;
}

//FuncDeclaration
FuncSymbol* FuncDeclaration::getFuncSymbol(){return this->func;}
dataType FuncDeclaration::getReturnType(){return this->func->returnType;}
const std::vector<dataType>FuncDeclaration::getParamTypes()const {return this->func->paramTypes;}

void FuncDeclaration::addArguments(dataType ty){
    this->func->addParam(ty);
}

void FuncDeclaration::addArguments(std::vector<dataType>ty){
    for(auto a : ty){
        this->func->addParam(a);
    }
}
std::string FuncDeclaration::getReturnTypeStr(dataType returnType) const {
    switch(returnType){
        case data_undefined: return "undefined";
        case void_: return "void";
        case i1: return "i1";
        case i8: return "i8";
        case i16: return "i16";
        case i32: return "i32";
        case i64: return "i64";
        case f32: return "float";
        case f64: return "double";
        default: throw std::invalid_argument("Unknown return type");
    }
}
std::string FuncDeclaration::getParamTypeStr(dataType paramType) const {
    switch(paramType){
        case data_undefined: return "undefined";
        case void_: return "void";
        case i1: return "i1";
        case i8: return "i8";
        case i16: return "i16";
        case i32: return "i32";
        case i64: return "i64";
        case f32: return "float";
        case f64: return "double";
        default: throw std::invalid_argument("Unknown parameter type");
    }
}
std::string FuncDeclaration::out_str()const{
    std::string res = "declare ";
    res += this->getReturnTypeStr(this->func->returnType) + " ";
    res += this->func->getName() + "(";
    
    for(size_t i = 0; i < this->func->paramTypes.size(); ++i){
        res += this->getParamTypeStr(this->func->paramTypes[i]);
        if(i < this->func->paramTypes.size() - 1){
            res += ", ";
        }
    }
    
    res += ")";
    return res;
}

//FuncDefination
FuncSymbol* FuncDefination::getFuncSymbol(){return this->func;}
dataType FuncDefination::getReturnType(){return this->func->returnType;}
const std::vector<dataType>FuncDefination::getParamTypes()const {return this->func->paramTypes;}
const std::vector<BasicSymbol*>FuncDefination::getParams(){return this->params;}

void FuncDefination::addArguments(dataType ty,BasicSymbol* sym){
    this->params.push_back(sym);
}
void FuncDefination::addArguments(std::vector<dataType>ty,std::vector<BasicSymbol*>sym){
    if(ty.size()!=sym.size()){
        throw std::invalid_argument("the size of the argument not match");
    }
    for(int i=0;i<ty.size();i++){
        this->addArguments(ty,sym);
    }
}
std::string FuncDefination::getReturnTypeStr(dataType returnType) const {
    switch(returnType){
        case data_undefined: return "undefined";
        case void_: return "void";
        case i1: return "i1";
        case i8: return "i8";
        case i16: return "i16";
        case i32: return "i32";
        case i64: return "i64";
        case f32: return "float";
        case f64: return "double";
        default: throw std::invalid_argument("Unknown return type");
    }
}
std::string FuncDefination::getParamTypeStr(dataType paramType) const {
    switch(paramType){
        case data_undefined: return "undefined";
        case void_: return "void";
        case i1: return "i1";
        case i8: return "i8";
        case i16: return "i16";         
        case i32: return "i32";
        case i64: return "i64";
        case f32: return "float";
        case f64: return "double";
        default: throw std::invalid_argument("Unknown parameter type");
    }
}
// Output the function definition as a string
std::string FuncDefination::out_str()const{
    std::string res = "define ";
    res += this->getReturnTypeStr(this->func->returnType) + " ";
    res += this->func->getName() + "(";
    
    for(size_t i = 0; i < this->func->paramTypes.size(); ++i){
        res += this->getParamTypeStr(this->func->paramTypes[i]);
        res += " "+this->params[i]->getName();
        if(i < this->func->paramTypes.size() - 1){
            res += ", ";
        }
    }
    
    res += ") {\n";
    if(this->block_tail==nullptr){
        res+="}\n";
        return res;
    }

    for(LLVM*llvm=this->next;llvm!=this->block_tail&&llvm!=nullptr;llvm=llvm->next){
        res += llvm->out_str()+ ";\n"; // Assuming params are BasicSymbol with a name
    }
    
    res += "}\n";
    return res;
}

//GlobalArrayVarDefination
const std::vector<int>&GlobalArrayVarDefination::getDimensions() const{
    return this->dest_sym->getDimensions();
}

dataType GlobalArrayVarDefination::getArrayType(){
    return this->dest_sym->getArrayType();
}

const std::vector<std::pair<std::vector<int>,Data*>>& GlobalArrayVarDefination::getInitializedData(){
    return this->dest_sym->getInitializedData();
}

std::string GlobalArrayVarDefination::out_str()const{
    std::string res;
    res=res+this->dest_sym->getName()+" = global ";
    std::vector<int>dim=this->dest_sym->getDimensions();
    dataType type=this->dest_sym->getArrayType();
    ArrayInitial* arrayInit=this->dest_sym->initialedData;
    std::vector<int>pos;
    array_def_recursion(dim,0,type,res,false,arrayInit,pos);
    return res;
}

//ConstantArrayVarDefination
const std::vector<int>&ConstantArrayVarDefination::getDimensions() const{
    return this->dest_sym->getDimensions();
}

dataType ConstantArrayVarDefination::getArrayType(){
    return this->dest_sym->getArrayType();
}

const std::vector<std::pair<std::vector<int>,Data*>>& ConstantArrayVarDefination::getInitializedData(){
    return this->dest_sym->getInitializedData();
}

std::string ConstantArrayVarDefination::out_str()const{
    std::string res;
    res=res+this->dest_sym->getName()+" = constant ";
    std::vector<int>dim=this->dest_sym->getDimensions();
    dataType type=this->dest_sym->getArrayType();
    ArrayInitial* arrayInit=this->dest_sym->initialedData;
    std::vector<int>pos;
    array_def_recursion(dim,0,type,res,false,arrayInit,pos);
    return res;
}

int vector_int_cmp(std::vector<int>& a,std::vector<int>& b){
    if(a.size()!=b.size()){
        return -1;
    }
    for(int i=0;i<a.size();i++){
        if(a[i]>b[i])
            return 1;
        else if(a[i]<b[i])
            return 2;
    }
    return 0;
}

std::string getZero(dataType type){
    switch (type)
    {
    case dataType::i1:
    case dataType::i8:
    case dataType::i16:
    case dataType::i32:
    case dataType::i64:
        return "0";
    case dataType::f32:
    case dataType::f64:
        return "0.000000";
    default:
        throw std::runtime_error("the type is wrong");
    }
}

void array_def_recursion(std::vector<int>&dim,int i,dataType& type,std::string& s,bool flag,ArrayInitial* arrayInit,std::vector<int>&pos){
    s += " [" + std::to_string(dim[i]);
    int cnt=1;
    for (size_t j = i+1; j < dim.size(); ++j) {
        s += " x [" + std::to_string(dim[j]);
        cnt++;
    }
    s+=" x ";
    
    s += Data::getTypeStr(type) ;
    for(int i=0;i<cnt;i++){
        s+="]";
    }

    s+=" [";
    if(i+1<dim.size()){
        s+="\n";
        for(int j=0;j<dim[i]-1;j++){
            pos.push_back(j);
            array_def_recursion(dim,i+1,type,s,true,arrayInit,pos);
            pos.pop_back();
        }
        pos.push_back(dim[i]-1);
        array_def_recursion(dim,i+1,type,s,false,arrayInit,pos);
        pos.pop_back();
    }
    else{
        std::vector<std::pair<std::vector<int>,Data*>> init_pos=arrayInit->getInitializedData();
        int k=0;
        int flag=-1;
        for(int j=0;j<dim[i];j++){
            for(k=0;k<init_pos.size();k++){
                std::cout<<"k= "<<k<<"\n";
                pos.push_back(j);
                flag=vector_int_cmp(init_pos[k].first,pos);
                pos.pop_back();
                if(flag==0){
                    s+=Data::getTypeStr(init_pos[k].second->getType())+" "+getSymOut(SymbolFactory::createConstSymbol(init_pos[k].second));
                    break;
                }
            }
            if(k>=init_pos.size()||flag==1){
                s+=Data::getTypeStr(type)+" "+getZero(type);
            }
            if(j!=dim[i-1])
                s+=", ";
        }
    }

    if(flag)
        s+="],\n";
    else
        s+="]\n";
}
