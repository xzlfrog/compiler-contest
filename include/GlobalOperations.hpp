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
    void out_arm_str() override;
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
    void out_arm_str() override;
    ~ConstantNonArrayVarDefination()=default;
};

/*
非初始化部分：
dest_sym = global dimensions ty 
*/
class GlobalArrayVarDefination:public LLVM{
public:
    ArraySymbol* dest_sym;

    const std::vector<int>&getDimensions() const;//数组的大小信息
    dataType getArrayType();//数组元素类型
    
    //得到初始化的数据的位置和值，与上一个函数的参数的形式差不多
    const std::vector<std::pair<std::vector<int>,Data*>>& getInitializedData();
    std::string out_str()const override;
    void out_arm_str() override;
    ~GlobalArrayVarDefination()=default;
};

class ConstantArrayVarDefination:public LLVM{
public:
    ArraySymbol* dest_sym;

    const std::vector<int>&getDimensions() const;
    dataType getArrayType();
    //void Initialize(std::vector<int>position,Data* data);
    const std::vector<std::pair<std::vector<int>,Data*>>& getInitializedData();
    std::string out_str()const override;
    void out_arm_str() override;
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
    std::string getReturnTypeStr(dataType returnType) const;
    std::string getParamTypeStr(dataType paramType) const;
    void out_arm_str() override;
    ~FuncDeclaration()=default;
};

//define ty func(ty1 param1,ty2 param2......)
class FuncDefination:public LLVM{
public:
    FuncSymbol* func;
    std::vector<Symbol*> params;
    LLVM* block_tail=nullptr;


    void addArguments(dataType ty,BasicSymbol* sym);
    void addArguments(std::vector<dataType>ty,std::vector<BasicSymbol*>sym);
    FuncSymbol* getFuncSymbol();
    dataType getReturnType();
    std::string getReturnTypeStr(dataType returnType) const;
    std::string getParamTypeStr(dataType paramType) const;
    const std::vector<dataType>getParamTypes()const ;
    const std::vector<Symbol*>getParams();
    std::string out_str()const override;
    void out_arm_str() override;
    ~FuncDefination()=default;
};