#include "../include/frontend/funcTool.hpp"

dataType stringToDatatyoe(std::string returnDataTypeString){
    if(returnDataTypeString == "int") {
        return dataType::i32;
    } else if(returnDataTypeString == "float") {
        return dataType::f32;
    } else if(returnDataTypeString == "void") {
        return dataType::void_;
    } else if(returnDataTypeString == "bool") {
        return dataType::i1;
    } else {
        throw std::runtime_error("Unknown data type: " + returnDataTypeString);
    }
}