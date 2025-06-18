#include"llvm.hpp"
#include"function.cpp"
#include"ControlOperations.hpp"
#include"function.hpp"

//dest_sym = global ty src_sym || dest_sym = constant ty src_sym
class GlobalNonArrayVarDefination:public LLVM{
public:
    Symbol* dest_sym;
    Symbol* src_sym;
    dataType ty;

    GlobalNonArrayVarDefination(LLVMtype type,Symbol* dest_sym,Symbol* src_sym,dataType ty):
    dest_sym(dest_sym),src_sym(src_sym),ty(ty)
    {
        this->llvmType=type;
        //如果是global初始化的，那么需要存到内存里面
        if(type==LLVMtype::global_def){
            dest_sym->allocateMemory(ty);
            dest_sym->setPointedElement(src_sym);
        }
        dest_sym->isArray=false;
    }
};


//dest_sym = global dimensions ty 
class GlobalArrayVarDefination:public LLVM{
public:
    Symbol* dest_sym;
    Symbol* src_sym;
    dataType ty;
};

//declare ty func (ty1 arg1,ty2 arg2......)
class FuncDeclaration:public LLVM{
public:
    dataType returnTy;
    Symbol* func;
    std::vector<std::pair<dataType,Symbol*>> arguments;

    FuncDeclaration(dataType returnTy,Symbol* func):
    returnTy(returnTy),func(func){
        this->llvmType=func_decl;
    }

    void addArguments(dataType ty,Symbol* sym);

    void addArguments(std::vector<dataType>ty,std::vector<Symbol*>tym);
    
};

//
class FuncDefination:public LLVM{
public:
    dataType returnTy;
    Symbol* func;
    std::vector<std::pair<dataType,Symbol*>> arguments;
    LLVM* block_;

    FuncDefination(dataType returnTy,Symbol* func):
    returnTy(returnTy),func(func){
        this->llvmType=func_decl;
        block_=new Label(get_tmp_label());
    }

    void addArguments(dataType ty,Symbol* sym);

    void addArguments(std::vector<dataType>ty,std::vector<Symbol*>tym);

};
