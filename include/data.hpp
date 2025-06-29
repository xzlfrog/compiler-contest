#pragma once

#include<string>
#include<variant>
#include<stdexcept>
#include<vector>
#include<utility>
#include<variant>

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
    const_exp_pointer
};

enum constExpType{
    const_exp_add,
    const_exp_sub,
    const_exp_mul,
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
    const_exp_sitofp,//有符号整数转浮点
};

//初始化方式
enum initializer{
    zeroinitializer,//全部赋值为0
    undef,//未初始化
    assignment//通过赋值进行初始化
};

class Data;

using ValueVariant = std::variant<bool,char,short,int,long long,float,double,Data*>;

class Data {
private:
    dataType type;//数据类型
    bool isInitialized;//是否被初始化
    initializer initMode;//初始化方式
    
public:
    static std::string getTypeStr(dataType type);//得到数据类型的字符串表示
    virtual dataType getType() const{
        return this->type;
    };//得到数据类型
    //得到数据，需要使用std::holds_alternative</*你要的数据类型*/>(data->getValue())来得到数据
    virtual ValueVariant getValue(){
        throw std::runtime_error("Base Data getValue() called");
    }

    //设置对应的数据
    virtual void setValue(ValueVariant value){
        throw std::runtime_error("Base Data setValue() called");
    }
    void setIsInitialize(bool flag);//设置变量是否被初始化
    bool getIsInitialized();//变量是否被初始化
    void setInitMode(initializer initMode);//设置初始化的方式
    initializer getInitMode();//得到初始化的方式
    bool checkIsInitialed();//检查是否被初始化，在类的成员方法实现中使用

    virtual ~Data() = default;
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
    ValueVariant getValue() override;
    void setValue(ValueVariant value)override;
};

class Data_i32:public Data {
private:
    int value;
public:    
    dataType getType() const override;
    ValueVariant getValue()override;
    void setValue(ValueVariant value)override;
};

class Data_i64:public Data {
private:
    long long value;
public:    
    dataType getType() const override;
    ValueVariant getValue()override;
    void setValue(ValueVariant value)override;
};

class Data_f32:public Data {
private:
    float value;
public:    
    dataType getType() const override;
    ValueVariant getValue()override;
    void setValue(ValueVariant value)override;
};

class Data_f64:public Data {
private:
    double value;
public:    
    dataType getType() const override;
    ValueVariant getValue()override;
    void setValue(ValueVariant value)override;
};

class Data_pointer:public Data {
private:
    Data* value;
public:
    dataType getType() const override;
    ValueVariant getValue()override;
    void setValue(ValueVariant value)override;
};

Data* createData(dataType type,ValueVariant v);//type为对应的数据的类，v为这个数据初始化的值
Data* createInitialedData(dataType type);//type为对应的数据的类,生成的data类是实际上已经赋值了的，但是由于我们没有在编译器中进行计算，所以不知道它的值
Data* createData(dataType type,initializer initMode);//type为对应的数据的类,initMode表示初始化方式，比如undef和zeroinitializer
Data* createNonInitialedData(dataType type);//type为对应的数据的类,生成的data类是未经过初始化的值
Data* createData(Data* data);

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
    Data* constFolding();//进行常数折叠，生成一个对应的Data*类型变量，只支持f32和i32的折叠，如果其他需要用到再写

    /*type表示常数表达式的类型，两个data分别是运算符左右，如果是不需要支持二元运算的常数表达式
    （比如类型转换），则需要给类型转换后转换为的新的数据类型*/
    ConstExp(constExpType type,Data*constData1,Data* constData2=nullptr,dataType newType=dataType::data_undefined):
    type(type),constData1(constData1),constData2(constData2),newType(newType)
    {
        if(constData2==nullptr&&type<=const_exp_fcmp_one)
            throw std::invalid_argument("the constant expression type not match the data");
    }
};

Data* constExp_add(Data* data1,Data* data2);
Data* constExp_sub(Data* data1,Data* data2);
Data* constExp_mul(Data* data1,Data* data2);
Data* constExp_sdiv(Data* data1,Data* data2);
Data* constExp_andi(Data* data1,Data* data2);
Data* constExp_ori(Data* data1,Data* data2);
Data* constExp_xori(Data* data1,Data* data2);
Data* constExp_fadd(Data* data1,Data* data2);
Data* constExp_fsub(Data* data1,Data* data2);
Data* constExp_fmul(Data* data1,Data* data2);
Data* constExp_fdiv(Data* data1,Data* data2);
Data* constExp_icmp_eq(Data* data1,Data* data2);//integer equal
Data* constExp_icmp_ne(Data* data1,Data* data2);//integer not equal
Data* constExp_icmp_sgt(Data* data1,Data* data2);//integer signed greater than
Data* constExp_icmp_sge(Data* data1,Data* data2);//integer signed greater than or equal
Data* constExp_icmp_slt(Data* data1,Data* data2);//integer signed less than
Data* constExp_icmp_sle(Data* data1,Data* data2);// integer signed less than or equal
Data* constExp_fcmp_oeq(Data* data1,Data* data2);//float equal
Data* constExp_fcmp_ogt(Data* data1,Data* data2);//float greater than
Data* constExp_fcmp_oge(Data* data1,Data* data2);//float greater than or equal
Data* constExp_fcmp_olt(Data* data1,Data* data2);//float less than
Data* constExp_fcmp_ole(Data* data1,Data* data2);//float less than or equal
Data* constExp_fcmp_one(Data* data1,Data* data2);//float not equal
Data* constExp_sitofp(Data* data1);//有符号整数转浮点

