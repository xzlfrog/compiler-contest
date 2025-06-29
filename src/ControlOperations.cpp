#include"../include/ControlOperations.hpp"

//UnconditionalBranchLLVM
LabelSymbol* UnconditionalBranchLLVM::getTarget(){return this->target;}

// Output the LLVM IR string representation
std::string UnconditionalBranchLLVM::out_str() const {
    if (target == nullptr) {
        throw std::invalid_argument("; <invalid unconditional branch>");
    }
    return "br label %" + target->name;
} 
void UnconditionalBranchLLVM::setTarget(LabelSymbol* target){this->target=target;} // Set the target label for the branch

//ReturnLLVM
BasicSymbol* ReturnLLVM::getReturnValue(){return this->returnValue;}
dataType ReturnLLVM::getReturnType(){return this->returnValue->getDataType();}
std::string ReturnLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

std::string ReturnLLVM::out_str() const{
    if (returnValue == nullptr) {
        return "ret void";
    
}
    return "ret " + getTypeStr(returnValue->getDataType()) + " %" + returnValue->name;
} // Output the LLVM IR string representation

void ReturnLLVM::setReturnValue(BasicSymbol* value){this->returnValue=value;}

//ConditionalBranchLLVM
BasicSymbol* ConditionalBranchLLVM::getCondition(){return this->condition;}
LabelSymbol* ConditionalBranchLLVM::getTrueBranch(){return this->trueBranch;}
LabelSymbol* ConditionalBranchLLVM::getFalseBranch(){return this->falseBranch;}

std::string ConditionalBranchLLVM::out_str() const {
    if (condition == nullptr || trueBranch == nullptr || falseBranch == nullptr) {
        throw std::invalid_argument("; <invalid conditional branch>");
    }

    return "br i1 %" + condition->name + ", label %" + trueBranch->name + ", label %" + falseBranch->name;
}// Output the LLVM IR string representation

// Set the condition for the branch
void ConditionalBranchLLVM::setCondition(BasicSymbol* cond){
    if(cond->getDataType()!=dataType::i1){
        throw std::runtime_error("the type of the condition is not right");
    }
    this->condition=cond;
} 
// Set the true branch LLVM IR
void ConditionalBranchLLVM::setTrueBranch(LabelSymbol* trueBranch){
    this->trueBranch=trueBranch;
} 
// Set the false branch LLVM IR
void ConditionalBranchLLVM::setFalseBranch(LabelSymbol* falseBranch){
    this->falseBranch=falseBranch;
} 

//SwitchLLVM
/*BasicSymbol* SwitchLLVM::getCondition(){return this->condition;}
LabelSymbol* SwitchLLVM::getDefaultCase(){return this->defaultCase;}
const std::vector<std::pair<BasicSymbol*,LabelSymbol*>> SwitchLLVM::getCaseValAndDest()const{return this->case_val_dest;}
// Output the LLVM IR string representation
std::string SwitchLLVM::out_str() const{
    //todo
} 
// Set the condition for the switch
void SwitchLLVM::setCondition(BasicSymbol* cond){
    this->condition=cond;
} 
// Add a case to the switch
void SwitchLLVM::addCase(BasicSymbol* case_val, LabelSymbol* case_des){
    this->case_val_dest.push_back({case_val,case_des});
} 
// Add a case to the switch
void SwitchLLVM::addCase(std::vector<BasicSymbol*> case_val, std::vector<LabelSymbol*> case_des){
    if(case_val.size()!=case_des.size()){
        throw std::invalid_argument("the size of the argument not match");
    }
    for(int i=0;i<case_val.size();i++){
        this->addCase(case_val[i],case_des[i]);
    }
} 
// Set the default case LLVM IR
void SwitchLLVM::setDefaultCase(LabelSymbol* defaultIR){
    this->defaultCase=defaultIR;
} */

//PhiLLVM
BasicSymbol* PhiLLVM::getDestSymbol(){return this->dest_sym;}
const std::vector<std::pair<BasicSymbol*,LabelSymbol*>>PhiLLVM::getValAndSrc() const{return this->vals_srcs;}
dataType PhiLLVM::getDestType(){return this->dest_sym->getDataType();}
std::string PhiLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "f32";
        case dataType::f64: return "f64";
        default: throw std::invalid_argument("Unknown data type");
    }
}

void PhiLLVM::addCase(BasicSymbol*src_sym,LabelSymbol*src_label){
    this->vals_srcs.push_back({src_sym,src_label});
}
void PhiLLVM::addCase(std::vector<BasicSymbol*> src_sym,std::vector<LabelSymbol*>src_label){
    if(src_sym.size()!=src_label.size()){
        throw std::invalid_argument("the size of the argument not match");
    }
    for(int i=0;i<src_sym.size();i++){
        this->addCase(src_sym[i],src_label[i]);
    }
}
std::string PhiLLVM::out_str() const{
    if (dest_sym == nullptr) {
        throw std::invalid_argument("; <invalid phi node>");
    }

    std::string result = "%" + dest_sym->name + " = phi " + getTypeStr(dest_sym->getDataType()) + " ";

    for (size_t i = 0; i < vals_srcs.size(); ++i) {
        if (i > 0) result += ", ";
        result += "[%" + vals_srcs[i].first->name + ", " + vals_srcs[i].second->name + "]";
    }

    return result;
}

//CallLLVM
const std::vector<dataType>& CallLLVM::getArgumentsType(){return this->function->getParamTypes();}
FuncSymbol* CallLLVM::getFuncSymbol(){return this->function;}
const std::vector<BasicSymbol*>& CallLLVM::getArguments() const{return this->arguments;}
const std::vector<dataType>& CallLLVM::getArgumentsType() const{return this->function->getParamTypes();}
dataType CallLLVM::getReturnType() {return this->function->getReturnType();}
std::string CallLLVM::getTypeStr(dataType type) const {
    switch (type) {
        case dataType::i1: return "i1";
        case dataType::i8: return "i8";
        case dataType::i16: return "i16";
        case dataType::i32: return "i32";
        case dataType::i64: return "i64";
        case dataType::f32: return "float";
        case dataType::f64: return "double";
        case dataType::void_: return "void";
        default: return "<unknown type>";
    }
} // Get the string representation of the data type

std::string CallLLVM::out_str() const {
    if (!function) {
        return "; <invalid function call>";
    }

    std::string result;
    dataType hasReturn = function->getReturnType();
    if ( hasReturn != dataType::void_) {
        result += "%" + dest_sym->name + " = ";
    }
    std::string funcType = this->getTypeStr(hasReturn);
    result += "call " + funcType + " @" + function->name + "(";

    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i > 0) result += ", ";
        std::string argType = getTypeStr(arguments[i]->getDataType());
        if (arguments[i]) {
            result += argType + " %" + arguments[i]->name;
        }
    }

    result += ")";
    return result;
} // Output the LLVM IR string representation
// Set the function to call
void CallLLVM::setFunction(FuncSymbol* func){
    this->function=func;
} 
// Add an argument to the function call
void CallLLVM::addArgument(BasicSymbol* arg){
    int n=this->arguments.size();
    if(function->paramTypes.size()<=n){
        throw std::runtime_error("too much arguments");
    }
    if(arg->getDataType()!=function->paramTypes[n]){
        throw std::invalid_argument("the argument's type do not match the parameter's type");
    }
    this->arguments.push_back(arg);
}
void CallLLVM::addArguments(std::vector<BasicSymbol*> args){
    for(auto arg : args){
        this->addArgument(arg);
    }
}
void CallLLVM::setArguments(std::vector<BasicSymbol*>& args){
    this->arguments=args;
}

//Label
LabelSymbol* Label::getLabel(){return this->label;}

    std::string Label::out_str() const{
        if (label == nullptr) {
            throw std::invalid_argument(" <invalid label>");
        }
        return label->name + ":";
}