#include"../include/data.hpp"

//Data
bool Data::getIsInitialized(){return this->isInitialized;};
void Data::setInitMode(initializer initMode){this->initMode=initMode;}
initializer Data::getInitMode(){return this->initMode;}

void setIsInitialize(bool flag);

//Data_i1
dataType Data_i1::getType() const{return dataType::i1;}
ValueVariant Data_i1::getValue(){return value;} 
void Data_i1::setValue(ValueVariant value){
    if (std::holds_alternative<bool>(value)) {
        this->value = std::get<bool>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not bool type");
    }
}

//Data_i8
dataType Data_i8::getType() const{return dataType::i8;}
ValueVariant Data_i8::getValue(){return value;}
void Data_i8::setValue(ValueVariant value){
    if (std::holds_alternative<char>(value)) {
        this->value = std::get<char>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}


//Data_i16
dataType Data_i16::getType() const{return dataType::i16;}
ValueVariant Data_i16::getValue(){return value;}
void Data_i16::setValue(ValueVariant value){
    if (std::holds_alternative<short>(value)) {
        this->value = std::get<short>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}

//Data_i32
dataType Data_i32::getType() const{return dataType::i32;}
ValueVariant Data_i32::getValue(){return value;}
void Data_i32::setValue(ValueVariant value){
    if (std::holds_alternative<int>(value)) {
        this->value = std::get<int>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}

//Data_i64
dataType Data_i64::getType() const{return dataType::i64;}
ValueVariant Data_i64::getValue(){return value;}
void Data_i8::setValue(ValueVariant value){
    if (std::holds_alternative<long long>(value)) {
        this->value = std::get<long long>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}

//Data_f32
dataType Data_f32::getType() const{return dataType::f32;}
ValueVariant Data_f32::getValue(){return value;}
void Data_i8::setValue(ValueVariant value){
    if (std::holds_alternative<float>(value)) {
        this->value = std::get<float>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}

//Data_f64
dataType Data_f64::getType() const{return dataType::f64;}
ValueVariant Data_f64::getValue(){return value;}
void Data_i8::setValue(ValueVariant value){
    if (std::holds_alternative<double>(value)) {
        this->value = std::get<double>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}

//Data_pointer
dataType Data_pointer::getType() const {return dataType::pointer;}
ValueVariant Data_pointer::getValue(){return value;}
void Data_pointer::setValue(ValueVariant value) {
    if (std::holds_alternative<Data*>(value)) {
        this->value = std::get<Data*>(value);
    } else {
        throw std::invalid_argument("ValueVariant is not pointer type");
    }
}

//other
Data* createData(dataType type,ValueVariant v){
    Data* ret;
    switch (type)
    {
    case dataType::i1:
        ret=new Data_i1();
        break;
    case dataType::i8:
        ret=new Data_i8();
        break;
    case dataType::i16:
        ret=new Data_i16();
        break;
    case dataType::i32:
        ret=new Data_i32();
        break;
    case dataType::i64:
        ret=new Data_i64();
        break;
    case dataType::f32:
        ret=new Data_f32();
        break;
    case dataType::f64:
        ret=new Data_f64();
        break;
    default:
        throw std::invalid_argument("invalid type in creating a new data");
    }
    ret->setValue(v);
    ret->setIsInitialize(true);
    ret->setInitMode(initializer::assignment);
    return ret;
}

Data* createData(dataType type,initializer initMode){
    Data* ret;
    switch (type)
    {
    case dataType::i1:
        ret=new Data_i1();
        break;
    case dataType::i8:
        ret=new Data_i8();
        break;
    case dataType::i16:
        ret=new Data_i16();
        break;
    case dataType::i32:
        ret=new Data_i32();
        break;
    case dataType::i64:
        ret=new Data_i64();
        break;
    case dataType::f32:
        ret=new Data_f32();
        break;
    case dataType::f64:
        ret=new Data_f64();
        break;
    default:
        throw std::invalid_argument("invalid type in creating a new data");
    }
    //ret->setValue(v);
    ret->setIsInitialize(true);
    ret->setInitMode(initMode);
    return ret;
}

Data* createInitialedData(dataType type){
    Data* ret;
    switch (type)
    {
    case dataType::i1:
        ret=new Data_i1();
        break;
    case dataType::i8:
        ret=new Data_i8();
        break;
    case dataType::i16:
        ret=new Data_i16();
        break;
    case dataType::i32:
        ret=new Data_i32();
        break;
    case dataType::i64:
        ret=new Data_i64();
        break;
    case dataType::f32:
        ret=new Data_f32();
        break;
    case dataType::f64:
        ret=new Data_f64();
        break;
    default:
        throw std::invalid_argument("invalid type in creating a new data");
    }
    ret->setIsInitialize(true);
    return ret;
}

Data* createNonInitialedData(dataType type){
    Data* ret=createInitialedData(type);
    ret->setIsInitialize(false);
    return ret;
}