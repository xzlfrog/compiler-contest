#pragma once

#include<string>
#include<variant>
#include<stdexcept>
#include<vector>
#include<utility>

//数据类型
enum dataType{
    data_undefined,
    void_,
    i1,
    i8,
    i16,
    i32,
    i64,
    f32,
    f64,
    pointer
};

enum constExpType{
    const_exp_add,
    const_exp_sub,
    const_exp_mul,
    const_exp_udiv,
    const_exp_sdiv,
    const_exp_and,
    const_exp_or,
    const_exp_xor,
    const_exp_fadd,
    const_exp_fsub,
    const_exp_fmul,
    const_exp_fdiv,
    const_exp_icmp_eq,//integer equal
    const_exp_icmp_ne,//integer not equal
    const_exp_icmp_ugt,//integer unsigned greater than
    const_exp_icmp_uge,//integer unsigned greater than or equal
    const_exp_icmp_ult,//integer unsigned less than
    const_exp_icmp_ule,//integer unsigned less than or equal
    const_exp_icmp_sgt,//integer signed greater than
    const_exp_icmp_sge,//integer signed greater than or equal
    const_exp_icmp_slt,//integer signed less than
    const_exp_icmp_sle,// integer signed less than or equal
    const_exp_fcmp_oeq,//float equal
    const_exp_fcmp_ogt,//float greater than
    const_exp_fcmp_oge,//float greater than or equal
    const_exp_fcmp_olt,//float less than
    const_exp_fcmp_ole,//float less than or equal
    const_exp_fcmp_one,//float not equal
    const_exp_fcmp_ord,// float ordered
    const_exp_uitofp,//无符号整数转浮点
    const_exp_sitofp,//有符号整数转浮点
};

//初始化方式
enum initializer{
    zeroinitializer,
    undef,
    assignment
};

class Data;

using ValueVariant = std::variant<bool,char,short,int,long long,float,double,Data*>;

class Data {
private:
    dataType type;//数据类型
    bool isInitialized;//是否被初始化
    initializer initMode;//初始化方式
    
public:
    virtual dataType getType() const;//得到数据类型
    virtual ValueVariant getValue();//得到数据，需要使用std::holds_alternative</*你要的数据类型*/>(data->getValue())来得到数据
    virtual void setValue(ValueVariant value);//设置对应的数据
    void setIsInitialize(bool flag);
    bool getIsInitialized();
    void setInitMode(initializer initMode);
    initializer getInitMode();
};

class Data_i1:public Data {
private:
    bool value;
public:
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

class Data_i8:public Data {
private:
    char value;
public:    
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

class Data_i16:public Data {
private:
    short value;
public:    
    dataType getType() const override;
    ValueVariant getValue()override;
    void setValue(ValueVariant value) override;
};

class Data_i32:public Data {
private:
    int value;
public:    
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

class Data_i64:public Data {
private:
    long long value;
public:    
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

class Data_f32:public Data {
private:
    float value;
public:    
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

class Data_f64:public Data {
private:
    double value;
public:    
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

class Data_pointer:public Data {
private:
    Data* value;
public:
    dataType getType() const override;
    ValueVariant getValue() override;
    void setValue(ValueVariant value) override;
};

Data* createData(dataType type,ValueVariant v);//type为对应的数据的类，v为这个数据初始化的值
Data* createInitialedData(dataType type);//type为对应的数据的类,生成的data类是实际上已经赋值了的，但是由于我们没有在编译器中进行计算，所以不知道它的值
Data* createData(dataType type,initializer initMode);//type为对应的数据的类,initMode表示初始化方式，比如undef和zeroinitializer
Data* createNonInitialedData(dataType type);//type为对应的数据的类,生成的data类是未经过初始化的值

/*
我们对于所有的常量表达式进行常量折叠，生成对应的BasicSymbol*类型
常数表达式对应的符号
常数表达式使用到的场景(部分)：
@a = global i32 add (i32 2, i32 3)                ; 5
@b = global i64 zext (i32 42 to i64)              ; 42扩展为i64
@c = global i32* getelementptr ([10 x i32], [10 x i32]* @arr, i32 0, i32 7)
@d = global i32 select (i1 true, i32 1, i32 2)    ; 1
*/
class ConstExp{
private:
    Data* constData1;
    Data* constData2;
    constExpType type;
    dataType newType;
    
public:
    Data* constFolding();//进行常数折叠，生成一个对应的BasicSymbol*类型符号

    /*type表示常数表达式的类型，两个data分别是运算符左右，如果是不需要支持二元运算的常数表达式
    （比如类型转换），则需要给类型转换后转换为的新的数据类型*/
    ConstExp(constExpType type,Data*constData1,Data* constData2=nullptr,dataType newType=dataType::data_undefined):
    type(type),constData1(constData1),constData2(constData2),newType(newType)
    {
        if(constData2==nullptr&&type<=const_exp_fcmp_ord)
            throw std::invalid_argument("the constant expression type not match the data");
    }

    ~ConstExp(){
        delete this->constData1;
        delete this->constData2;
    }
};