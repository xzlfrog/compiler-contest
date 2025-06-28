#include"../include/data.hpp"

//Data
bool Data::getIsInitialized(){return this->isInitialized;};
void Data::setInitMode(initializer initMode){this->initMode=initMode;}
initializer Data::getInitMode(){return this->initMode;}
bool Data::checkIsInitialed(){
    if(this->isInitialized==false){
        throw std::runtime_error("the variable is not initialized");
    }
}
void Data::setIsInitialize(bool flag){this->isInitialized=flag;}
dataType Data::getType() const{return dataType::data_undefined;}
std::string Data::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1:   return "i1";
        case dataType::i8:   return "i8";
        case dataType::i16:  return "i16";
        case dataType::i32:  return "i32";
        case dataType::i64:  return "i64";
        case dataType::f32:  return "f32";
        case dataType::f64:  return "f64";
        default: throw std::invalid_argument("Invalid data type for function call");
    }
}

//Data_i1
dataType Data_i1::getType() const{return dataType::i1;}

ValueVariant Data_i1::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (bool)0;
    else
        return value;
} 

void Data_i1::setValue(ValueVariant value){
    if (std::holds_alternative<bool>(value)) {
        this->value = std::get<bool>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not bool type");
    }
}

//Data_i8
dataType Data_i8::getType() const{return dataType::i8;}

ValueVariant Data_i8::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (char)0;
    else
        return value;
}

void Data_i8::setValue(ValueVariant value){
    if (std::holds_alternative<char>(value)) {
        this->value = std::get<char>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not char type");
    }
}


//Data_i16
dataType Data_i16::getType() const{return dataType::i16;}

ValueVariant Data_i16::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (short)0;
    else
        return value;
}

void Data_i16::setValue(ValueVariant value){
    if (std::holds_alternative<short>(value)) {
        this->value = std::get<short>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not short type");
    }
}

//Data_i32
dataType Data_i32::getType() const{return dataType::i32;}

ValueVariant Data_i32::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (int)0;
    else
        return value;
}

void Data_i32::setValue(ValueVariant value){
    if (std::holds_alternative<int>(value)) {
        this->value = std::get<int>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not int type");
    }
}

//Data_i64
dataType Data_i64::getType() const{return dataType::i64;}

ValueVariant Data_i64::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (long long)0;
    else
        return value;
}

void Data_i64::setValue(ValueVariant value){
    if (std::holds_alternative<long long>(value)) {
        this->value = std::get<long long>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not long long type");
    }
}

//Data_f32
dataType Data_f32::getType() const{return dataType::f32;}

ValueVariant Data_f32::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (float)0;
    else
        return value;
}

void Data_f32::setValue(ValueVariant value){
    if (std::holds_alternative<float>(value)) {
        this->value = std::get<float>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not float type");
    }
}

//Data_f64
dataType Data_f64::getType() const{return dataType::f64;}

ValueVariant Data_f64::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return (double)0;
    else
        return value;
}

void Data_f64::setValue(ValueVariant value){
    if (std::holds_alternative<double>(value)) {
        this->value = std::get<double>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not double type");
    }
}

//Data_pointer
dataType Data_pointer::getType() const {return dataType::pointer;}

ValueVariant Data_pointer::getValue(){
    this->checkIsInitialed();
    if(this->getInitMode()==initializer::zeroinitializer)
        return nullptr;
    else
        return value;
}

void Data_pointer::setValue(ValueVariant value) {
    if (std::holds_alternative<Data*>(value)) {
        this->value = std::get<Data*>(value);
        this->setInitMode(initializer::assignment);
        this->setIsInitialize(true);
    } else {
        throw std::invalid_argument("ValueVariant is not pointer type");
    }
}

//other
Data* createData(dataType type,ValueVariant v){
    Data* ret=createInitialedData(type);
    ret->setValue(v);
    ret->setInitMode(initializer::assignment);
    return ret;
}

Data* createData(dataType type,initializer initMode){
    Data* ret=createInitialedData(type);
    ret->setInitMode(initMode);
    if(initMode==initializer::undef)
        ret->setIsInitialize(false);
    return ret;
}

Data* createInitialedData(dataType type){
    Data* ret=new Data();
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
    case dataType::data_undefined:
        ret=new Data();
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

Data* createData(Data* data){
    Data* ret=createData(data->getType(),data->getValue());
    return ret;
}

Data* ConstExp::constFolding(){
    Data* data;
    switch(this->type)
    {
        case constExpType::const_exp_add :
            data=add(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_sub :
            data=sub(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_mul :
            data=mul(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_sdiv :
            data=sdiv(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_and :
            data=andi(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_or :
            data=ori(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_xor :
            data=xori(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fadd :
            data=fadd(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fsub :
            data=fsub(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fmul :
            data=fmul(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fdiv :
            data=fdiv(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fcmp_oeq :
            data=fcmp_oeq(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fcmp_oge :
            data=fcmp_oge(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fcmp_ogt :
            data=fcmp_ogt(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fcmp_ole :
            data=fcmp_ole(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fcmp_olt :
            data=fcmp_olt(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_fcmp_one :
            data=fcmp_one(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_icmp_eq :
            data=icmp_eq(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_icmp_sge :
            data=icmp_sge(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_icmp_sgt :
            data=icmp_sgt(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_icmp_sle :
            data=icmp_sle(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_icmp_slt :
            data=icmp_slt(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_icmp_ne :
            data=icmp_ne(this->constData1,this->constData2);
            break;
        case constExpType::const_exp_sitofp :
            data=sitofp(this->constData1);
            break;
    }
    return data;
}

Data* add(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a+b);
}

Data* sub(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a-b);
}

Data* mul(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a*b);
}

Data* sdiv(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a/b);
}

Data* andi(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a&b);
}
Data* ori(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a|b);
}

Data* xori(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i32,a^b);
}

Data* fadd(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::f32,a+b);
}

Data* fsub(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::f32,a-b);
}

Data* fmul(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::f32,a*b);
}

Data* fdiv(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::f32,a/b);
}

Data* icmp_eq(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i1,a==b);
}
Data* icmp_ne(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i1,a!=b);
}

//integer signed greater than
Data* icmp_sgt(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i1,a>b);
}

//integer signed greater than or equal
Data* icmp_sge(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i1,a>=b);
}

//integer signed less than
Data* icmp_slt(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i1,a<b);
}

// integer signed less than or equal
Data* icmp_sle(Data* data1,Data* data2){
    int a=std::get<int>(data1->getValue());
    int b=std::get<int>(data2->getValue());
    return createData(dataType::i1,a<=b);
}

//float equal
Data* fcmp_oeq(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::i1,a==b);
}

//float greater than
Data* fcmp_ogt(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::i1,a>b);
}

//float greater than or equal
Data* fcmp_oge(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::i1,a>=b);
}

//float less than
Data* fcmp_olt(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::i1,a<b);
}

//float less than or equal
Data* fcmp_ole(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::i1,a<=b);
}

//float not equal
Data* fcmp_one(Data* data1,Data* data2){
    float a=std::get<float>(data1->getValue());
    float b=std::get<float>(data2->getValue());
    return createData(dataType::i1,a!=b);
}

//有符号整数转浮点
Data* sitofp(Data* data1){
    int a=std::get<int>(data1->getValue());
    return createData(dataType::f32,(float)a);
}

