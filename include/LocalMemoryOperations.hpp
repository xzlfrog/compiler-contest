#pragma once

#include"llvm.hpp"
#include"sym.hpp"
#include<string>
#include"function.hpp"

//对于alloca分配的局部变量（全局变量不用alloca），不能进行初始化操作，而全局变量可以进行初始化操作
//对于内存操作，我们只对用户定义的变量分配内存，生成的临时变量都不分配内存，这些变量会被分配到寄存器中

//sym=alloca elementType
class AllocaNonArrayLLVM:public LLVM{
    public:
        PointerSymbol* sym;//分配内存的变量
        dataType ty=dataType::dataType_pointer;//变量的类型

        std::string out_str() const override;
        dataType getPointedType();//举个例子，虽然我们定义的是int类型的变量，
        //但是由于我们当作是把它分配到内存里，所以我们其实是把源程序中的变量变成了一个int*类型的变量来处理
        PointerSymbol* getSymbol();//返回这个指针
        ~AllocaNonArrayLLVM()=default;
};

//array=alloca [dim[0]*[dim[1]*[......arrayType]]]
class AllocaArrayLLVM:public LLVM{
    public:
        ArraySymbol* array;//分配的数组

        dataType getArrayType();//数组中元素的类型

        const std::vector<int>& getDimensions() const;//数组的大小
        ArraySymbol* getArray();//返回这个数组
        std::string out_str() const override;
        ~AllocaArrayLLVM()=default;
};


//dest_sym = load dest_ty src_ty* src_sym,该指令不能load数组，数组需要使用getelementptr
class LoadLLVM:public LLVM{
public:
    PointerSymbol* src_sym;//源操作数
    BasicSymbol* dest_sym;//目的操作数

    //dest_ty:this->getDestType()
    dataType getDestType();
    //src_ty:this->getSrcType()
    dataType getSrcPointedType();
    PointerSymbol* getSrcSymbol();
    BasicSymbol* getDestSymbol();
    std::string out_str() const override;
    ~LoadLLVM()=default;
};

//store src_ty src_sym dest_ty* dest_ty,对于数组，我们需要先getelementptr，然后对getelementptr得到的元素进行store
class StoreLLVM:public LLVM{
public:
    BasicSymbol* src_sym;//源操作数
    PointerSymbol* dest_sym;//目的操作数

    //dest_ty:this->getDestType()
    dataType getDestPointedType();
    //src_ty:this->getSrcType()
    dataType getSrcType();
    BasicSymbol* getSrcSymbol();
    PointerSymbol* getDestSymbol();
    std::string out_str() const override;
    ~StoreLLVM()=default;
};

//dest_sym=getelementptr [dim[0]*[dim[1]*......*ty1]] [dim[0]*[dim[1]*......*ty2]]* ptrval ,ty_idx1.first ty_idx1.second,ty_idx2.first ty_idx2.second......
class GetElementPtrLLVM:public LLVM{
public:
    ArraySymbol* ptrval;//数组变量
    PointerSymbol* dest_sym;//从数组中取出的元素的指针
    std::vector<std::pair<dataType,BasicSymbol*>> ty_idx;//比如i32 2,i32 3,i32 4，表示的就是取数组（假设是a）的a[2][3][4]

    //即ty1,ty2
    dataType getArrayType();
    const std::vector<int>&getDimensions() const;
    ArraySymbol* getSrcSymbol();
    PointerSymbol* getDestSymbol();
    dataType getDestPointedType();
    const std::vector<std::pair<dataType,BasicSymbol*>> getTyAndIdx();
    void addTyIdx(dataType ty,BasicSymbol* idx);
    void addTyIdx(std::vector<dataType>ty,std::vector<BasicSymbol*>idx);
    std::string out_str() const override;
    ~GetElementPtrLLVM()=default;
};

class GetElementPtrLLVM_PointerToVar:public LLVM{
public:
    ArraySymbol* src_sym;
    BasicSymbol* dest_sym;
    BasicSymbol* idx;

    dataType getArrayType();
    std::string out_str() const override;
    ~GetElementPtrLLVM_PointerToVar()=default;
};