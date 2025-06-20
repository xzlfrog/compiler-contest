#include"../include/ControlOperations.hpp"

//UnconditionalBranchLLVM
LabelSymbol* UnconditionalBranchLLVM::getTarget(){return this->target;}

std::string UnconditionalBranchLLVM::out_str() const {} // Output the LLVM IR string representation
void UnconditionalBranchLLVM::setTarget(LabelSymbol* target){} // Set the target label for the branch

//ReturnLLVM
BasicSymbol* ReturnLLVM::getReturnValue(){return this->returnValue;}
dataType ReturnLLVM::getReturnType(){return this->returnValue->getDataType();}

std::string ReturnLLVM::out_str() const{}
void ReturnLLVM::setReturnValue(BasicSymbol* value){}

//ConditionalBranchLLVM
BasicSymbol* ConditionalBranchLLVM::getCondition(){return this->condition;}
LabelSymbol* ConditionalBranchLLVM::getTrueBranch(){return this->trueBranch;}
LabelSymbol* ConditionalBranchLLVM::getFalseBranch(){return this->falseBranch;}

std::string ConditionalBranchLLVM::out_str() const {}// Output the LLVM IR string representation
void ConditionalBranchLLVM::setCondition(BasicSymbol* cond){} // Set the condition for the branch
void ConditionalBranchLLVM::setTrueBranch(LabelSymbol* trueBranch){} // Set the true branch LLVM IR
void ConditionalBranchLLVM::setFalseBranch(LabelSymbol* falseBranch){} // Set the false branch LLVM IR

//SwitchLLVM
BasicSymbol* SwitchLLVM::getCondition(){return this->condition;}
LabelSymbol* SwitchLLVM::getDefaultCase(){return this->defaultCase;}
const std::vector<std::pair<BasicSymbol*,LabelSymbol*>> SwitchLLVM::getCaseValAndDest()const{return this->case_val_dest;}

std::string SwitchLLVM::out_str() const{} // Output the LLVM IR string representation
void SwitchLLVM::setCondition(BasicSymbol* cond){} // Set the condition for the switch
void SwitchLLVM::addCase(BasicSymbol* case_val, LabelSymbol* case_des){} // Add a case to the switch
void SwitchLLVM::addCase(std::vector<BasicSymbol*> case_val, std::vector<LabelSymbol*> case_des){} // Add a case to the switch
void SwitchLLVM::setDefaultCase(LabelSymbol* defaultIR){} // Set the default case LLVM IR

//PhiLLVM
BasicSymbol* PhiLLVM::getDestSymbol(){return this->dest_sym;}
const std::vector<std::pair<BasicSymbol*,LabelSymbol*>>PhiLLVM::getValAndSrc() const{return this->vals_srcs;}
dataType PhiLLVM::getDestType(){return this->dest_sym->getDataType();}

void PhiLLVM::addCase(BasicSymbol*src_sym,LabelSymbol*src_label){}
void PhiLLVM::addCase(std::vector<BasicSymbol*> src_sym,std::vector<LabelSymbol*>src_label){}
std::string PhiLLVM::out_str() const{return "";}

//CallLLVM
const std::vector<dataType>& CallLLVM::getArgumentsType(){return this->function->getParamTypes();}
FuncSymbol* CallLLVM::getFuncSymbol(){return this->function;}
const std::vector<BasicSymbol*>& CallLLVM::getArguments() const{return this->arguments;}
const std::vector<dataType>& CallLLVM::getArgumentsType() const{return this->function->getParamTypes();}

std::string CallLLVM::out_str() const {} // Output the LLVM IR string representation
void CallLLVM::setFunction(FuncSymbol* func){} // Set the function to call
void CallLLVM::addArgument(BasicSymbol* arg){} // Add an argument to the function call
void CallLLVM::addArguments(std::vector<BasicSymbol*> args){}
void CallLLVM::setArguments(std::vector<BasicSymbol*>& args){}

//Label
LabelSymbol* Label::getLabel(){return this->label;}

std::string Label::out_str() const{}