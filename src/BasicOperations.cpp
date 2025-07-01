#include "../include/BasicOperations.hpp"
#include "../include/sym.hpp"
#include "../include/llvm.hpp"
#include "../include/function.hpp"
#include<iostream>

void ArithmeticOperationLLVM::setOperandA(BasicSymbol* operand)//set the result operand
    {
        if(this->llvmType>=icmp_eq&&this->llvmType<=fcmp_ord)
            checkType(operand->data->getType(),dataType::i1);
        else if(this->ty!=dataType::data_undefined)
            checkType(operand->data->getType(),this->ty);
        else
            this->ty=operand->data->getType();
        this->a=operand;
    }

void ArithmeticOperationLLVM::setOperandB(BasicSymbol* operand)//set the first operand
    {
        if(this->ty!=dataType::data_undefined){
            checkType(operand->data->getType(),this->ty);
        }
        else{
            this->ty=operand->data->getType();
        }
        this->b=operand;
    }

void ArithmeticOperationLLVM::setOperandC(BasicSymbol* operand)//set the first operand
    {
        if(this->ty!=dataType::data_undefined){
            checkType(operand->data->getType(),this->ty);
        }
        else{
            this->ty=operand->data->getType();
        }
        this->c=operand;
    }

void ArithmeticOperationLLVM::setLLVMType(LLVMtype type){
    if(type>=LLVMtype::llvm_fadd && type <= LLVMtype::fcmp_ord){
        this->llvmType = type;
    } else {
        throw std::invalid_argument("Invalid LLVM type for ArithmeticOperationLLVM");
    }
}

void ArithmeticOperationLLVM::setOperand(BasicSymbol* a, BasicSymbol* b, BasicSymbol *c) {
    setOperandA(a);
    setOperandB(b);
    setOperandC(c);
}

BasicSymbol* ArithmeticOperationLLVM::getA(){return this->a;}
BasicSymbol* ArithmeticOperationLLVM::getB(){return this->b;}
BasicSymbol* ArithmeticOperationLLVM::getC(){return this->c;}
dataType ArithmeticOperationLLVM::getType(){return this->ty;}

std::string ArithmeticOperationLLVM::out_str() const {
    std::string opStr;

    switch (llvmType) {
        case LLVMtype::add:   opStr = "add"; break;
        case LLVMtype::sub:   opStr = "sub"; break;
        case LLVMtype::mul:   opStr = "mul"; break;
        case LLVMtype::llvm_fadd:   opStr = "fadd"; break;
        case LLVMtype::llvm_fsub:   opStr = "fsub"; break;
        case LLVMtype::llvm_fmul:   opStr = "fmul"; break;
        case LLVMtype::llvm_frem:   opStr = "frem"; break;
        case LLVMtype::llvm_fdiv:   opStr = "fdiv"; break;
        case LLVMtype::sdiv:   opStr = "sdiv"; break;
        case LLVMtype::udiv:   opStr = "udiv"; break;
        case LLVMtype::icmp_eq:  opStr = "icmp eq"; break;
        case LLVMtype::icmp_ne:  opStr = "icmp ne"; break;
        case LLVMtype::icmp_slt: opStr = "icmp slt"; break;
        case LLVMtype::icmp_sgt: opStr = "icmp sgt"; break;
        case LLVMtype::icmp_sge: opStr = "icmp sge"; break;
        case LLVMtype::icmp_sle: opStr = "icmp sgt"; break;
        default: throw std::invalid_argument("unknown arithmetic operation");
    }

    std::string typeStr=Data::getTypeStr(ty);
    std::string b_out;
    std::string c_out;


    if(this->b->getType()==symType::constant_var||this->b->getType()==symType::variable){
        b_out=b->name;
    }
    else if(this->b->getType()==symType::constant_nonvar){
        b_out=my_to_string(b->data);
    }
    else{
        throw std::runtime_error("the type of b is wrong");
    }

    if(this->c->getType()==symType::constant_var||this->c->getType()==symType::variable){
        c_out=c->name;
    }
    else if(this->c->getType()==symType::constant_nonvar){
        c_out=my_to_string(c->data);
    }
    else{
        throw std::runtime_error("the type of c is wrong");
    }


    return a->name + " = " + opStr + " " + typeStr + " " + b_out + ", " + c_out;

}