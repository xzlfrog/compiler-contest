#include"llvm.hpp"
#include"function.hpp"

//src_ty src_sym->dest_ty dest_sym
class TypeConversionOperation:public LLVM{
public:
    Symbol* src_sym;
    dataType src_ty;
    Symbol* dest_sym;
    dataType dest_ty;

    TypeConversionOperation(LLVMtype type,Symbol* src_sym=nullptr,dataType src_ty=dataType::data_undefined
    ,Symbol* dest_sym=nullptr,dataType dest_ty=dataType::data_undefined):
    src_sym(src_sym),src_ty(src_ty),dest_sym(dest_sym),dest_ty(dest_ty)
    {
        this->llvmType=type;
        if(type<trunc||type>inttoptr)
            throw std::invalid_argument("llvm type is invalid");
        checkType(src_sym->data->getType(),src_ty);
        checkType(dest_sym->data->getType(),dest_ty);
    }
};
