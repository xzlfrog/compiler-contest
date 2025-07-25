#include "../../include/backend/out_arm.hpp"
#include "../../include/backend/StaAlloca.hpp"
#include "../../include/llvm.hpp"

// extern std:ofstream outputArmFile;
OutArm* OutArm::instance = nullptr; 
std::ofstream outputArmFile;

void OutArm::outString(const std::string &str) {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.out.open(out_Arm.outputFileName, std::ios::out | std::ios::app);
    if (!outputArmFile.is_open()) {
        std::cerr << "无法打开输出文件" << std::endl;
        throw std::runtime_error("无法打开输出文件");
    }
    outputArmFile << str << std::endl;
    outputArmFile.flush();
}

std::string OutArm::ArithmeticOpConvert(LLVMtype op) {
    switch (op) {
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

std::string OutArm::getIntNumberOfOperands(Symbol *constvarsym){
    ValueVariant number = constvarsym->data->getValue();
    if (std::holds_alternative<int>(number)) {
        if(std::get<int>(number) == 0) {
            return "XZR"; // ARM zero register
        }
        return "#" + std::to_string(std::get<int>(number));
    }else if(std::holds_alternative<float>(number)) {
        return std::to_string(std::get<float>(number));
    }
}

// std::string getIntNumberOfOperands(ConstSymbol *sym){
//     ValueVariant number = sym->data->getValue();
//     if (std::holds_alternative<int>(number)) {
//         if(std::get<int>(number) == 0) {
//             return "XZR"; // ARM zero register
//         }
//         return "#" + std::to_string(std::get<int>(number));
//     }else if(std::holds_alternative<float>(number)) {
//         return std::to_string(std::get<float>(number));
//     }
//     throw std::invalid_argument("Unsupported type for getIntNumberOfOperands");
// }


std::string OutArm::DispatchReg(Symbol* symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string reg_name;
    if(symbol->type == symType::constant_var || symbol->type == symType::constant_nonvar) {
        reg_name = OutArm::getIntNumberOfOperands(symbol);
    }else if(auto* array_Symbol = dynamic_cast<ArraySymbol*>(symbol)) {       
        if (array_Symbol->getArrayType() == dataType::f32 || 
        array_Symbol->getArrayType() == dataType::f64) {
        reg_name = out_Arm.dRegAllocator.accessVariable(array_Symbol);
    } else if (array_Symbol->getArrayType() == dataType::i32 || 
               array_Symbol->getArrayType() == dataType::i64 || 
               array_Symbol->getArrayType() == dataType::i16 || 
               array_Symbol->getArrayType() == dataType::i8 || 
               array_Symbol->getArrayType() == dataType::i1 || 
               array_Symbol->getArrayType() == dataType::array_data) {
        reg_name = out_Arm.xRegAllocator.accessVariable(array_Symbol);
    }
    }else if(auto* pointer_symbol = dynamic_cast<PointerSymbol*>(symbol)){
        if (pointer_symbol->getPointedType() == dataType::f32 || 
        pointer_symbol->getPointedType() == dataType::f64) {
        reg_name = out_Arm.dRegAllocator.accessVariable(pointer_symbol);
    } else if (pointer_symbol->getPointedType() == dataType::i32 || 
               pointer_symbol->getPointedType() == dataType::i64 || 
               pointer_symbol->getPointedType() == dataType::i16 || 
               pointer_symbol->getPointedType() == dataType::i8 || 
               pointer_symbol->getPointedType() == dataType::i1 || 
               pointer_symbol->getPointedType() == dataType::array_data) {
        reg_name = out_Arm.xRegAllocator.accessVariable(pointer_symbol);
    }
    }
    else{
        if(symbol->data->getType() == (dataType::f32) || symbol->data->getType() == (dataType::f64)) {
            reg_name = out_Arm.dRegAllocator.accessVariable(symbol);
        }else if(symbol->data->getType() == (dataType::i32) || symbol->data->getType() == (dataType::i64) || symbol->data->getType() == (dataType::i16) || symbol->data->getType() == (dataType::i8) || symbol->data->getType() == (dataType::i1)||symbol->data->getType() == (dataType::array_data)) {
            reg_name = out_Arm.xRegAllocator.accessVariable(symbol);
        }
    }
    return reg_name;
}

std::string OutArm::DispatchRegParam(VarSymbol* symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string reg_name;
    if(symbol->type == symType::constant_var || symbol->type == symType::constant_nonvar) {
        reg_name = OutArm::getIntNumberOfOperands(symbol);
    }else if(symbol->getDataType() == (dataType::f32) || symbol->getDataType() == (dataType::f64)) {
        reg_name = out_Arm.dRegAllocator.accessParam(symbol);
    }else if(symbol->getDataType() == (dataType::i32) || symbol->getDataType() == (dataType::i64) || symbol->getDataType() == (dataType::i16) || symbol->getDataType() == (dataType::i8) || symbol->getDataType() == (dataType::i1)|| symbol->getDataType() == (dataType::array_data)) {
        reg_name = out_Arm.xRegAllocator.accessParam(symbol);
    }
    return reg_name; 
}

std::string OutArm::DispatchRegParam(ArraySymbol* symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string reg_name;
    if(symbol->getArrayType() == (dataType::f32) || symbol->getArrayType() == (dataType::f64)) {
        reg_name = out_Arm.dRegAllocator.accessParam(symbol);
    }else if(symbol->getArrayType() == (dataType::i32) || symbol->getArrayType() == (dataType::i64) || symbol->getArrayType() == (dataType::i16) || symbol->getArrayType() == (dataType::i8) || symbol->getArrayType() == (dataType::i1)||symbol->getArrayType() == (dataType::array_data)) {
        reg_name = out_Arm.xRegAllocator.accessParam(symbol);
    }
    return reg_name; 
}

void ArithmeticOperationLLVM::out_arm_str(){

    switch(this->llvmType){
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
        case logical_xor:
            OutArm::outString("\t"+OutArm::ASMDOperation(this));
            break;
        case llvm_frem:
        case urem:
        case srem:
            OutArm::outString("\t"+OutArm::RemOperation(this));
            break;
        case icmp_eq:
        case icmp_ne:
        case icmp_sgt:
        case icmp_sge:
        case icmp_slt:
        case icmp_sle:
            OutArm::outString("\t"+OutArm::ComparisonOperation(this));
            break;

        default:
            throw std::invalid_argument("Unsupported LLVM type for ARM conversion");
    }
    
}

std::string OutArm::RemOperation(ArithmeticOperationLLVM* REMllvm){
    OutArm& out_Arm = OutArm::getInstance();
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
    a_str = out_Arm.DispatchReg(REMllvm->a);
    tmp_str = out_Arm.DispatchReg(tmp);
    b_str = out_Arm.DispatchReg(REMllvm->b);
    c_str = out_Arm.DispatchReg(REMllvm->c);

    return op1 + " " + tmp_str + ", " + b_str + ", " + c_str + "\n" +
           op2 + " " + tmp_str + ", " + tmp_str + ", " + c_str + "\n" +
           op3 + " " + a_str + ", " + a_str + ", " + tmp_str;
    
}

std::string OutArm::ASMDOperation(ArithmeticOperationLLVM* ASMDllvm){
    OutArm& out_Arm = OutArm::getInstance();
    std::string a_str, b_str, c_str, op;

    op = ArithmeticOpConvert(ASMDllvm->llvmType);
    
    a_str = out_Arm.DispatchReg(ASMDllvm->a);
    b_str = out_Arm.DispatchReg(ASMDllvm->b);
    c_str = out_Arm.DispatchReg(ASMDllvm->c);

    return op + " " + a_str + ", " + b_str + ", " + c_str;
}

std::string OutArm::ComparisonOperation(ArithmeticOperationLLVM* cmpllvm) {
    OutArm& out_Arm = OutArm::getInstance();
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

    a_str = out_Arm.DispatchReg(cmpllvm->a);
    tmp_str = out_Arm.DispatchReg(tmp);
    b_str = out_Arm.DispatchReg(cmpllvm->b);
    c_str = out_Arm.DispatchReg(cmpllvm->c);

    return op0 + " " + b_str + ", " + c_str + "\n" +
           op1 + " " + a_str + ", " + op2 ;
           
}

void UnconditionalBranchLLVM::out_arm_str() {
    std::string target_str = this->target->getName();
    OutArm::outString("\tB " + target_str);
}

void ConditionalBranchLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string condition_str = out_Arm.DispatchReg(this->condition);
    std::string true_branch_str = this->trueBranch->getName();
    std::string false_branch_str = this->falseBranch->getName();

    OutArm::outString("\tCBZ " + condition_str + ", " + true_branch_str);
    OutArm::outString("\tCBNZ " + condition_str + ", " + false_branch_str);
}

void ReturnLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    if (this->returnValue) {
        std::string return_value_str = out_Arm.DispatchReg(this->returnValue);
        OutArm::outString("\tMOV X0, " + return_value_str); // Assuming X0 is the return register
    }
    OutArm::outString(out_Arm.stackAllocator.emitEpilogue(out_Arm.stackAllocator.calculateStackSize()));
    OutArm::outString("\tRET");
}

void CallLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string func_name = this->function->getName();
    if (!func_name.empty()) {
        func_name = func_name.substr(1);  // 从第1个字符开始，取到末尾
    }
    std::string dest_str; 
    if(this->dest_sym) {
        dest_str= out_Arm.DispatchReg(this->dest_sym);
    }
    std::string arg_str;

    for (const auto& arg : this->arguments) {
        if (auto* array_symbol = dynamic_cast<ArraySymbol*>(arg)) {
            arg_str = out_Arm.DispatchRegParam(array_symbol);
        }
        else if (auto* var_symbol = dynamic_cast<VarSymbol*>(arg)) {
            arg_str = out_Arm.DispatchRegParam(var_symbol);
        }
        
        OutArm::outString("\tMOV " + arg_str + ", X" + std::to_string(&arg - &this->arguments[0] + 1)); // X1, X2, ...
    }

    std::string call_str = "BL " + func_name;
    OutArm::outString("\t"+call_str);
    if (this->dest_sym) {
        OutArm::outString("\tMOV " + dest_str + ", X0"); // Assuming X0 is the return register
    }


}

void Label::out_arm_str()  {
    std::string label_name = this->label->getName();
    OutArm::outString(label_name + ":");
}

void PhiLLVM::out_arm_str()  {
    return  ;
    //phi语句没有直接翻译捏。。。
}

//全局变量将会统一在文件顶部输出

void GlobalNonArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateGlobal(dest_sym);
}

void ConstantNonArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateGlobal(dest_sym);
}

void GlobalArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateArray(dest_sym);
}

void ConstantArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateArray(dest_sym);
}

//函数声明暂时不翻译？
void FuncDeclaration::out_arm_str()  {
    // 函数声明不需要输出 ARM 汇编代码
}

//没有写出函数的emit
void FuncDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    // 函数定义需要输出 ARM 汇编代码
    std::string func_name = this->func->getName();
    if(!func_name.empty()) {
        func_name = func_name.substr(1);  // 从第1个字符开始，取到末尾
    }
    OutArm::outString(func_name + " :");
    
    int stack_size = out_Arm.stackAllocator.calculateStackSize();
    OutArm::outString(out_Arm.stackAllocator.emitPrologue(stack_size));

    std::string param_str;
    // 输出函数参数
        
    for (const auto& param : this->params) {
        if (auto* array_symbol = dynamic_cast<ArraySymbol*>(param)) {
            param_str = out_Arm.DispatchRegParam(array_symbol);
        }
        else if (auto* var_symbol = dynamic_cast<VarSymbol*>(param)) {
            param_str = out_Arm.DispatchRegParam(var_symbol);
        }
    }
    // 输出函数体的 LLVM 指令
    //for (LLVM* llvm = this->block_tail; llvm != nullptr; llvm = llvm->next) {
    //
    //    llvm->out_arm_str();
}

void AllocaNonArrayLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    std::string var_str = out_Arm.DispatchReg(this->sym);
    int size = out_Arm.stackAllocator.allocateLocal(this->sym);
    OutArm::outString("\tSUB SP, SP, #" + std::to_string(size));
    OutArm::outString("\tMOV " + var_str + ", SP");
}

void AllocaArrayLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string array_str = out_Arm.DispatchReg(this->array);
    int size = out_Arm.stackAllocator.allocateArray(this->array);
    
    OutArm::outString("\tSUB SP, SP, #" + std::to_string(size));
    OutArm::outString("\tMOV " + array_str + ", SP");
}

void LoadLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    std::string src_str = out_Arm.DispatchReg(this->src_sym);
    int offset = out_Arm.stackAllocator.getOffset(this->dest_sym);
    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
   
    OutArm::outString("\tLDR " + src_str + ", [SP, #" + std::to_string(offset) + "]");
}

void StoreLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    std::string src_str = out_Arm.DispatchReg(this->src_sym);
    int offset = out_Arm.stackAllocator.getOffset(this->dest_sym);
    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
    
    OutArm::outString("\tSTR " + src_str + ", [SP, #" + std::to_string(offset) + "]");
}

//未对齐 可能有隐患
void GetElementPtrLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string base_ptr = out_Arm.DispatchReg(this->ptrval);

    int offset = out_Arm.stackAllocator.getOffset(this->ptrval);
    // for (auto dim : ty_idx) {
    //     if (dim.first == dataType::i32) {
    //         offset += dim.second->data->getValue() * out_Arm.stackAllocator.getTypeSize(dim.first);
    //     } else {
    //         throw std::invalid_argument("Unsupported dimension type for ARM conversion");
    //     }
    // }

    out_Arm.stackAllocator.addPtr(this->dest_sym, offset);
}

void TypeConversionOperation::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
    std::string src_str = out_Arm.DispatchReg(this->src_sym);

    switch (this->llvmType) {
        case llvm_trunc:
            OutArm::outString("\tTRUNC " + dest_str + ", " + src_str);
            break;
        case zext:
            OutArm::outString("\tZEXT " + dest_str + ", " + src_str);
            break;
        case sext:
            OutArm::outString("\tSEXT " + dest_str + ", " + src_str);
            break;
        case bitcast:
            OutArm::outString("\tBITCAST " + dest_str + ", " + src_str);
            break;
        case fptrunc:
            OutArm::outString("\tFPTRUNC " + dest_str + ", " + src_str);
            break;
        case fpext:
            OutArm::outString("\tFPEXT " + dest_str + ", " + src_str);
            break;
        case fptoui:
            OutArm::outString("\tFPTUOI " + dest_str + ", " + src_str);
            break;
        case fptosi:
            OutArm::outString("\tFPTOSI " + dest_str + ", " + src_str);
            break;
        case uitofp:
            OutArm::outString("\tUITOFP " + dest_str + ", " + src_str);
            break;
        case sitofp:
            OutArm::outString("\tSITOFP " + dest_str + ", " + src_str);
            break;
        case ptrtoint:
            OutArm::outString("\tPTRTOINT " + dest_str + ", " + src_str);
            break;
        case inttoptr:
            OutArm::outString("\tINTTOPTR " + dest_str + ", " + src_str);
            break;
        default:
            throw std::invalid_argument("Unsupported type conversion for ARM conversion");
    }
}

void UnaryOperationLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
    std::string src_str = out_Arm.DispatchReg(this->src_sym);

    switch (this->llvmType) {
        case llvm_neg:
            OutArm::outString("\tNEG " + dest_str + ", " + src_str);
            break;
        case llvm_fneg:
            OutArm::outString("\tFNEG " + dest_str + ", " + src_str);
            break;
        default:
            throw std::invalid_argument("Unsupported unary operation for ARM conversion");
    }
}

// void insertContentToFileFront(std::ofstream& outputFile, const std::string& contentToInsert) {
//     if (!outputFile.is_open()) {
//         std::cerr << "无法打开输出文件" << std::endl;
//         throw std::runtime_error("无法打开输出文件");
//     }

//     // 读取现有内容
//     std::string existingContent;
//     outputFile.seekp(0, std::ios::end);
//     size_t fileSize = outputFile.tellp();
//     if (fileSize > 0) {
//         outputFile.seekp(0, std::ios::beg);
//         existingContent.resize(fileSize);
//         //outputFile.read(&existingContent[0], fileSize);
//     }

//     // 将新内容插入到现有内容前面
//     outputFile.seekp(0, std::ios::beg);
//     outputFile << contentToInsert << existingContent;
//     outputFile.flush();
// }
void insertContentToFileFront(const std::string& filename, const std::string& contentToInsert) {
    std::ifstream read(filename, std::ios::binary);
    std::string oldContent;
    if (read.is_open()) {
        oldContent.assign((std::istreambuf_iterator<char>(read)),
                          std::istreambuf_iterator<char>());
        read.close();
    }

    std::ofstream write(filename, std::ios::binary);
    if (!write.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }
    write << contentToInsert << oldContent;
    write.close();
}

void XRegAllocator::promoteToRegister(Symbol* symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    bool is_in_stack = stackAllocator.hasVariable(symbol->getName());
    if (is_in_stack) {
        int stack_offset = stackAllocator.getOffset(symbol);
        std::string reg_name = this->getRegister(symbol);
        if (reg_name.empty()) {
            throw std::runtime_error("No free registers available for promotion");
        }
        OutArm::outString("\tLDR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
        int position = this->var_to_reg[symbol]; 
        if(Registers[position]!= nullptr){
            this->spillToStack(Registers[position]); // 将原寄存器内容溢出到栈
        }
        Registers[position] = symbol;
    }else{
        throw std::runtime_error("Wrong load!");
    }   
}

void XRegAllocator::spillToStack(Symbol* symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    int stack_offset;
    std::string reg_name = this->getRegister(symbol);
    if (reg_name.empty()) {
        throw std::runtime_error("No register allocated for spilling");
    }
    bool is_in_stack = stackAllocator.hasVariable(symbol->getName());
    if(is_in_stack) {
        stack_offset = stackAllocator.getOffset(symbol);
    }else{
        stack_offset = stackAllocator.allocateLocal(symbol);
    }
        OutArm::outString("\tSTR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
   
    // 清除寄存器映射
    this->freeRegister(reg_name);
}


void DRegAllocator::promoteToRegister(Symbol* symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    bool is_in_stack = stackAllocator.hasVariable(symbol->getName());
    if (is_in_stack) {
        int stack_offset = stackAllocator.getOffset(symbol);
        std::string reg_name = this->getRegister(symbol);
        if (reg_name.empty()) {
            throw std::runtime_error("No free registers available for promotion");
        }
        OutArm::outString("\tLDR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
        int position = this->var_to_reg[symbol]; 
        if(Registers[position]!= nullptr){
            this->spillToStack(Registers[position]); // 将原寄存器内容溢出到栈
        }
        Registers[position] = symbol;
    }else{
        throw std::runtime_error("Wrong load!");
    }   
}

void DRegAllocator::spillToStack(Symbol* symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    std::string reg_name = this->getRegister(symbol);
    int stack_offset;
    if (reg_name.empty()) {
        throw std::runtime_error("No register allocated for spilling");
    }
    bool is_in_stack = stackAllocator.hasVariable(symbol->getName());
    if(is_in_stack) {
        stack_offset = stackAllocator.getOffset(symbol);
    }else{
        stack_offset = stackAllocator.allocateLocal(symbol);
    }
        OutArm::outString("\tSTR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
   
    // 清除寄存器映射
    this->freeRegister(reg_name);
}

void out_arm(std::string outputFileName, ModuleList* module_list) {
    std::string name = outputFileName;
    
    // 创建OutArm实例
    OutArm& Out_Arm = OutArm::getInstance();
    Out_Arm.setName(name);
    
    // 遍历模块列表
    for (Module* module = module_list->head; module != nullptr; module = module->next) {
        // 输出模块名称
        OutArm::outString(";.module start");
        
        // 遍历每个llvm语句
        for (LLVM* llvm = module->head; llvm != nullptr; llvm = llvm->next) {
            llvm->out_arm_str();
        }
        
        insertContentToFileFront(name, Out_Arm.globalAllocator.emitAssemblyToString());

        OutArm::outString(";.endmodule");
    }
}