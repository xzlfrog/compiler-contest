#pragma once

#include"llvm.hpp"
#include<vector>
#include"function.hpp"

class ControlOperationLLVM:public LLVM{

};

//
class ConditionalBranchLLVM:public ControlOperationLLVM{
public:
    Symbol* condition; // The condition for the branch
    Symbol* trueBranch;  // The LLVM IR for the true branch
    Symbol* falseBranch; // The LLVM IR for the false branch

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

//br target
class UnconditionalBranchLLVM:public ControlOperationLLVM{
public:
    Symbol* target; // The target label for the branch

    UnconditionalBranchLLVM(Symbol* target=nullptr) : target(target){
        this->llvmType = LLVMtype::br_unconditional;
    }

    std::string out_str() const override; // Output the LLVM IR string representation

    void setTarget(Symbol* target); // Set the target label for the branch
};

//return 
class ReturnLLVM:public ControlOperationLLVM{
public:
    Symbol* returnValue; // The value to return
    dataType ty;

    ReturnLLVM(Symbol* returnValue=nullptr): returnValue(returnValue){
        this->llvmType=LLVMtype::ret;
        if(returnValue==nullptr||returnValue->data==nullptr)
            return;
        ty=returnValue->data->getType();
    }

    std::string out_str() const override; // Output the LLVM IR string representation

    void setReturnValue(Symbol* value); // Set the return value
};

//call 
class CallLLVM:public ControlOperationLLVM{
public:
    Symbol* function; // The function to call

    std::vector<Symbol*> arguments; // The arguments to pass to the function

    std::vector<dataType> arguments_ty;

    CallLLVM(Symbol* func=nullptr,std::vector<Symbol*>arguments={}):function(func),arguments(arguments){
        this->llvmType=LLVMtype::call;

        if(arguments.size()!=0)
        {
            for(auto argument:arguments)
            {
                if(argument->data!=nullptr)
                    arguments_ty.push_back(argument->data->getType());
            }
        }
    }

    std::string out_str() const override; // Output the LLVM IR string representation

    void setFunction(Symbol* func); // Set the function to call

    void addArgument(Symbol* arg); // Add an argument to the function call
};

//switch (condition) case case_val_dest.first goto label case_val_dest_second
class SwitchLLVM:public ControlOperationLLVM{
public:
    Symbol* condition; // The condition for the switch

    std::vector<std::pair<Symbol*,Symbol*>> case_val_dest; //case values and destinations

    Symbol* defaultCase; // The default case LLVM IR

    SwitchLLVM(Symbol* cond=nullptr, Symbol* defaultCase=nullptr)
        : condition(cond), defaultCase(defaultCase) {
        this->llvmType = LLVMtype::llvm_switch;
    }

    std::string out_str() const override; // Output the LLVM IR string representation

    void setCondition(Symbol* cond); // Set the condition for the switch

    void addCase(Symbol* case_val, Symbol* case_des); // Add a case to the switch

    void addCase(std::vector<Symbol*> case_val, std::vector<Symbol*> case_des); // Add a case to the switch

    void setDefaultCase(Symbol* defaultIR); // Set the default case LLVM IR
};

//dest_sym=phi dest_ty [src_sym1,label1],[src_sym2,label2]......
class PhiLLVM:public ControlOperationLLVM{
public:
    Symbol* dest_sym;
    std::vector<std::pair<Symbol*,Symbol*>> vals_srcs;
    dataType dest_ty;

    PhiLLVM(Symbol* dest_sym,dataType dest_ty):
    dest_sym(dest_sym),dest_ty(dest_ty)
    {
        this->llvmType=LLVMtype::phi;
        if(dest_sym->data==nullptr)
            return;
        checkType(dest_sym->data->getType(),dest_ty);
    }

    void addCase(Symbol*src_sym,Symbol*label);

    void addCase(std::vector<Symbol*> src_sym,std::vector<Symbol*>label);

    std::string out_str() const override;

};

//label:
class Label:public ControlOperationLLVM{
public:
    Symbol* label;

    Label(Symbol* label):label(label){
        if(label->type!=symType::label)
            throw std::invalid_argument("the symbol is not a label");
        this->llvmType=LLVMtype::label;
    }
};
