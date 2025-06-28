#pragma once

#include"llvm.hpp"
#include"ControlOperations.hpp"
#include"function.hpp"
#include"SymbolFactory.hpp"

//dest_sym = global ty src_sym
class GlobalNonArrayVarDefination:public LLVM{
public:
    PointerSymbol* dest_sym;//定义的变量
    BasicSymbol* src_sym;//用于初始化的变量，可以通过symType确定是否是常数

    dataType getPointedType();
    PointerSymbol* getDestSymbol();
    BasicSymbol* getSrcSymbol();
    initializer getInitMode();
    std::string out_str()const override;
    ~GlobalNonArrayVarDefination()=default;
};

//dest_sym = constant ty src_sym
class ConstantNonArrayVarDefination:public LLVM{
public:
    BasicSymbol* dest_sym;
    BasicSymbol* src_sym;

    dataType getConstType();
    BasicSymbol* getDestSymbol();
    BasicSymbol* getSrcSymbol();
    initializer getInitMode();
    std::string out_str()const override;
    ~ConstantNonArrayVarDefination()=default;
};

/*
非初始化部分：
dest_sym = global dimensions ty 
*/
class GlobalArrayVarDefination:public LLVM{
public:
    ArraySymbol* dest_sym;

    const std::vector<int>getDimensions() const;//数组的大小信息
    dataType getArrayType();//数组元素类型
    //给一个初始化的位置和对应的元素，如果是a[3][3][3]，传入position为{0}表示所有的数据初始化为data，
    //如果传入{0,1,2}，表示a[1][2][0],a[1][2][1],a[1][2][2]都初始化为data
    //void Initialize(std::vector<int>position,Data* data);
    
    //得到初始化的数据的位置和值，与上一个函数的参数的形式差不多
    std::vector<std::pair<std::vector<int>,Data*>> getInitializedData();
    std::string out_str()const override;
    ~GlobalArrayVarDefination()=default;
};

class ConstantArrayVarDefination:public LLVM{
public:
    ArraySymbol* dest_sym;

    const std::vector<int>getDimensions() const;
    dataType getArrayType();
    //void Initialize(std::vector<int>position,Data* data);
    std::vector<std::pair<std::vector<int>,Data*>> getInitializedData();
    std::string out_str()const override;
    ~ConstantArrayVarDefination()=default;
};

//declare ty func (ty1,ty2......)
class FuncDeclaration:public LLVM{
public:
    FuncSymbol* func;

    void addArguments(dataType ty);
    void addArguments(std::vector<dataType>ty);
    FuncSymbol* getFuncSymbol();
    dataType getReturnType();
    const std::vector<dataType>getParamTypes()const;
    std::string out_str()const override;
    ~FuncDeclaration()=default;
};

//define ty func(ty1 param1,ty2 param2......)
class FuncDefination:public LLVM{
public:
    FuncSymbol* func;
    std::vector<BasicSymbol*> params;


    void addArguments(dataType ty,BasicSymbol* sym);
    void addArguments(std::vector<dataType>ty,std::vector<BasicSymbol*>sym);
    FuncSymbol* getFuncSymbol();
    dataType getReturnType();
    const std::vector<dataType>getParamTypes()const ;
    const std::vector<BasicSymbol*>getParams();
    std::string out_str()const override;
    ~FuncDefination()=default;
};