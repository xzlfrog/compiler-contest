#pragma once

#include"llvm.hpp"
#include"sym.hpp"
#include<string>
#include"function.hpp"


//对于内存操作，我们只对用户定义的变量分配内存，生成的临时变量都不分配内存，这些变量会被分配到寄存器中
class MemoryOperationLLVM:public LLVM{};

//variable=alloca elementType
class AllocaLLVM:public MemoryOperationLLVM{
    public:
        Symbol* variable;
        dataType elementType;//当前指针指向的元素类型
        bool isArray;//是否是数组

        AllocaLLVM(Symbol* variable) : variable(variable) {
            this->llvmType = LLVMtype::allocate;
            this->ty = dataType::pointer;
        }

        AllocaLLVM() : variable(nullptr) {
            this->llvmType = LLVMtype::allocate;
            this->ty = dataType::pointer;
        }

        std::string out_str() const override;

        //给数组分配内存空间
        template<typename... Args>
        void AllocaArrayLLVM(dataType elementType,std::string name,Args... dims){
            Symbol* sym=new Symbol(name,symType::variable);
            sym->allocateMemory(elementType,dims...);
            sym->isArray=true;
            this->isArray=true;
            this->elementType=elementType;
            this->variable=sym;
        }

        void AllocaUnarrayLLVM(dataType elementType,std::string name){
            Symbol* sym=new Symbol(name,symType::variable);
            sym->allocateMemory(elementType);
            sym->isArray=false;
            this->isArray=false;
            this->elementType=elementType;
            this->variable=sym;
        }
};


//dest_sym = load dest_ty src_ty* src_sym
class LoadLLVM:public MemoryOperationLLVM{
public:
    Symbol* src_sym;//源操作数
    Symbol* dest_sym;//目的操作数
    dataType dest_ty;//目的操作数类型
    dataType src_ty;//src_ty*为源操作数类型

    LoadLLVM(Symbol* src_sym,Symbol* dest_sym,dataType dest_ty,dataType src_ty):
    src_sym(src_sym),dest_sym(dest_sym),dest_ty(dest_ty),src_ty(src_ty)
    {
        this->llvmType=LLVMtype::load;
        checkType(src_sym->getElementType(),src_ty);
        checkType(dest_sym->data->getType(),dest_ty);
        checkType(src_ty,dest_ty);
    }

    std::string out_str() const override;
};

//store src_ty src_sym dest_ty* dest_ty
class StoreLLVM:public MemoryOperationLLVM{
public:
    Symbol* src_sym;//源操作数
    Symbol* dest_sym;//目的操作数
    dataType dest_ty;//目的操作数类型
    dataType src_ty;//src_ty*为源操作数类型

    StoreLLVM(Symbol* src_sym,Symbol* dest_sym,dataType dest_ty,dataType src_ty):
    src_sym(src_sym),dest_sym(dest_sym),dest_ty(dest_ty),src_ty(src_ty)
    {
        this->llvmType=LLVMtype::store;
        dest_sym->setPointedElement(src_sym);
        checkType(src_sym->data->getType(),src_ty);
        checkType(dest_sym->getElementType(),dest_ty);
        checkType(src_ty,dest_ty);
    }

    std::string out_str() const override;
};

//getelementptr ty1 ty2* ptrval ,ty_idx1.first ty_idx1.second,ty_idx2.first ty_idx2.second......
class GetElementPtrLLVM:public MemoryOperationLLVM{
    dataType ty1;
    dataType ty2;
    Symbol* ptrval;
    std::vector<std::pair<dataType,Symbol*>> ty_idx;

    GetElementPtrLLVM(dataType ty1=dataType::data_undefined,dataType ty2=dataType::data_undefined,Symbol*ptrval=nullptr):
    ty1(ty1),ty2(ty2),ptrval(ptrval)
    {
        checkType(ty1,ty2);
        if(ptrval!=nullptr)
            checkType(ptrval->getElementType(),ty1);
        checkType(ty1,ty2);
    }

    void addTyIdx(dataType ty,Symbol* idx);

    void addTyIdx(std::vector<dataType>ty,std::vector<Symbol*>idx);

    std::string out_str() const override;

};
