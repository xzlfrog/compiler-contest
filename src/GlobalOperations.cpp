#include"../include/GlobalOperations.hpp"

//GlobalNonArrayVarDefination
dataType GlobalNonArrayVarDefination::getPointedType(){return this->dest_sym->getPointedType();}
PointerSymbol* GlobalNonArrayVarDefination::getDestSymbol(){return this->dest_sym;}
BasicSymbol* GlobalNonArrayVarDefination::getSrcSymbol(){return this->src_sym;}
initializer GlobalNonArrayVarDefination::getInitMode(){return this->dest_sym->pointedData->getInitMode();}
std::string GlobalNonArrayVarDefination::getPointedTypeStr(dataType PointedType) const{
    switch(PointedType){
        case data_undefined: return "undefined";
        case void_: return "void";
        case i1: return "i1";
        case i8: return "i8";
        case i16: return "i16";
        case i32: return "i32";
        case i64: return "i64";
        case f32: return "f32";
        case f64: return "f64";
        default: throw std::invalid_argument("Unknown pointed type");
    }
}

std::string GlobalNonArrayVarDefination::out_str()const{
    std::string res =  "@" + dest_sym->name + " = global ";
    res += this->getPointedTypeStr(this->dest_sym->getPointedType()) + " ";
    if(this->src_sym){
        res += this->src_sym->name;
    } else {
        res += "null";
    }
    return res;
}

//ConstantNonArrayVarDefination
dataType ConstantNonArrayVarDefination::getConstType(){return this->dest_sym->getDataType();}
BasicSymbol* ConstantNonArrayVarDefination::getDestSymbol(){return this->dest_sym;}
BasicSymbol* ConstantNonArrayVarDefination::getSrcSymbol(){return this->src_sym;}
initializer ConstantNonArrayVarDefination::getInitMode(){return this->dest_sym->data->getInitMode();}
std::string ConstantNonArrayVarDefination::getConstTypeStr(dataType constType) const {
    switch(constType){
        case data_undefined: return "undefined";
        case void_: return "void";
        case i1: return "i1";
        case i8: return "i8";
        case i16: return "i16";
        case i32: return "i32";
        case i64: return "i64";
        case f32: return "f32";
        case f64: return "f64";
        default: throw std::invalid_argument("Unknown constant type");
    }
}

std::string ConstantNonArrayVarDefination::out_str()const{
    std::string res =  "@" + dest_sym->name + " = constant ";
    res += this->getConstTypeStr(this->dest_sym->getDataType()) + " ";
    if(this->src_sym){
        res += this->src_sym->name;
    } else {
        res += "null";  
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
        case f32: return "f32";
        case f64: return "f64";
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
        case f32: return "f32";
        case f64: return "f64";
        default: throw std::invalid_argument("Unknown parameter type");
    }
}
std::string FuncDeclaration::out_str()const{
    std::string res = "declare ";
    res += this->getReturnTypeStr(this->func->returnType) + " ";
    res += this->func->name + "(";
    
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
        case f32: return "f32";
        case f64: return "f64";
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
        case f32: return "f32";
        case f64: return "f64";
        default: throw std::invalid_argument("Unknown parameter type");
    }
}
// Output the function definition as a string
std::string FuncDefination::out_str()const{
    std::string res = "define ";
    res += this->getReturnTypeStr(this->func->returnType) + " ";
    res += this->func->name + "(";
    
    for(size_t i = 0; i < this->func->paramTypes.size(); ++i){
        res += this->getParamTypeStr(this->func->paramTypes[i]);
        if(i < this->func->paramTypes.size() - 1){
            res += ", ";
        }
    }
    
    res += ") {\n";
    
    for(auto& param : this->params){
        res += "  " + param->name + ";\n"; // Assuming params are BasicSymbol with a name
    }
    
    res += "}\n";
    return res;
}
