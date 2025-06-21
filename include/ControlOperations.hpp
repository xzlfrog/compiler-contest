#pragma once

#include"llvm.hpp"
#include<vector>
#include"function.hpp"

class ControlOperationLLVM:public LLVM{

};

class ConditionalBranchLLVM:public ControlOperationLLVM{
public:
    BasicSymbol* condition; // The condition for the branch
    LabelSymbol* trueBranch;  // The LLVM IR for the true branch
    LabelSymbol* falseBranch; // The LLVM IR for the false branch

    std::string out_str() const override; // Output the LLVM IR string representation
    void setCondition(BasicSymbol* cond); // Set the condition for the branch
    void setTrueBranch(LabelSymbol* trueBranch); // Set the true branch LLVM IR
    void setFalseBranch(LabelSymbol* falseBranch); // Set the false branch LLVM IR
    BasicSymbol* getCondition();
    LabelSymbol* getTrueBranch();
    LabelSymbol* getFalseBranch();
};

//br target
class UnconditionalBranchLLVM:public ControlOperationLLVM{
public:
    LabelSymbol* target; // The target label for the branch

    std::string out_str() const override; // Output the LLVM IR string representation
    void setTarget(LabelSymbol* target); // Set the target label for the branch
    LabelSymbol* getTarget();
};

//return 
class ReturnLLVM:public ControlOperationLLVM{
public:
    BasicSymbol* returnValue; // The value to return

    std::string out_str() const override; // Output the LLVM IR string representation
    void setReturnValue(BasicSymbol* value); // Set the return value
    BasicSymbol* getReturnValue();
    dataType getReturnType();
};

//call 
class CallLLVM:public ControlOperationLLVM{
public:
    FuncSymbol* function; // The function to call
    std::vector<BasicSymbol*> arguments; // The arguments to pass to the function

    std::string out_str() const override; // Output the LLVM IR string representation
    void setFunction(FuncSymbol* func); // Set the function to call
    void addArgument(BasicSymbol* arg); // Add an argument to the function call
    void addArguments(std::vector<BasicSymbol*> args);
    void setArguments(std::vector<BasicSymbol*>& args);
    const std::vector<dataType>& getArgumentsType();
    FuncSymbol* getFuncSymbol();
    const std::vector<BasicSymbol*>& getArguments() const;
    const std::vector<dataType>& getArgumentsType() const;
    dataType getReturnType();
};

//switch (condition) case case_val_dest.first goto label case_val_dest_second
class SwitchLLVM:public ControlOperationLLVM{
public:
    BasicSymbol* condition; // The condition for the switch
    std::vector<std::pair<BasicSymbol*,LabelSymbol*>> case_val_dest; //case values and destinations
    LabelSymbol* defaultCase; // The default case LLVM IR

    std::string out_str() const override; // Output the LLVM IR string representation
    void setCondition(BasicSymbol* cond); // Set the condition for the switch
    void addCase(BasicSymbol* case_val, LabelSymbol* case_des); // Add a case to the switch
    void addCase(std::vector<BasicSymbol*> case_val, std::vector<LabelSymbol*> case_des); // Add a case to the switch
    void setDefaultCase(LabelSymbol* defaultIR); // Set the default case LLVM IR
    BasicSymbol* getCondition();
    LabelSymbol* getDefaultCase();
    const std::vector<std::pair<BasicSymbol*,LabelSymbol*>> getCaseValAndDest()const;
};

//dest_sym=phi dest_ty [src_sym1,label1],[src_sym2,label2]......
class PhiLLVM:public ControlOperationLLVM{
public:
    BasicSymbol* dest_sym;//被赋值的变量
    std::vector<std::pair<BasicSymbol*,LabelSymbol*>> vals_srcs;//源操作数和来自哪个基本块

    void addCase(BasicSymbol*src_sym,LabelSymbol*src_label);
    void addCase(std::vector<BasicSymbol*> src_sym,std::vector<LabelSymbol*>src_label);
    std::string out_str() const override;
    BasicSymbol* getDestSymbol();
    const std::vector<std::pair<BasicSymbol*,LabelSymbol*>>getValAndSrc() const;
    dataType getDestType();

};

//label:
class Label:public ControlOperationLLVM{
public:
    LabelSymbol* label;

    std::string out_str() const override;
    LabelSymbol* getLabel();
};