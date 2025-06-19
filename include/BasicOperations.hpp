#pragma once

#include"sym.hpp"
#include"llvm.hpp"

//a=b op c;
class ArithmeticOperationLLVM : public LLVM{

public:
    BasicSymbol* a;//result
    BasicSymbol* b;//operand 1
    BasicSymbol* c;//operand 2
    dataType ty;//b,c的数据类型，只有比较指令a，b，c的数据类型不同，此时a的类型位i1，其他时候三者数据类型相同

    void setLLVMType(LLVMtype type);

    std::string out_str() const override;//output the LLVM IR string representation
    
    void setOperandA(BasicSymbol* operand);//set the result operand

    void setOperandB(BasicSymbol* operand);//set the first operand

    void setOperandC(BasicSymbol* operand);//set the second operand

    void setOperand(BasicSymbol* a,BasicSymbol* b,BasicSymbol *c);

    BasicSymbol* getA(){return this->a;}
    BasicSymbol* getB(){return this->b;}
    BasicSymbol* getC(){return this->c;}

};

typedef ArithmeticOperationLLVM LogicalOperationLLVM;

typedef ArithmeticOperationLLVM CmpOperationLLVM;
