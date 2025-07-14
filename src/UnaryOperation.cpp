#include"../include/UnaryOperation.hpp"

dataType UnaryOperationLLVM::getType(){
    return this->dest_sym->getDataType();
}

std::string UnaryOperationLLVM::out_str() const{
    std::string res;
    res=this->dest_sym->name;
    switch (this->llvmType)
    {
        case LLVMtype::llvm_neg:
            res=" = neg ";
            break;
        case LLVMtype::llvm_fneg:
            res=" = fneg ";
            break;
        default:
            break;
    }
    res+=Data::getTypeStr(this->dest_sym->getDataType())+" "+getSymOut(this->src_sym);
}