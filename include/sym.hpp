#pragma once

#include"data.hpp"
#include"GlobalArrayInitial.hpp"

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

class Symbol {
public:
    symType type;//symbol类型，比如函数，变量，常量等等
    std::string name;//symbol的名字
    Data* data;//symbol存的值，主要是变量（在做优化时）和常量需要使用
    int offset;//偏移，和课上的实验差不多，在栈内的偏移或者在堆中的偏移
    int scope;//作用域，这次需要考虑每个基本块的作用域，gloabl 0,local 1,block 2
    Symbol* next;//下一个symbol，用于符号表的连接

    virtual symType getType() const;//返回type成员变量
};

//只考虑了指针的情况，未考虑指针的指针的情况，如需使用需后续补充
class PointerSymbol:public Symbol{
private:
    dataType PointedType;//当前指针指向的元素类型

public:
    Data* pointedData;//指向的数据

    symType getType() const override;
    dataType getPointedType() const;//获得指针指向的元素的数据类型，比如源程序中是int类型，此处就是i32
    void allocateMemory(dataType elementType,ValueVariant value);
};

//包含常数符号和放在寄存器里的符号
class BasicSymbol: public Symbol{
public:
    symType getType() const override;//返回type成员变量
    dataType getDataType()const;//返回这个符号存的数据的类型，比如i32,i1,f32等等
    void setData(dataType dtype,ValueVariant v=nullptr);//修改符号存的数据
    void setType(symType type);//修改type成员变量
};

//这里只存了初始化的元素，对于作为全局变量定义的数组，都有初始值，这里可以通过scope来判断
class ArraySymbol: public Symbol{
private:
    std::vector<int> dimensions; //数组的维度信息 
    dataType arrayType;//比如int a[2][3]，类型就是int，或者用llvm ir中的数据类型 i32
    std::vector<int> elementNums;//比如数组a[5][6][7],则该向量中包含5*6*7,6*7,7,1表示每一个维度的"1"有几个元素
    HierarchicalBitmap* initialedData;//在数组的初始化阶段需要使用，对于初始化，不考虑在初始化之后再对数组元素修改的情况，只解决了数组初始化的问题
    bool isInitialed=false;//是否被初始化
    /*template<typename... Args>
        void addDimensions(Args... dims){ 
        (this->dimensions.push_back(static_cast<size_t>(dims)), ...);
    }*/

public:
    symType getType() const override;
    void allocateMemory(dataType type,std::vector<int>&dims);
    const std::vector<int>&getDimensions() const;//数组大小
    dataType getArrayType()const;//数组保存的数据类型
    void Initialize(std::vector<int>position,Data* data);//给一个初始化的位置和对应的元素，如果是a[3][3][3]，传入position为{0}表示所有的数据初始化为data，如果传入{0,1,2}，表示a[1][2][0],a[1][2][1],a[1][2][2]都初始化为data
    std::vector<std::pair<std::vector<int>,Data*>> getInitializedData();//得到初始化的数据的位置和值，与上一个函数的参数的形式差不多
};


//标签对应的符号
class LabelSymbol:public Symbol{
public:
    symType getType() const override;
};

//函数对应的符号
class FuncSymbol:public Symbol{
public:
    std::vector<dataType> paramTypes;//参数数据类型
    dataType returnType;//返回值数据类型
    bool isDef=false;
    
    symType getType() const override;
    void addParams(std::vector<dataType>& paramTypes);//或许创建完之后还要增加参数？
    void addParam(dataType paramType);//同上
    const std::vector<dataType> getParamTypes()const;//得到函数参数类型
    dataType getReturnType()const;//返回函数返回值类型
    bool getIsDef();
};