#include"../include/GlobalOperations.hpp"

//GlobalNonArrayVarDefination
dataType GlobalNonArrayVarDefination::getPointedType(){return this->dest_sym->getPointedType();}
PointerSymbol* GlobalNonArrayVarDefination::getDestSymbol(){return this->dest_sym;}
BasicSymbol* GlobalNonArrayVarDefination::getSrcSymbol(){return this->src_sym;}

std::string GlobalNonArrayVarDefination::out_str()const{}

//ConstantNonArrayVarDefination
dataType ConstantNonArrayVarDefination::getConstType(){return this->dest_sym->getDataType();}
BasicSymbol* ConstantNonArrayVarDefination::getDestSymbol(){return this->dest_sym;}
BasicSymbol* ConstantNonArrayVarDefination::getSrcSymbol(){return this->src_sym;}
initializer ConstantNonArrayVarDefination::getInitMode(){return this->dest_sym->data->getInitMode();}

std::string ConstantNonArrayVarDefination::out_str()const{}

//FuncDeclaration
FuncSymbol* FuncDeclaration::getFuncSymbol(){return this->func;}
dataType FuncDeclaration::getReturnType(){return this->func->returnType;}
const std::vector<dataType>FuncDeclaration::getParamTypes()const {return this->func->paramTypes;}

void FuncDeclaration::addArguments(dataType ty){}
void FuncDeclaration::addArguments(std::vector<dataType>ty){}
std::string FuncDeclaration::out_str()const{}

//FuncDefination
FuncSymbol* FuncDefination::getFuncSymbol(){return this->func;}
dataType FuncDefination::getReturnType(){return this->func->returnType;}
const std::vector<dataType>FuncDefination::getParamTypes()const {return this->func->paramTypes;}
const std::vector<BasicSymbol*>FuncDefination::getParams(){return this->params;}

void FuncDefination::addArguments(dataType ty,Symbol* sym){}
void FuncDefination::addArguments(std::vector<dataType>ty,std::vector<Symbol*>tym){}
std::string FuncDefination::out_str()const{}
