#include "../../include/backend/out_arm.hpp"
#include "../../include/backend/StaAlloca.hpp"
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
        case logical_xor: return "EOR"; // 异或在ARM中用EOR指令实现
        
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
    //phi语句没有直接翻译捏。。。
}

//全局变量将会统一在文件顶部输出

void GlobalNonArrayVarDefination::out_arm_str() const {
    void GlobalAllocator::allocateGlobal(dest_sym);
}

void ConstantNonArrayVarDefination::out_arm_str() const {
    void GlobalAllocator::allocateGlobal(dest_sym);
}

void GlobalArrayVarDefination::out_arm_str() const {
    void GlobalAllocator::allocateArray(dest_sym);
}

void ConstantArrayVarDefination::out_arm_str() const {
    void GlobalAllocator::allocateArray(dest_sym);
}

//函数声明暂时不翻译？
void FuncDeclaration::out_arm_str() const {
    // 函数声明不需要输出 ARM 汇编代码
}

//没有写出函数的emit
void FuncDefination::out_arm_str() const {
    // 函数定义需要输出 ARM 汇编代码
    std::string func_name = this->func->getName();
    OutArm::outString(func_name + ":");
    
    int stack_size = StackAllocator::calculateStackSize(&this);
    OutArm::outString(StackAllocator::emitPrologue(stack_size));

    // 输出函数参数
    for (const auto& param : this->params) {
        std::string param_str = RegisterAllocator::accessVariable(param);
        OutArm::outString("MOV " + param_str + ", X" + std::to_string(&param - &this->params[0] + 1)); // X1, X2, ...
    }

    // 输出函数体的 LLVM 指令
    //for (LLVM* llvm = this->block_tail; llvm != nullptr; llvm = llvm->next) {
    //
        llvm->out_arm_str();
}


void AllocaNonArrayLLVM::out_arm_str() const {
    std::string var_str = RegisterAllocator::accessVariable(this->dest_sym);
    int size = StackAllocator::allocateLocal(this->dest_sym);
    OutArm::outString("SUB SP, SP, #" + std::to_string(size));
    OutArm::outString("MOV " + var_str + ", SP");
}

void AllocaArrayLLVM::out_arm_str() const {
    std::string array_str = RegisterAllocator::accessVariable(this->array);
    int size = StackAllocator::allocateLocal(this->array);
    OutArm::outString("SUB SP, SP, #" + std::to_string(size));
    OutArm::outString("MOV " + array_str + ", SP");
}

void LoadLLVM::out_arm_str() const {
    std::string src_str = RegisterAllocator::accessVariable(this->src_sym);
    int offset = StackAllocator::getOffset(this->src_sym);
    std::string dest_str = RegisterAllocator::accessVariable(this->dest_sym);
    OutArm::outString("LDR " + src_str + ", [SP, #" + std::to_string(offset) + "]");
}

void StoreLLVM::out_arm_str() const {
    std::string src_str = RegisterAllocator::accessVariable(this->src_sym);
    int offset = StackAllocator::getOffset(this->dest_sym);
    std::string dest_str = RegisterAllocator::accessVariable(this->dest_sym);
    
    OutArm::outString("STR " + src_str + ", [SP, #" + std::to_string(offset) + "]");
}

//未对齐 可能有隐患
void GetElementPtrLLVM::out_arm_str() const {
    std::string base_ptr = RegisterAllocator::accessVariable(this->ptrval);

    int offset = StackAllocator::getOffset(this->ptrval);
    for (auto dim : ty_idx) {
        if (dim.first == dataType::i32) {
            offset += dim.second->data->getValue<int>() * StackAllocator::getTypeSize(dim.first);
        } else {
            throw std::invalid_argument("Unsupported dimension type for ARM conversion");
        }
    }

    StackAllocator::addPtr(this->dest_sym, offset);
}

void TypeConversionOperation::out_arm_str() const {
    std::string src_str = RegisterAllocator::accessVariable(this->src_sym);
    std::string dest_str = RegisterAllocator::accessVariable(this->dest_sym);

    switch (this->llvmType) {
        case llvm_trunc:
            OutArm::outString("TRUNC " + dest_str + ", " + src_str);
            break;
        case zext:
            OutArm::outString("ZEXT " + dest_str + ", " + src_str);
            break;
        case sext:
            OutArm::outString("SEXT " + dest_str + ", " + src_str);
            break;
        case bitcast:
            OutArm::outString("BITCAST " + dest_str + ", " + src_str);
            break;
        case fptrunc:
            OutArm::outString("FPTRUNC " + dest_str + ", " + src_str);
            break;
        case fpext:
            OutArm::outString("FPEXT " + dest_str + ", " + src_str);
            break;
        case fptoui:
            OutArm::outString("FPTUOI " + dest_str + ", " + src_str);
            break;
        case fptosi:
            OutArm::outString("FPTOSI " + dest_str + ", " + src_str);
            break;
        case uitofp:
            OutArm::outString("UITOFP " + dest_str + ", " + src_str);
            break;
        case sitofp:
            OutArm::outString("SITOFP " + dest_str + ", " + src_str);
            break;
        case ptrtoint:
            OutArm::outString("PTRTOINT " + dest_str + ", " + src_str);
            break;
        case inttoptr:
            OutArm::outString("INTTOPTR " + dest_str + ", " + src_str);
            break;
        default:
            throw std::invalid_argument("Unsupported type conversion for ARM conversion");
    }
}

void UnaryOperationLLVM::out_arm_str() const {
    std::string src_str = RegisterAllocator::accessVariable(this->src_sym);
    std::string dest_str = RegisterAllocator::accessVariable(this->dest_sym);

    switch (this->llvmType) {
        case llvm_neg:
            OutArm::outString("NEG " + dest_str + ", " + src_str);
            break;
        case llvm_fneg:
            OutArm::outString("FNEG " + dest_str + ", " + src_str);
            break;
        default:
            throw std::invalid_argument("Unsupported unary operation for ARM conversion");
    }
}


