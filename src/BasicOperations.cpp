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

std::string ArithmeticOperationLLVM::out_str() const {
    std::string opStr;

    switch (llvmType) {
        case add:   opStr = "add"; break;
        case sub:   opStr = "sub"; break;
        case mul:   opStr = "mul"; break;
        case icmp_eq:  opStr = "icmp eq"; break;
        case icmp_ne:  opStr = "icmp ne"; break;
        case icmp_slt: opStr = "icmp slt"; break;
        case icmp_sgt: opStr = "icmp sgt"; break;
        case icmp_sge: opStr = "icmp sge"; break;
        case icmp_sle: opStr = "icmp sgt"; break;
        default: throw std::invalid_argument("unknown arithmetic operation");
    }

    std::string typeStr;
    switch (ty) {
        case i1:   typeStr = "i1"; break;
        case i8:   typeStr = "i8"; break;
        case i16:  typeStr = "i16"; break;
        case i32:  typeStr = "i32"; break;
        case i64:  typeStr = "i64"; break;
        case f32:  typeStr = "f32"; break;
        case f64:  typeStr = "f64"; break;
        //case pointer: typeStr = "ptr"; break;
        default:
            throw std::invalid_argument("wrong_return_type") ;
    }

    std:: string operandaType;
    std::string operandbType;
    std::string operandcType;
    switch(a->getType()){
        case symType::constant_var || symType::constant_nonvar:
            operandaType = "@";
            break;
        case symType::variable:
            operandaType = "%";
            break;
        default:
            throw std::invalid_argument("wrong_operand_type");
    }

    return operandaType + a->name + " = " + opStr + " " + typeStr + " " + operandaType + b->name + ", " + operandcType + c->name;

}