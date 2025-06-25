#include"../include/SymbolFactory.hpp"

VarSymbol* SymbolFactory::createVarSymbol(std::string name,Data*data=nullptr){}
ConstVarSymbol* SymbolFactory::createConstVarSymbol(std::string name,Data* data=nullptr){}
VarSymbol* SymbolFactory::createTmpVarSymbol(Data*data=nullptr){}
ConstSymbol* SymbolFactory::createConstSymbol(Data*data=nullptr){}
PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,dataType pointedType=dataType::data_undefined){}
PointerSymbol* SymbolFactory::createPointerSymbol(std::string name,ValueVariant value,dataType pointedType=dataType::data_undefined){}
ArraySymbol* SymbolFactory::createArraySymbol(std::string name,dataType type=dataType::data_undefined){}
ArraySymbol* SymbolFactory::createArraySymbol(std::string name,std::vector<int>&dimensions,dataType type=dataType::data_undefined){}
LabelSymbol* SymbolFactory::createLabelSymbol(std::string name){}
LabelSymbol* SymbolFactory::createTmpLabelSymbol(){}
FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,std::vector<dataType>& paramTypes,dataType returnType=dataType::data_undefined){}
FuncSymbol* SymbolFactory::createFuncSymbol(std::string name,dataType returnType=dataType::data_undefined){}