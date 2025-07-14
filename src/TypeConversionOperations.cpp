#include"../include/TypeConversionOperations.hpp"

//TypeConversionOperation::
BasicSymbol* TypeConversionOperation::getSrcSymbol(){return this->src_sym;}
BasicSymbol* TypeConversionOperation::getDestSymbol(){return this->dest_sym;}
dataType TypeConversionOperation::getSrcType(){return this->src_sym->getDataType();}
dataType TypeConversionOperation::getDestType(){return this->dest_sym->getDataType();}

std::string TypeConversionOperation::out_str() const {
    std::string res;
    res=this->dest_sym->getName()+=" = ";
    switch (this->llvmType)
    {
    case LLVMtype::fpext:
        res+="fpext "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::fptosi:
        res+="fptosi "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::fptoui:
        res+="fptoui "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::fptrunc:
        res+="fptrunc "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::sext:
        res+="sext "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::sitofp:
        res+="sitofp "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::uitofp:
        res+="uitofp "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::zext:
        res+="zext "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break; 
    case LLVMtype::bitcast:
        res+="bitcast "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::llvm_trunc:
        res+="trunc "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    //case LLVMtype::addrspacecast:
        //res+="addrspacecast ";
        //break;
    case LLVMtype::ptrtoint:
        res+="ptrtoint "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+"* to "+Data::getTypeStr(this->dest_sym->getDataType());
        break;
    case LLVMtype::inttoptr:
        res+="inttoptr "+Data::getTypeStr(this->src_sym->getDataType())+" "+getSymOut(this->src_sym)+" to "+Data::getTypeStr(this->dest_sym->getDataType())+"*";
        break; 
    default:
        throw std::runtime_error("the type of the typeConversion llvm is wrong");
        break;
    }
    return res;
}