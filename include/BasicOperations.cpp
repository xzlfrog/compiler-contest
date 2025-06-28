#include "../include/BasicOperations.hpp"
#include "../include/sym.hpp"
#include "../include/llvm.hpp"
#include "../include/function.hpp"

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
        if(type>=LLVMtype::add && type <= LLVMtype::fcmp_ord){
            llvmType = type;
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
std::string ArithmeticOperationLLVM::out_str() const {}