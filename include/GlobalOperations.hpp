#pragma once

#include"llvm.hpp"
#include"ControlOperations.hpp"
#include"function.hpp"
#include"SymbolFactory.hpp"

//dest_sym = global ty src_sym
class GlobalNonArrayVarDefination:public LLVM{
public:
    PointerSymbol* dest_sym;
    BasicSymbol* src_sym;

    dataType getPointedType();
    PointerSymbol* getDestSymbol();
    BasicSymbol* getSrcSymbol();
    std::string out_str()const override;
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
};

/*
非初始化部分：
dest_sym = global dimensions ty 
初始化部分：
若有对第"0"维初始化(给所有数组中所有元素初始化为0) zeroinitializer 直接结束初始化部分
接下来开始遍历第一维的每一个元素，比如对a[8][9][10](类型若是i32)进行操作，以下开始举例说明
对于a[0]，包含了9*10=90个元素，如果全部初始化为0，则直接为
[9*[10*i32]] zeroinitializer，进入a[1]的初始化部分
如果不是再进入下一个维度即考虑a[0][0]，同理。
对于此处，用树来存储是否是一个可行的方式？
其实本质就是，还是上面的例子，其实我们可以看作根节点root，表示所有的a的元素，
连下来是8颗子树，每一个分别表示a[0]-a[7]，然后再接着下来
我们其实就是如果根节点被初始化了，那么就不用继续搜索这颗子树了，
否则继续搜索
使用bfs算法即可
此处目前未完成，等到之后我再来写，先写其他部分
*/
class GlobalArrayVarDefination:public LLVM{
public:
    ArraySymbol* dest_sym;

    const std::vector<int>getDimensions() const{return this->dest_sym->getDimensions();}
    dataType getArrayType(){return this->dest_sym->getArrayType();}
    std::string out_str()const override;
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
};

//define ty func(ty1 param1,ty2 param2......)
class FuncDefination:public LLVM{
public:
    FuncSymbol* func;
    std::vector<BasicSymbol*> params;


    void addArguments(dataType ty,Symbol* sym);
    void addArguments(std::vector<dataType>ty,std::vector<Symbol*>tym);
    FuncSymbol* getFuncSymbol(){return this->func;}
    dataType getReturnType(){return this->func->returnType;}
    const std::vector<dataType>getParamTypes()const {return this->func->paramTypes;}
    const std::vector<BasicSymbol*>getParams(){return this->params;}
    std::string out_str()const override;
};
