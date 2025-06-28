#include"../include/TypeConversionOperations.hpp"

//TypeConversionOperation::
BasicSymbol* TypeConversionOperation::getSrcSymbol(){return this->src_sym;}
BasicSymbol* TypeConversionOperation::getDestSymbol(){return this->dest_sym;}
dataType TypeConversionOperation::getSrcType(){return this->src_sym->getDataType();}
dataType TypeConversionOperation::getDestType(){return this->dest_sym->getDataType();}

std::string TypeConversionOperation::out_str() const {}