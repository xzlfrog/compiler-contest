#include "../../include/backend/out_arm.hpp"
#include "../../include/llvm.hpp"

void outputModule(Module *module) {
    OutArm out("output.s");
    out.outputModule(module);
}

void OutArm::outString(FILE* file, const std::string &str) const {
    if (file) {
        fprintf(file, "%s\n", str.c_str());
    }
}
std::string LLVM::out_arm_str() const {
}

std::string ArithmeticOpConvert(LLVMtype *op) {
    switch (*op) {
        case llvm_fadd: return "FADD";
        case llvm_fsub: return "FSUB";
        case llvm_fmul: return "FMUL";
        case llvm_fdiv: return "FDIV";

        case add: return "ADD";
        case sub: return "SUB";
        case mul: return "MUL";
        case udiv: return "UDIV";
        case sdiv: return "SDIV";

        case logical_and: return "AND";
        case logical_or: return "OR";
        
        default: throw std::invalid_argument("Unsupported LLVM type for ARM conversion");
    }

}

std::string OutArm::getIntNumberOfOperands(ConstVarSymbol *constvarsym) const {
    ValueVariant number = constvarsym->data->getValue();
    if (std::holds_alternative<int>(number)) {
        if(std::get<int>(number) == 0) {
            return "XZR"; // ARM zero register
        }
        return "#" + std::to_string(std::get<int>(number));
    }
}


void ArithmeticOperationLLVM::out_arm_str() const {
    std::string op_str = ArithmeticOpConvert(&this->llvmType);

    switch(&this->llvmType){
        case llvm_fadd:
        case llvm_fsub:
        case llvm_fmul:
        case llvm_fdiv:
        case add:
        case sub:
        case mul:
        case udiv:
        case sdiv:
        case logical_and:
        case logical_or:
            OutArm::outString(OutArm::ASMDOperation(&this));
            break;
        case llvm_frem:
        case urem:
        case srem:
            OutArm::outString(OutArm::RemOperation(&this));
            break;
        case icmp_eq:
        case icmp_ne:
        case icmp_sgt:
        case icmp_sge:
        case icmp_slt:
        case icmp_sle:
            OutArm::outString(OutArm::ComparisonOperation(&this));
            break;

        default:
            throw std::invalid_argument("Unsupported LLVM type for ARM conversion");
    }
    
}

std::string OutArm::RemOperation(ArithmeticOperationLLVM* REMllvm){
    std::string a_str, b_str, c_str, tmp_str, op1, op2, op3;
    VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);

    switch (REMllvm->llvmType) {
    case llvm_frem:
        op1 = "FDIV";
        op2 = "FMUL";    
        op3 = "FSUB";
        break;
    
    case urem:
        op1 = "UDIV";
        op2 = "MUL";
        op3 = "SUB";
        break;
    
    case srem:
        op1 = "SDIV";
        op2 = "MUL";
        op3 = "SUB";
        break;       
    }
    a_str = RegisterAllocator::accessVariable(REMllvm->a);
    tmp_str = RegisterAllocator::accessVariable(tmp);
    if(REMllvm->b->symType == symType::constant_var || symType::constant_nonvar) {
        b_str = getIntNumberOfOperands(REMllvm->b);
    }else if(REMllvm->b->Data->getType() == dataType::f32) {
        b_str = VRegAllocator::accessVariable(REMllvm->b);
    }else if(REMllvm->b->Data->getType() == dataType::i32) {
        b_str = XRegAllocator::accessVariable(REMllvm->b);
    }
    if(ASMDllvm->c->symType == symType::constant_var || symType::constant_nonvar) {
        c_str = getIntNumberOfOperands(ASMDllvm->c);
    }else if(ASMDllvm->c->Data->getType() == dataType::f32) {
        c_str = VRegAllocator::accessVariable(ASMDllvm->c);
    }else if(ASMDllvm->c->Data->getType() == dataType::i32) {
        c_str = XRegAllocator::accessVariable(ASMDllvm->c);
    }

    return op1 + " " + tmp_str + ", " + b_str + ", " + c_str + "\n" +
           op2 + " " + tmp_str + ", " + tmp_str + ", " + c_str + "\n" +
           op3 + " " + a_str + ", " + a_str + ", " + tmp_str;
    
}

std::string OutArm::ASMDOperation(ArithmeticOperationLLVM* ASMDllvm){
    
    std::string a_str, b_str, c_str, op;

    op = ArithmeticOpConvert(&ASMDllvm->llvmType);
    a_str = RegisterAllocator::accessVariable(ASMDllvm->a);

    if(ASMDllvm->b->symType == symType::constant_var || symType::constant_nonvar) {
        b_str = getIntNumberOfOperands(ASMDllvm->b);
    }else if(ASMDllvm->b->Data->getType() == dataType::f32) {
        b_str = VRegAllocator::accessVariable(ASMDllvm->b);
    }else if(ASMDllvm->b->Data->getType() == dataType::i32) {
        b_str = XRegAllocator::accessVariable(ASMDllvm->b);
    }

    if(ASMDllvm->c->symType == symType::constant_var || symType::constant_nonvar) {
        c_str = getIntNumberOfOperands(ASMDllvm->c);
    }else if(ASMDllvm->c->Data->getType() == dataType::f32) {
        c_str = VRegAllocator::accessVariable(ASMDllvm->c);
    }else if(ASMDllvm->c->Data->getType() == dataType::i32) {
        c_str = XRegAllocator::accessVariable(ASMDllvm->c);
    }

    return op + " " + a_str + ", " + b_str + ", " + c_str;
}

std::string OutArm::ComparisonOperation(ArithmeticOperationLLVM* cmpllvm) {
    std::string a_str, b_str, c_str, tmp_str, op0, op1, op2;
    VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
    op0 = "CMP";
    op1 = "CSET";

    switch(cmpllvm->llvmType) {
        case icmp_eq:
            op2 = "EQ";
            break;
        case icmp_ne:
            op2 = "NE";
            break;
        case icmp_sgt:
            op2 = "GT";
            break;
        case icmp_sge:
            op2 = "GE";
            break;
        case icmp_slt:
            op2 = "LT";
            break;
        case icmp_sle:
            op2 = "LE";
            break;
        default:
            throw std::invalid_argument("Unsupported comparison type for ARM conversion");
    }

    a_str = RegisterAllocator::accessVariable(cmpllvm->a);
    tmp_str = RegisterAllocator::accessVariable(tmp);
    b_str = RegisterAllocator::accessVariable(cmpllvm->b);
    c_str = RegisterAllocator::accessVariable(cmpllvm->c);

    return op0 + " " + b_str + ", " + c_str + "\n" +
           op1 + " " + a_str + ", " + op2 ;
           
}

void UnconditionalBranchLLVM::out_arm_str() const {
    std::string target_str = this->target->getName();
    OutArm::outString("B " + target_str);
}

void ConditionalBranchLLVM::out_arm_str() const {
    std::string condition_str = RegisterAllocator::accessVariable(condition);
    std::string true_branch_str = this->trueBranch->getName();
    std::string false_branch_str = this->falseBranch->getName();

    OutArm::outString("CBZ " + condition_str + ", " + true_branch_str);
    OutArm::outString("CBNZ " + condition_str + ", " + false_branch_str);
}

void ReturnLLVM::out_arm_str() const {
    if (this->returnValue) {
        std::string return_value_str = RegisterAllocator::accessVariable(this->returnValue);
        OutArm::outString("MOV X0, " + return_value_str); // Assuming X0 is the return register
    }
    OutArm::outString("RET");
}

void CallLLVM::out_arm_str() const {
    std::string func_name = this->function->getName();
    std::string dest_str = RegisterAllocator::accessVariable(this->dest_sym);

    for (const auto& arg : this->arguments) {
        std::string arg_str = RegisterAllocator::accessVariable(arg);
        OutArm::outString("MOV " + arg_str + ", X" + std::to_string(&arg - &this->arguments[0] + 1)); // X1, X2, ...
    }

    std::string call_str = "BL " + func_name;
    OutArm::outString(call_str);
    if (this->dest_sym) {
        OutArm::outString("MOV " + dest_str + ", X0"); // Assuming X0 is the return register
    }


}

void Label::out_arm_str() const {
    std::string label_name = this->label->getName();
    OutArm::outString(label_name + ":");
}

void PhiLLVM::out_arm_str() const {
    return  ;
}