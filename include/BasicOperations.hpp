#include"sym.hpp"
#include"llvm.hpp"

//a=b op c;
class ArithmeticOperationLLVM : public LLVM{

public:
    Symbol* a;//result
    Symbol* b;//operand 1
    Symbol* c;//operand 2

    void setLLVMType(LLVMtype type) override;

    std::string out_str() const override;//output the LLVM IR string representation
    
    void setOperandA(Symbol* operand);//set the result operand

    void setOperandB(Symbol* operand);//set the first operand

    void setOperandC(Symbol* operand);//set the second operand

    void setOperand(Symbol* a,Symbol* b,Symbol *c);

};

typedef ArithmeticOperationLLVM LogicalOperationLLVM;

typedef ArithmeticOperationLLVM CmpOperationLLVM;


