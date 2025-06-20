#pragma once

#include"data.hpp"

#define GLOBAL_SCOPE 0
#define FUNCTION_SCOPE 1
#define BLOCK_SCOPE 2

enum symType{
    sym_undefined,
    function,
    label,
    variable,
    constant_i1,
    constant_i8,
    constant_i16,
    constant_i32,
    constant_i64,
    constant_f32,
    constant_f64,
    array,
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

class Symbol {
public:
    symType type;
    std::string name;
    Data* data;
    int offset;
    int scope;
    Symbol* next;

    virtual symType getType() const;
    
    Symbol(const std::string& name)
        : name(name), type(symType::sym_undefined) , data(nullptr), offset(0), scope(0), next(nullptr) {}

    Symbol(const std::string& name,symType type)
        : name(name), type(type) , data(nullptr), offset(0), scope(0), next(nullptr) {}

};

//只考虑了指针的情况，未考虑指针的指针的情况，如需使用需后续补充
class PointerSymbol:public Symbol{
private:
    dataType PointedType;//当前指针指向的元素类型

public:
    Data* pointedData;//指向的数据

    symType getType() const override;
    dataType getPointedType() const;
    void allocateMemory(dataType elementType,ValueVariant value);
};

//包含常数符号和放在寄存器里的符号
class BasicSymbol: public Symbol{
public:
    symType getType() const override;
    dataType getDataType()const;
    void setData(dataType dtype,ValueVariant v=nullptr);
    void setType(symType type);
};

//这里只存了初始化的元素，对于作为全局变量定义的数组，都有初始值，这里可以通过scope来判断
class ArraySymbol: public Symbol{
private:
    std::vector<int> dimensions; //数组的维度信息 
    dataType arrayType;
    std::vector<int> elementNums;//比如数组a[5][6][7],则该向量中包含5*6*7,6*7,7,1表示每一个维度的"1"有几个元素
    std::vector<std::pair<std::vector<int>,BasicSymbol*>>initialedData;

    /*template<typename... Args>
        void addDimensions(Args... dims){ 
        (this->dimensions.push_back(static_cast<size_t>(dims)), ...);
    }*/

public:
    symType getType() const override;
    void allocateMemory(dataType type,std::vector<int>&dims);
    std::vector<int>getDimensions()const;
    dataType getArrayType()const;
};


//标签对应的符号
class LabelSymbol:public Symbol{
public:
    symType getType() const override;
};

//函数对应的符号
class FuncSymbol:public Symbol{
public:
    std::vector<dataType> paramTypes;
    dataType returnType;
    
    symType getType() const override;
    void addArguments(std::vector<dataType> arguments);
    void addArgument(dataType argument);
    const std::vector<dataType> getParamTypes()const;
    dataType getReturnType()const;
};

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
    BasicSymbol* constFolding();//进行常数折叠，生成一个对应的BasicSymbol*类型符号

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
