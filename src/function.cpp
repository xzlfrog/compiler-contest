#include"../include/function.hpp"

int getDataSize(dataType type){
    switch(type){
        case dataType::i1: return 1;
        case dataType::i8: return 1;
        case dataType::i16: return 2;
        case dataType::i32: return 4;
        case dataType::i64: return 8;
        case dataType::f32: return 4;
        case dataType::f64: return 8;
        case dataType::pointer: return sizeof(void*);
        default: throw std::invalid_argument("Unknown data type");
    }
}

std::string DataTypeToString(dataType type)
{
    switch(type){
        case dataType::i1:return std::string("i1");
        case dataType::i8:return std::string("i8");
        case dataType::i16:return std::string("i16");
        case dataType::i32:return std::string("i32");
        case dataType::i64:return std::string("i64");
        case dataType::f32:return std::string("f32");
        case dataType::f64:return std::string("f64");
        default: throw std::invalid_argument("Unknown data type");
    }
}
