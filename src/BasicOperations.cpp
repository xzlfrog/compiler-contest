#include "../include/BasicOperations.hpp"
#include "../include/sym.hpp"
#include "../include/llvm.hpp"
#include "../include/function.hpp"

void ArithmeticOperationLLVM::setOperandA(Symbol* operand)//set the result operand
    {
        if(this->ty!=dataType::undefined){
            checkType(operand->data->getType(),this->ty);
        }
        else{
            this->ty=operand->data->getType();
        }
        this->a=operand;
    }

void ArithmeticOperationLLVM::setOperandB(Symbol* operand)//set the first operand
    {
        if(this->ty!=dataType::undefined){
            checkType(operand->data->getType(),this->ty);
        }
        else{
            this->ty=operand->data->getType();
        }
        this->b=operand;
    }

void ArithmeticOperationLLVM::setOperandC(Symbol* operand)//set the first operand
    {
        if(this->ty!=dataType::undefined){
            checkType(operand->data->getType(),this->ty);
        }
        else{
            this->ty=operand->data->getType();
        }
        this->c=operand;
    }

void ArithmeticOperationLLVM::setLLVMType(LLVMtype type){
        if(type>=LLVMtype::add && type <= LLVMtype::fcmp_ord){
            llvmType = type;
        } else {
            throw std::invalid_argument("Invalid LLVM type for ArithmeticOperationLLVM");
        }
    }

void ArithmeticOperationLLVM::setOperand(Symbol* a, Symbol* b, Symbol *c) {
    setOperandA(a);
    setOperandB(b);
    setOperandC(c);
}