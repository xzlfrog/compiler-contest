#pragma once

#include"llvm.hpp"
#include<vector>
#include"function.hpp"

class ConditionalBranchLLVM:public LLVM{
public:
    BasicSymbol* condition; // The condition for the branch
    LabelSymbol* trueBranch;  // The LLVM IR for the true branch
    LabelSymbol* falseBranch; // The LLVM IR for the false branch

    std::string out_str() const override; // Output the LLVM IR string representation
    void out_arm_str() override;
    void setCondition(BasicSymbol* cond); // Set the condition for the branch
    void setTrueBranch(LabelSymbol* trueBranch); // Set the true branch LLVM IR
    void setFalseBranch(LabelSymbol* falseBranch); // Set the false branch LLVM IR
    BasicSymbol* getCondition();
    LabelSymbol* getTrueBranch();
    LabelSymbol* getFalseBranch();
    ~ConditionalBranchLLVM()=default;
};

//br target
class UnconditionalBranchLLVM:public LLVM{
public:
    LabelSymbol* target; // The target label for the branch

    std::string out_str() const override; // Output the LLVM IR string representation
    void out_arm_str() override;
    void setTarget(LabelSymbol* target); // Set the target label for the branch
    LabelSymbol* getTarget();
    ~UnconditionalBranchLLVM()=default;
};

//return 
class ReturnLLVM:public LLVM{
public:
    BasicSymbol* returnValue; // The value to return

    std::string out_str() const override; // Output the LLVM IR string representation
    void out_arm_str() override;
    void setReturnValue(BasicSymbol* value); // Set the return value
    BasicSymbol* getReturnValue();//未检查return的类型是否和函数的返回值类型相匹配
    dataType getReturnType();
    ~ReturnLLVM()=default;
};

//call 
class CallLLVM:public LLVM{
public:
    FuncSymbol* function; // The function to call
    BasicSymbol* dest_sym; // The destination symbol to store the return value
    std::vector<Symbol*> arguments; // The arguments to pass to the function

    std::string out_str() const override; // Output the LLVM IR string representation
    void out_arm_str() override;
    void setFunction(FuncSymbol* func); // Set the function to call
    void addArgument(Symbol* arg); // Add an argument to the function call
    void addArguments(std::vector<Symbol*> args);
    void setArguments(std::vector<Symbol*>& args);
    const std::vector<dataType>& getArgumentsType();
    FuncSymbol* getFuncSymbol();
    const std::vector<Symbol*>& getArguments() const;
    const std::vector<dataType>& getArgumentsType() const;
    dataType getReturnType();
    ~CallLLVM()=default;
};

//switch (condition) case case_val_dest.first goto label case_val_dest_second
/*class SwitchLLVM:public ControlOperationLLVM{
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
};*/

//dest_sym=phi dest_ty [src_sym1,label1],[src_sym2,label2]......
class PhiLLVM:public LLVM{
public:
    BasicSymbol* dest_sym;//被赋值的变量
    std::vector<std::pair<BasicSymbol*,LabelSymbol*>> vals_srcs;//源操作数和来自哪个基本块

    void addCase(BasicSymbol*src_sym,LabelSymbol*src_label);
    void addCase(std::vector<BasicSymbol*> src_sym,std::vector<LabelSymbol*>src_label);
    std::string out_str() const override;
    void out_arm_str() override;
    BasicSymbol* getDestSymbol();
    const std::vector<std::pair<BasicSymbol*,LabelSymbol*>>&getValAndSrc() const;
    dataType getDestType();

    ~PhiLLVM()=default;
};

//label:
class Label:public LLVM{
public:
    LabelSymbol* label;

    std::string out_str() const override;
    void out_arm_str() override;
    LabelSymbol* getLabel();
    ~Label()=default;
};