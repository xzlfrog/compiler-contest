#pragma once

#include"llvm.hpp"
#include"sym.hpp"
#include<string>
#include"function.hpp"

//对于alloca分配的局部变量（全局变量不用alloca），不能进行初始化操作，而全局变量可以进行初始化操作
//对于内存操作，我们只对用户定义的变量分配内存，生成的临时变量都不分配内存，这些变量会被分配到寄存器中
class LocalMemoryOperationLLVM:public LLVM{};

//sym=alloca elementType
class AllocaNonArrayLLVM:public LocalMemoryOperationLLVM{
    public:
        PointerSymbol* sym;
        dataType ty=dataType::pointer;

        std::string out_str() const override;
        dataType getPointedType();
        PointerSymbol* getSymbol();
};

//array=alloca [dim[0]*[dim[1]*[......arrayType]]]
class AllocaArrayLLVM:public LocalMemoryOperationLLVM{
    public:
        ArraySymbol* array;

        dataType getArrayType();
        const std::vector<int>& getDimensions() const;
        ArraySymbol* getArray();
        std::string out_str() const override;
};


//dest_sym = load dest_ty src_ty* src_sym,该指令不能load数组，数组需要使用getelementptr
class LoadLLVM:public LocalMemoryOperationLLVM{
public:
    PointerSymbol* src_sym;//源操作数
    BasicSymbol* dest_sym;//目的操作数

    //dest_ty:this->getDestType()
    dataType getDestType();
    //src_ty:this->getSrcType()
    dataType getSrcType();
    PointerSymbol* getSrcSymbol();
    BasicSymbol* getDestSymbol();
    std::string out_str() const override;
};

//store src_ty src_sym dest_ty* dest_ty,对于数组，我们需要先getelementptr，然后对getelementptr得到的元素进行store
class StoreLLVM:public LocalMemoryOperationLLVM{
public:
    BasicSymbol* src_sym;//源操作数
    PointerSymbol* dest_sym;//目的操作数

    //dest_ty:this->getDestType()
    dataType getDestType();
    //src_ty:this->getSrcType()
    dataType getSrcType();
    BasicSymbol* getSrcSymbol();
    PointerSymbol* getDestSymbol();
    std::string out_str() const override;
};

//dest_sym=getelementptr [dim[0]*[dim[1]*......*ty1]] [dim[0]*[dim[1]*......*ty2]]* ptrval ,ty_idx1.first ty_idx1.second,ty_idx2.first ty_idx2.second......
class GetElementPtrLLVM:public LocalMemoryOperationLLVM{
public:
    ArraySymbol* ptrval;
    BasicSymbol* dest_sym;
    std::vector<std::pair<dataType,BasicSymbol*>> ty_idx;

    //即ty1,ty2
    dataType getArrayType();
    const std::vector<int>&getDimensions() const;
    ArraySymbol* getSrcSymbol();
    BasicSymbol* getDestSymbol();
    const std::vector<std::pair<dataType,BasicSymbol*>> getTyAndIdx();
    void addTyIdx(dataType ty,BasicSymbol* idx);
    void addTyIdx(std::vector<dataType>ty,std::vector<BasicSymbol*>idx);
    std::string out_str() const override;
};
