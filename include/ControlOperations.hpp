#include"llvm.hpp"
#include<vector>

class ControlOperationLLVM:public LLVM{

};

class ConditionalBranchLLVM:public ControlOperationLLVM{
public:
    Symbol* condition; // The condition for the branch
    Symbol* trueBranch;  // The LLVM IR for the true branch
    Symbol* falseBranch; // The LLVM IR for the false branch

    void setLLVMType(LLVMtype type) override;

    std::string out_str() const override; // Output the LLVM IR string representation

    void setCondition(Symbol* cond); // Set the condition for the branch

    void setTrueBranch(Symbol* trueBranch); // Set the true branch LLVM IR

    void setFalseBranch(Symbol* falseBranch); // Set the false branch LLVM IR

    ConditionalBranchLLVM(Symbol* cond, Symbol* trueBranch, Symbol* falseBranch)
        : condition(cond), trueBranch(trueBranch), falseBranch(falseBranch) 
        { 
            this->llvmType=LLVMtype::br_conditional; 
        }
};

class UnconditionalBranchLLVM:public ControlOperationLLVM{
public:
    Symbol* target; // The target label for the branch

    void setLLVMType(LLVMtype type) override;

    std::string out_str() const override; // Output the LLVM IR string representation

    void setTarget(Symbol* target); // Set the target label for the branch
};

class ReturnLLVM:public ControlOperationLLVM{
public:
    Symbol* returnValue; // The value to return

    void setLLVMType(LLVMtype type) override;

    std::string out_str() const override; // Output the LLVM IR string representation

    void setReturnValue(Symbol* value); // Set the return value
};

class CallLLVM:public ControlOperationLLVM{
public:
    Symbol* function; // The function to call

    std::vector<Symbol*> arguments; // The arguments to pass to the function

    void setLLVMType(LLVMtype type) override;

    std::string out_str() const override; // Output the LLVM IR string representation

    void setFunction(Symbol* func); // Set the function to call

    void addArgument(Symbol* arg); // Add an argument to the function call
};

class SwitchLLVM:public ControlOperationLLVM{
public:
    Symbol* condition; // The condition for the switch

    std::vector<Symbol*> case_val; //case values

    std::vector<Symbol*> case_dest; //case destinations

    Symbol* defaultCase; // The default case LLVM IR

    void setLLVMType(LLVMtype type) override;

    std::string out_str() const override; // Output the LLVM IR string representation

    void setCondition(Symbol* cond); // Set the condition for the switch

    void addCase(Symbol* case_val, Symbol* case_des); // Add a case to the switch

    void setDefaultCase(Symbol* defaultIR); // Set the default case LLVM IR
};