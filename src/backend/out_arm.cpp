#include "../../include/backend/out_arm.hpp"
#include "../../include/backend/StaAlloca.hpp"
#include "../../include/llvm.hpp"
#include <variant>

// extern std:ofstream outputArmFile;
OutArm* OutArm::instance = nullptr; 
std::ofstream outputArmFile;

void OutArm::emitLargeNumber(const std::string& reg, uint64_t imm){
        bool first = true;
        std::string reg_new;
        if(reg.front()=='W'){
            reg_new = "X" + reg.substr(1);
        }else{
            reg_new = reg;
        }
        // 提取四个 16 位段
        uint16_t parts[4] = {
            static_cast<uint16_t>(imm & 0xFFFF),           // bits 0-15
            static_cast<uint16_t>((imm >> 16) & 0xFFFF),   // bits 16-31
            static_cast<uint16_t>((imm >> 32) & 0xFFFF),   // bits 32-47
            static_cast<uint16_t>((imm >> 48) & 0xFFFF)    // bits 48-63
        };
        int shifts[4] = {0, 16, 32, 48};
    
        for (int i = 3; i >= 0; i--) {
            if (parts[i] != 0 || (first && i == 0)) {
                std::string instr = first ? "MOVZ" : "MOVK";
                if (shifts[i] == 0) {
                    OutArm::outString("\t" + instr + " " + reg_new + ", #" + std::to_string(parts[i]));
                } else {
                    OutArm::outString("\t" + instr + " " + reg_new + ", #" + std::to_string(parts[i]) + ", LSL #" + std::to_string(shifts[i]));
                }
                first = false;
            }
        }
    
        // 如果全为 0
        if (first) {
            OutArm::outString("\tMOVZ " + reg + ", #0");
        }
    
}

void OutArm::emitLoadFloat(const std::string& reg, float value) {
    // 判断是 S 寄存器（32位）还是 D 寄存器（64位）
    if (reg[0] == 'S' || reg[0] == 's') {
        // S0, S1, ... 表示 float (32-bit)
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "\tLDR %s, =%.7gf", reg.c_str(), value);
        OutArm::outString(std::string(buffer));
    }
    else if (reg[0] == 'D' || reg[0] == 'd') {
        // D0, D1, ... 表示 double (64-bit)
        // 注意：我们传入的是 float，要转成 double
        double dval = static_cast<double>(value);
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "\tLDR %s, =%.15g", reg.c_str(), dval);
        OutArm::outString(std::string(buffer));
    }
    else {
        // 错误：不是浮点寄存器
        // 可以抛出错误或断言
        OutArm::outString("\t// ERROR: invalid float register: " + reg);
    }
}

void OutArm::emitLoadFloatSymbol(const std::string& reg, Symbol* float_symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string tmp_str = float_symbol->getName();
    if(!out_Arm.globalAllocator.rodata.count(float_symbol->getName())){
        std::vector<Data*> float_value;
        float_value.push_back(float_symbol->data);
        
        if(tmp_str == ""){
            tmp_str = generate_tmp_var_name();
        }
        out_Arm.globalAllocator.rodata[tmp_str] = float_value;
    }

    if (out_Arm.globalAllocator.rodata.count(tmp_str)){
        OutArm::outString("\tADRP X8, " + tmp_str.substr(1));
        OutArm::outString("\tADD X8, X8, :lo12:"+ tmp_str.substr(1));
        OutArm::outString("\tLDR " + reg + ", [X8]");
    }
    else {
        // 错误：不是浮点寄存器
        // 可以抛出错误或断言
        OutArm::outString("\t// ERROR: invalid float register: " + reg);
    }
}

// 暂时不用了 因为我们统一用X寄存器 D寄存器
int OutArm::getDataSize(Symbol* symbol){
    int size ;
    if(auto * arraySymbol = dynamic_cast<ArraySymbol*>(symbol)) {
        size =  arraySymbol->getArrayType();
    } else if(auto * pointerSymbol = dynamic_cast<PointerSymbol*>(symbol)) {
        size = pointerSymbol->getPointedType();
    } else {
        size = symbol->getDataType();
    }
    switch(size) {
        case dataType::i1: return 1;
        case dataType::i8: return 1;
        case dataType::i16: return 2;
        case dataType::i32: return 4;
        case dataType::i64: return 8;
        case dataType::f32: return 4;
        case dataType::f64: return 8;
        case dataType::dataType_pointer: return 16; // 假设指针大小为8字节
        default: throw std::invalid_argument("Unsupported data type for size calculation");
    }
}

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
        case logical_or: return "ORR";
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

//常数 时候 未考虑 浮点数溢出！
std::string OutArm::DispatchReg(Symbol* symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string reg_name;
    //全局变量情况
    if(out_Arm.globalAllocator.find_symbol(symbol->getName())){
        if(out_Arm.globalAllocator.rodata.count(symbol->getName())){
            if((out_Arm.globalAllocator.rodata[symbol->getName()].front()->getType()) == dataType::i32){
                reg_name = "#" + my_to_string(out_Arm.globalAllocator.rodata[symbol->getName()].front());
            }else{
                reg_name = "=" + my_to_string(out_Arm.globalAllocator.rodata[symbol->getName()].front());
            }
                
        }else{
            reg_name = symbol->getName() ;
            reg_name = reg_name.substr(1);
        }
        // }
    }//计算数组offset情况 好像都被我手动分配了X8 在外面
    else if(out_Arm.stackAllocator.Tmp_StackAddress_InReg.count(symbol->getName())){
            reg_name = "X8" ;
    }//常数情况
    else if(symbol->getType() == symType::constant_nonvar){
            if(symbol->getDataType() == dataType::i32){
                if(std::stoi(getSymOut(symbol)) < 4096 && std::stoi(getSymOut(symbol)) > -4096){
                    reg_name = "#" + getSymOut(symbol);
                }else{
                    VarSymbol* tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i32);
                    reg_name = out_Arm.DispatchReg(tmp_sym);
                    out_Arm.emitLargeNumber(reg_name,std::stoi(getSymOut(symbol)));
                }
        }else if(symbol->getDataType() == dataType::i1){
            if(std::stoi(getSymOut(symbol)) < 4096 && std::stoi(getSymOut(symbol)) > -4096){
                reg_name = "#" + getSymOut(symbol);
            }else{
                VarSymbol* tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i32);
                reg_name = out_Arm.DispatchReg(tmp_sym);
                out_Arm.emitLargeNumber(reg_name,std::stoi(getSymOut(symbol)));
            }
        }
        else if(symbol->getDataType() == dataType::f32){
            reg_name = "=" + getSymOut(symbol);
        }
    }//数组情况
    else if(auto* array_Symbol = dynamic_cast<ArraySymbol*>(symbol)) {       

        reg_name = out_Arm.xRegAllocator.accessAddress(array_Symbol->getName());

    }else if(auto* pointer_symbol = dynamic_cast<PointerSymbol*>(symbol)){

        reg_name = out_Arm.xRegAllocator.accessAddress(pointer_symbol->getName());
   // }
    }
    else{
        if(symbol->data->getType() == (dataType::f32) || symbol->data->getType() == (dataType::f64)) {
            reg_name = out_Arm.dRegAllocator.accessVariable(symbol->getName());
        }else if(symbol->data->getType() == (dataType::i32) || symbol->data->getType() == (dataType::i16) || symbol->data->getType() == (dataType::i8) || symbol->data->getType() == (dataType::i1)) {
            reg_name = out_Arm.xRegAllocator.accessVariable(symbol->getName());
        }else if(symbol->data->getType() == (dataType::i64) || symbol->data->getType() == (dataType::array_data)){
            reg_name = out_Arm.xRegAllocator.accessAddress(symbol->getName());
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
        reg_name = out_Arm.dRegAllocator.accessParam(symbol->getName());
    }else if(symbol->getDataType() == (dataType::i32) || symbol->getDataType() == (dataType::i64) || symbol->getDataType() == (dataType::i16) || symbol->getDataType() == (dataType::i8) || symbol->getDataType() == (dataType::i1)|| symbol->getDataType() == (dataType::array_data)) {
        reg_name = out_Arm.xRegAllocator.accessParam(symbol->getName());
    }
    return reg_name; 
}

std::string OutArm::DispatchRegParam(ArraySymbol* symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string reg_name;
       reg_name = out_Arm.xRegAllocator.accessParam(symbol->getName());

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
        case fcmp_oeq:
        case fcmp_oge:
        case fcmp_ogt:
        case fcmp_olt:
        case fcmp_ole:
        case fcmp_one:
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

    if(b_str.front()== '#'){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(b_str.substr(1));
        OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
        b_str = tmp_tmp_str;
    }

    if(b_str.front()== '='){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(b_str.substr(1));
        OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
        b_str = tmp_tmp_str ;
    }

    if(c_str.front()== '#'){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(c_str.substr(1));
        OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
        c_str = tmp_tmp_str;
    }

    if(c_str.front()== '='){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(c_str.substr(1));
        OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
        c_str = tmp_tmp_str;
    }

    switch(REMllvm->llvmType){
        case llvm_frem:
        if(b_str.front()== 'W'){
            VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
            std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
            out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + b_str);
            b_str = tmp_tmp_str;
        }
            if(c_str.front()== 'W'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + c_str);
                c_str = tmp_tmp_str;
            }
        break;
    }

    return op1 + " " + tmp_str + ", " + b_str + ", " + c_str + "\n\t" +
           op2 + " " + tmp_str + ", " + tmp_str + ", " + c_str + "\n\t" +
           op3 + " " + a_str + ", " + a_str + ", " + tmp_str;
    
}

std::string OutArm::ASMDOperation(ArithmeticOperationLLVM* ASMDllvm){
    OutArm& out_Arm = OutArm::getInstance();
    std::string a_str, b_str, c_str, op;

    op = ArithmeticOpConvert(ASMDllvm->llvmType);
    
    a_str = out_Arm.DispatchReg(ASMDllvm->a);
    b_str = out_Arm.DispatchReg(ASMDllvm->b);
    c_str = out_Arm.DispatchReg(ASMDllvm->c);
    
        if(b_str.front()== '#'){
            VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
            std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
            int tmp_num = std::stoi(b_str.substr(1));
            OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
            b_str = tmp_tmp_str;
        }

        if(c_str.front()== '#'){
            VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
            std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
            int tmp_num = std::stoi(c_str.substr(1));
            OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
            c_str = tmp_tmp_str;
        }

        if(b_str.front()== '='){
            VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
            std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
            int tmp_num = std::stoi(b_str.substr(1));
            OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
            b_str = tmp_tmp_str;
        }
    
        if(c_str.front()== '='){
            VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
            std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
            int tmp_num = std::stoi(c_str.substr(1));
            OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
            c_str = tmp_tmp_str;
        }
    switch (ASMDllvm->llvmType)
    {
        case llvm_fadd:
        case llvm_fsub:
        case llvm_fmul:
        case llvm_fdiv:
            if(b_str.front()== 'W'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + b_str);
                b_str = tmp_tmp_str;
            }
            if(c_str.front()== 'W'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + c_str);
                c_str = tmp_tmp_str;
            }
        break;
    
    default:
        break;
    }
    return op + " " + a_str + ", " + b_str + ", " + c_str;
}

std::string OutArm::ComparisonOperation(ArithmeticOperationLLVM* cmpllvm) {
    OutArm& out_Arm = OutArm::getInstance();
    std::string a_str, b_str, c_str, op0, op1, op2;

    op1 = "CSET";

    switch(cmpllvm->llvmType) {
        case icmp_eq:
            op0 = "CMP";
            op2 = "EQ";
            break;
        case icmp_ne:
            op0 = "CMP";
            op2 = "NE";
            break;
        case icmp_sgt:
            op0 = "CMP";
            op2 = "GT";
            break;
        case icmp_sge:
            op0 = "CMP";
            op2 = "GE";
            break;
        case icmp_slt:
            op0 = "CMP";
            op2 = "LT";
            break;
        case icmp_sle:
            op0 = "CMP";
            op2 = "LE";
            break;
            case fcmp_oeq:
            op0 = "FCMP";
            op2 = "EQ";
            break;
        case fcmp_ogt:
            op0 = "FCMP";
            op2 = "GT";
            break;
        case fcmp_oge:
            op0 = "FCMP";
            op2 = "GE";
            break;
        case fcmp_olt:
            op0 = "FCMP";
            op2 = "LT";
            break;
        case fcmp_ole:
            op0 = "FCMP";
            op2 = "LE";
            break;
        case fcmp_one:
            op0 = "FCMP";
            op2 = "NE";
            break;
        default:
            throw std::invalid_argument("Unsupported comparison type for ARM conversion");
    }

    a_str = out_Arm.DispatchReg(cmpllvm->a);
    b_str = out_Arm.DispatchReg(cmpllvm->b);
    c_str = out_Arm.DispatchReg(cmpllvm->c);

    if(b_str.front()== '#'){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(b_str.substr(1));
        OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
        b_str = tmp_tmp_str;
    }

    if(c_str.front()== '#'){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(c_str.substr(1));
        OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
        c_str = tmp_tmp_str;
    }
    
    if(b_str.front()== '='){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(b_str.substr(1));
        OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
        b_str = tmp_tmp_str;
    }

    if(c_str.front()== '='){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(c_str.substr(1));
        OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
        c_str = tmp_tmp_str;
    }

    switch(cmpllvm->llvmType){
        case fcmp_oeq:
        case fcmp_oge:
        case fcmp_ogt:
        case fcmp_ole:
        case fcmp_olt:
        case fcmp_one:
            if(b_str.front()== 'W'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + b_str);
                b_str = tmp_tmp_str;
            }

            if(c_str.front()== 'W'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + c_str);
                c_str = tmp_tmp_str;
            }
        break;
    }

    return op0 + " " + b_str + ", " + c_str + "\n\t" +
           op1 + " " + a_str + ", " + op2 ;
           
}

void UnconditionalBranchLLVM::out_arm_str() {
    std::string target_str = this->target->getName();
    if (!target_str.empty()) {
        target_str = target_str.substr(1);  // 从第1个字符开始，取到末尾
    }
    OutArm::outString("\tB " + target_str);
}

void ConditionalBranchLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string condition_str = out_Arm.DispatchReg(this->condition);
    std::string true_branch_str = this->trueBranch->getName();
    if (!true_branch_str.empty()) {
        true_branch_str = true_branch_str.substr(1);  // 从第1个字符开始，取到末尾
    }
    std::string false_branch_str = this->falseBranch->getName();
    if (!false_branch_str.empty()) {
        false_branch_str = false_branch_str.substr(1);  // 从第1个字符开始，取到末尾
    }
    OutArm::outString("\tCBZ " + condition_str + ", " + true_branch_str);
    OutArm::outString("\tCBNZ " + condition_str + ", " + false_branch_str);
}

void ReturnLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
        if (this->returnValue) {
            std::string return_value_str = out_Arm.DispatchReg(this->returnValue);
            if(out_Arm.globalAllocator.rodata.count(this->returnValue->getName())){
                if(auto* i32_data = dynamic_cast<Data_i32*>(out_Arm.globalAllocator.rodata[this->returnValue->getName()].front())){
                    return_value_str = "#" + my_to_string(i32_data);
                }else if(auto* f32_data = dynamic_cast<Data_f32*>(out_Arm.globalAllocator.rodata[this->returnValue->getName()].front())){
                    return_value_str = "=" + my_to_string(i32_data);
                }
            }
            if(this->getReturnType() == dataType::f32 || this->getReturnType() == dataType::f64){
                if(return_value_str == ""){
                    std::string name = generate_tmp_var_name();
                    VarSymbol* tmp_float_sym = SymbolFactory::createVarSymbol(name,returnValue->data);
                    std::string tmp_float_str = out_Arm.DispatchReg(tmp_float_sym);
                    out_Arm.emitLoadFloatSymbol(tmp_float_str,tmp_float_sym);
                    OutArm::outString("\tFMOV S0, " + tmp_float_str);
                }else if(return_value_str.front() == '='){
                    out_Arm.emitLoadFloatSymbol("S0",returnValue);
                }else{
                    OutArm::outString("\tFMOV S0, " + return_value_str);
                }
            }
            else{
                OutArm::outString("\tMOV W0, " + return_value_str);
            }
        }
        if(out_Arm.exit){
            OutArm::outString("\tMOV X8, #93\n\tSVC #0");
        }else{
            OutArm::outString(out_Arm.stackAllocator.emitEpilogue(out_Arm.stackAllocator.calculateStackSize()));
            OutArm::outString("\tRET");
        }
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
    std::string ori_str;//目的地 （源参数说是）
    std::vector<std::string> ori_strs = out_Arm.func_Params_Regs[func_name];
    int i = 0;
    for (const auto& arg : this->arguments) {
        ori_str = ori_strs[i];
        if (auto* array_symbol = dynamic_cast<ArraySymbol*>(arg)) {
                if(out_Arm.globalAllocator.find_symbol(array_symbol->getName())){
                    VarSymbol* tmp_sym =SymbolFactory::createTmpVarSymbol (dataType::i32);
                    std::string tmp_str = out_Arm.DispatchReg(tmp_sym);
                    //全局变量 而不是临时变量
                if(!out_Arm.globalAllocator.symbol_to_global.count(array_symbol->getName())){
                    
                    OutArm::outString("\tADRP " + tmp_str + ", " + array_symbol->getName().substr(1));
                    OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", :lo12:" + array_symbol->getName().substr(1));
                }else{//临时变量
                    std::string tmp_src_str = out_Arm.globalAllocator.symbol_to_global[array_symbol->getName()].first;
                    //out_Arm.stackAllocator.Tmp_StackAddress_InReg[tmp_src_str] = tmp_str;
                    tmp_src_str = tmp_src_str.substr(1);
                    OutArm::outString("\tADRP " + tmp_str + ", " + tmp_src_str);
                    OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", :lo12:" + tmp_src_str);
                }
                //有偏移情况
                if(out_Arm.globalAllocator.symbol_to_global.count(array_symbol->getName())){
                    int offset = out_Arm.globalAllocator.symbol_to_global[array_symbol->getName()].second ;
                    if(offset > 4095){
                        VarSymbol* tmp_tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i32);
                        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp_tmp_sym);
                        OutArm::emitLargeNumber(tmp_tmp_str,offset);
                        OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", " + tmp_tmp_str);
                    }else if( offset == 0){

                    }else{
                        OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", " + std::to_string(offset));
                    }
                }
                    arg_str = tmp_str;
            }else{
                arg_str = out_Arm.DispatchReg(array_symbol);
            }

            if(ori_str.front() == 'D'){
                OutArm::outString("\tFMOV " + ori_str + ", " + arg_str);
            }else{
                OutArm::outString("\tMOV " + ori_str + ", " + arg_str);
            }
        }
        else if (auto* var_symbol = dynamic_cast<VarSymbol*>(arg)) {
            arg_str = out_Arm.DispatchReg(var_symbol);
            if(ori_str.front() == 'D'){
                OutArm::outString("\tFMOV " + ori_str + ", " + arg_str);
            }else if(arg_str.front() == 'D' && ori_str.front() == 'X'){
                OutArm::outString("\tFMOV " + ori_str + ", " + arg_str);
            }else{
                OutArm::outString("\tMOV " + ori_str + ", " + arg_str);
            }
        }else if (auto* const_symbol = dynamic_cast<ConstSymbol*>(arg)){
            if(const_symbol->getDataType()==dataType::i32 || const_symbol->getDataType()==dataType::i1){
                int val = std::get<int>(const_symbol->data->getValue());
                OutArm::emitLargeNumber(ori_str,val);
            }else{
                if(const_symbol->getName() == ""){
                    std::string name = generate_tmp_var_name();
                    VarSymbol* tmp_float_sym = SymbolFactory::createVarSymbol(name,const_symbol->data);
                    std::string tmp_float_str = out_Arm.DispatchReg(tmp_float_sym);
                    out_Arm.emitLoadFloatSymbol(tmp_float_str,tmp_float_sym);
                }else{
                    out_Arm.emitLoadFloatSymbol(ori_str,const_symbol);
                }
            }
        }else if (auto* const_var_symbol = dynamic_cast<ConstVarSymbol*>(arg)){
            arg_str = out_Arm.DispatchReg(const_var_symbol);
            if(const_var_symbol->getDataType()==dataType::i32 || const_var_symbol->getDataType()==dataType::i1){
                int val ;
                //全局变量时候
                if(out_Arm.globalAllocator.find_symbol(const_var_symbol->getName())){
                    Data* tmp_data = out_Arm.globalAllocator.rodata[const_var_symbol->getName()].front();
                    val = std::get<int>(tmp_data->getValue());
                }else{
                    val = std::get<int>(const_var_symbol->data->getValue());
                }
                OutArm::emitLargeNumber(ori_str,val);
            }else{
                 if(arg_str.front() == '=' || arg_str.front() == '#'){
                    out_Arm.emitLoadFloatSymbol(ori_str,const_var_symbol);
                }
                else{
                    OutArm::outString("\tFMOV " + ori_str + ", " + arg_str);
                }
                
            }
        }
        ++i;
    }  
    
    std::string call_str = "BL " + func_name;
    OutArm::outString("\t"+call_str);
    if (this->dest_sym) {
        if(this->function->getReturnType() == dataType::f32 || this->function->getReturnType() == dataType::f64) {
            OutArm::outString("\tFMOV " + dest_str + ", D0"); // Assuming S0 is the return register for floating point
        } else {
            OutArm::outString("\tMOV " + dest_str + ", X0"); // Assuming X0 is the return register for integers
        }
    }


}

void Label::out_arm_str()  {
    std::string label_name = this->label->getName();
    if (!label_name.empty()) {
        label_name = label_name.substr(1);  // 从第1个字符开始，取到末尾
    }
    OutArm::outString(label_name + ":");
}

void PhiLLVM::out_arm_str()  {
    return  ;
    //phi语句没有直接翻译捏。。。
}

//全局变量将会统一在文件顶部输出

void GlobalNonArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateGlobalNonArray(this);
}

void ConstantNonArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateConstantNonArray(this);
}

void GlobalArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateGlobalArray(this);
}

void ConstantArrayVarDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.globalAllocator.allocateConstantArray(this);
}

//函数声明暂时不翻译？
void FuncDeclaration::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string func_name = this->func->getName();
    out_Arm.globalAllocator.allocateFunc(func_name);
    // 函数声明不需要输出 ARM 汇编代码
}

//没有写出函数的emit
void FuncDefination::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.resetReg();

    // 函数定义需要输出 ARM 汇编代码
    std::string func_name = this->func->getName();
    
    if(!func_name.empty()) {
        func_name = func_name.substr(1);  // 从第1个字符开始，取到末尾
    }
    if(func_name == "main"){
        //func_name = "_start";
        //out_Arm.exit = true;
    }
    out_Arm.globalAllocator.allocateFunc(func_name);
    OutArm::outString(func_name + ":");
    
    int stack_size = out_Arm.stackAllocator.calculateStackSize();
    OutArm::outString(out_Arm.stackAllocator.emitPrologue(stack_size));

    std::string param_str;
    std::vector<std::string> param_strs;
    // 输出函数参数
        
    for (const auto& param : this->params) {
        out_Arm.params.insert(param->getName());
        if (auto* array_symbol = dynamic_cast<ArraySymbol*>(param)) {
            param_str = out_Arm.DispatchRegParam(array_symbol);
        }
        else if (auto* var_symbol = dynamic_cast<VarSymbol*>(param)) {
            param_str = out_Arm.DispatchRegParam(var_symbol);
        }
            param_strs.push_back(param_str);
    }
    
    out_Arm.func_Params_Regs[func_name] = param_strs;
}

void AllocaNonArrayLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    //int datasize = OutArm::getDataSize(this->sym); 暂时不用了 我们统一用x寄存器 所以偏移量为16.
    int size = out_Arm.stackAllocator.allocateLocal( 4 ,this->sym->getName());
    
}

void AllocaArrayLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    //好吧 数组还是需要的哈  额额 实际不需要
    //int datasize = OutArm::getDataSize(this->array);
    int size = out_Arm.stackAllocator.allocateArray( 4 ,this->getDimensions(),this->array->getName());
}

void LoadLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.stackAllocator.RegVar_StackVar[dest_sym->getName()] = src_sym->getName();

    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);

    //加载普通变量 数组首位 已计算过【1】【2】地址的数组  ---- ----  全局变量 [i][j] 地址的数组
    if(!out_Arm.globalAllocator.find_symbol(src_sym->getName()) && !out_Arm.stackAllocator.Tmp_StackAddress_InReg.count(src_sym->getName())){
        int offset = out_Arm.stackAllocator.getOffset(this->src_sym->getName());

        out_Arm.SPmove(false, dest_str, offset);

    }else{
        std::string src_str = out_Arm.DispatchReg(this->src_sym);
        if(out_Arm.globalAllocator.find_symbol(src_sym->getName())) {
            VarSymbol* tmp_address_sym = SymbolFactory::createTmpVarSymbol(dataType::i64);
            std::string tmp_address_str = out_Arm.DispatchReg(tmp_address_sym);
            //全局变量 非数组情况
            if(!out_Arm.globalAllocator.symbol_to_global.count(src_sym->getName())){ 
                // out_Arm.stackAllocator.Tmp_StackAddress_InReg[src_sym->getName()] = dest_str;
                OutArm::outString("\tADRP " + tmp_address_str + ", " + src_str);
                OutArm::outString("\tADD " + tmp_address_str + ", " + tmp_address_str + ", :lo12:" + src_str);
            }else{
                //变量 映射了全局数组情况
                std::string tmp_src_str = out_Arm.globalAllocator.symbol_to_global[src_sym->getName()].first;
                // out_Arm.stackAllocator.Tmp_StackAddress_InReg[src_sym->getName()] = dest_str;
                tmp_src_str = tmp_src_str.substr(1);
                OutArm::outString("\tADRP " + tmp_address_str + ", " + tmp_src_str);
                OutArm::outString("\tADD " + tmp_address_str + ", " + tmp_address_str + ", :lo12:" + tmp_src_str);
            }
            //有偏移情况
            if(out_Arm.globalAllocator.symbol_to_global.count(src_sym->getName())){
                int offset = out_Arm.globalAllocator.symbol_to_global[src_sym->getName()].second ;
                if(offset > 4095){
                    VarSymbol* tmp_tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i64);
                    std::string tmp_tmp_str = out_Arm.DispatchReg(tmp_tmp_sym);
                    OutArm::emitLargeNumber(tmp_tmp_str,offset);
                    OutArm::outString("\tADD " + tmp_address_str + ", " + tmp_address_str + ", " + tmp_tmp_str);
                }else{
                    OutArm::outString("\tADD " + tmp_address_str + ", " + tmp_address_str + ", " + std::to_string(offset));
                }
            }
            OutArm::outString("\tLDR " + dest_str + ", " + "[" + tmp_address_str + "]");
        }else
        //临时变量情况(Tmp_StackAddress_InReg)
        {   src_str = "X8";
            OutArm::outString("\tLDR " + dest_str + ", " + "[" + src_str + "]");
        }
    }
    
}


void StoreLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.stackAllocator.RegVar_StackVar[src_sym->getName()] = dest_sym->getName();
    
    std::string src_str = out_Arm.DispatchReg(this->src_sym);


    //store语句 特殊处理src为常数情况
    if(src_str.front() == '#' && this->src_sym->getDataType()==dataType::i32){
        std::string tmp_num_str = src_str;
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        src_str = out_Arm.DispatchReg(tmp);
        if(std::stoi(src_str.substr(1)) > 4095){
            out_Arm.emitLargeNumber(src_str,std::stoi(src_str.substr(1)));
        }else{
            OutArm::outString("\tMOV " + src_str + ", " + tmp_num_str);
        }
    }else if(src_str.front() == '=' && this->src_sym->getDataType()==dataType::f32){
        std::string tmp_num_str = src_str;
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        src_str = out_Arm.DispatchReg(tmp);
        OutArm::outString("\tMOV " + src_str + ", " + tmp_num_str);
    }

    //普通变量 ———— 非全局变量 或 非数组情况
    if(!out_Arm.globalAllocator.find_symbol(dest_sym->getName()) && !out_Arm.stackAllocator.Tmp_StackAddress_InReg.count(dest_sym->getName())){
        int offset = out_Arm.stackAllocator.getOffset(this->dest_sym->getName());

        out_Arm.SPmove(true, src_str, offset);
        
    }
    //全局变量 数组时候
    else{
        std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
        if(out_Arm.globalAllocator.find_symbol(dest_sym->getName())){
                VarSymbol* tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i64);
                std::string tmp_str = out_Arm.DispatchReg(tmp_sym);
             //全局变量 而不是临时变量
             if(!out_Arm.globalAllocator.symbol_to_global.count(dest_sym->getName())){
                OutArm::outString("\tADRP " + tmp_str + ", " + dest_str);
                OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", :lo12:" + dest_str);
                OutArm::outString("\tSTR " + src_str + ", " + "[" + tmp_str + "]");
            }else{//临时变量
                std::string tmp_dest_str = out_Arm.globalAllocator.symbol_to_global[dest_sym->getName()].first;
                tmp_dest_str = tmp_dest_str.substr(1);
                OutArm::outString("\tADRP " + tmp_str + ", " + tmp_dest_str);
                OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", :lo12:" + tmp_dest_str);
                OutArm::outString("\tSTR " + src_str + ", " + "[" + tmp_str + "]");
            }//有偏移情况
            if(out_Arm.globalAllocator.symbol_to_global.count(dest_sym->getName())){
                int offset = out_Arm.globalAllocator.symbol_to_global[dest_sym->getName()].second ;
                out_Arm.SPmove(true, tmp_str, offset);
                // if(offset > 4095){
                //     VarSymbol* tmp_tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i64);
                //     std::string tmp_tmp_str = out_Arm.DispatchReg(tmp_tmp_sym);
                //     OutArm::emitLargeNumber(tmp_tmp_str,offset);
                //     OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", " + tmp_tmp_str);
                // }else{
                //     OutArm::outString("\tADD " + tmp_str + ", " + tmp_str + ", #" + std::to_string(offset));
                // }
            }
        }else{//临时变量情况(Tmp_StackAddress_InReg)
            dest_str = "X8";
            OutArm::outString("\tSTR " + src_str + ", " + "[" + dest_str + "]");
        }
    }
}

//此处未给[a][b]数组设置那个啥溢出去的地方 默认后面用不到
void GetElementPtrLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    const auto& container = this->getTyAndIdx();


    bool index_allnumber = true;//判断逻辑 是否为[1][1] 还是[a][b]
    for (const auto& [data_type, symbol_ptr] : this->getTyAndIdx()) {
        if (!symbol_ptr) {
            index_allnumber = false;
            break;
        }
        
        bool is_number_type = false;
        switch (symbol_ptr->getType()) {
            case symType::constant_nonvar:
                is_number_type = true;
                break;
            default:
                is_number_type = false;
                break;
        }
        
        if (!is_number_type) {
            index_allnumber = false;
            break;
        }
    }

    //全是数字数组的情况
    if(index_allnumber){
        
        // N维数组偏移量计算（通用方法）
        int offset = 0;
        int multiplier = 1;
        std::vector<int> dims = this->getDimensions();
        int i = this->getDimensions().size() - 1;
        
        for (auto it = container.rbegin(); it != container.rend(); ++it) {
            const auto& [data_type, symbol_ptr] = *it;
                if (i >= 0) {
                    offset += (std::stoi(getSymOut(symbol_ptr))) * multiplier;                   
                    // 更新乘数和索引
                    if (i > 0) {
                        multiplier *= dims[i];
                    }
                    i--;
                }
        }   
        offset *= 4; //这里！！！ 我觉得可能有bug哦。。。 

        // 全局变量的情况   str-str,int symbolTOglobal offset 全局变量的offset就是正偏移的
        if(out_Arm.globalAllocator.find_symbol(this->ptrval->getName())){
            out_Arm.globalAllocator.addSymbolToGlobal(this->dest_sym->getName(),this->ptrval->getName(),offset);
        }else{
            //正常变量的情况    localoffset str offset(绝对位置)
            out_Arm.stackAllocator.addArrayPtrwithOffset(this->dest_sym->getName(), this->ptrval->getName(), offset);
        }

    }else{//这里是[][]含有变量的情况
        
        //获取其所在地址
        //X8 专门作为getelem寄存器来用吧
        std::string arr_str = "X8";

        std::string arr_name = this->getSrcSymbol()->getName();
        std::string poi_name = this->getDestSymbol()->getName();

        std::string arr_offset_str;
        out_Arm.stackAllocator.Tmp_StackAddress_InReg.insert(poi_name);
        
        //先把数组的首地址正确传递
        //非全局变量 (全局变量只需要记录 offset) 参数数组也不用算首地址 都在他寄存器里
        if(!out_Arm.globalAllocator.find_symbol(arr_name) && !out_Arm.params.count(arr_name)) // "&&" out_Arm.stackAllocator.hasVariable(poi_name) 可能会加载别的值b = a[1]->a[2]，故省略
        {   

            int offset = out_Arm.stackAllocator.getOffset(this->getSrcSymbol()->getName());
            //out_Arm.SPmove
            arr_offset_str = std::to_string(offset);
            if(offset == 0){
                OutArm::outString("\tMOV " + arr_str + ", SP");
            }else{
                if(offset > 0 && offset <= 4095){
                    OutArm::outString("\tADD " + arr_str + ", SP, #" + arr_offset_str );
                }else if(offset > 4095){
                    VarSymbol* tmp = SymbolFactory::createTmpVarSymbol(dataType::i32);
                    std::string tmp_str = out_Arm.DispatchReg(tmp);
                    OutArm::emitLargeNumber(tmp_str,offset);
                    OutArm::outString("\tADD " + arr_str + ", SP, " + tmp_str );
                }else if(offset < 0 && offset >= -4095){
                    OutArm::outString("\tSUB " + arr_str + ", SP, #" + arr_offset_str );
                }else{
                    VarSymbol* tmp = SymbolFactory::createTmpVarSymbol(dataType::i32);
                    std::string tmp_str = out_Arm.DispatchReg(tmp);
                    OutArm::emitLargeNumber(tmp_str,-offset);
                    OutArm::outString("\tSUB " + arr_str + ", SP, " + tmp_str);
                }
            }
        }else{
            OutArm::outString("\tADRP " + arr_str+ ", " + arr_name.substr(1));
            OutArm::outString("\tADD " + arr_str + ", " + arr_str + ", :lo12:" + arr_name.substr(1));
        }

        // N维数组偏移量计算（通用方法）
        int offset = 0;//此为数字时候算的偏移量
        int multiplier = 1;
        std::vector<int> dims = this->getDimensions();
        int i = dims.size() - 1;
        
        for (auto it = container.rbegin(); it != container.rend(); ++it) {
            const auto& [data_type, symbol_ptr] = *it;
                if (i >= 0) {
                    //常数时候
                    if(it->second->getType() == symType::constant_nonvar){
                        
                        offset += (std::stoi(getSymOut(symbol_ptr))) * multiplier;
                    }//字母时候
                    else{
                        //给该字母找其寄存器捏 话说需要读取值不？ 好像还真需要？ 不对getelem前会 用phi 一次所以其实不需要。
                        std::string tmp_str = out_Arm.DispatchReg(symbol_ptr);
                        std::string tmp_num_str = std::to_string(multiplier * 4);
                        
                        //最后一维 不用乘？
                        if(multiplier == 1){
                            out_Arm.outString("\tMOV "+ tmp_str + ", #" + tmp_num_str);
                        }else{
                        //其他维度需要乘 比如对于a[10][20] 读取a[i][j]  第二维度时候直接加 第一维度加i*20
                            VarSymbol* tmp_tmp_sym = SymbolFactory::createTmpVarSymbol(dataType::i64);
                            std::string tmp_tmp_str = out_Arm.DispatchReg(tmp_tmp_sym);
                            if(multiplier * 4 > 4095){
                                out_Arm.emitLargeNumber(tmp_tmp_str,multiplier * 4);
                            }else{
                                out_Arm.outString("\tMOV " + tmp_tmp_str + ", #" + tmp_num_str);
                            }
                            out_Arm.outString("\tMUL " + tmp_str + ", " + tmp_str + ", " + tmp_tmp_str);
                        }

                            OutArm::outString("\tADD " + arr_str + ", " + arr_str + ", " + tmp_str);
                    } 

                    // 更新乘数和索引
                    if (i > 0) {
                        multiplier *= dims[i] ;
                    }
                    i--;
                }
        }

        if(offset!=0){
            std::string tmp_num_str = std::to_string(offset * 4);
            if(offset * 4 > 0 && offset * 4 <= 4095){
                OutArm::outString("\tADD " + arr_str + ", " + arr_str  + ", #" + tmp_num_str);
            }else if(offset * 4 > 4095){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbol(dataType::i64);
                std::string tmp_str = out_Arm.DispatchReg(tmp);
                OutArm::emitLargeNumber(tmp_str,offset);
                OutArm::outString("\tADD " + arr_str + ", " + arr_str  + ", " + tmp_str);
            }else if(offset * 4 < 0 && offset * 4 >= -4095){
                OutArm::outString("\tSUB " + arr_str + ", " + arr_str  + ", #" + tmp_num_str);
            }else{
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbol(dataType::i64);
                std::string tmp_str = out_Arm.DispatchReg(tmp);
                OutArm::emitLargeNumber(tmp_str,-offset);
                OutArm::outString("\tSUB " + arr_str + ", " + arr_str  + ", #" + tmp_num_str);
            }
        } 

    }
}


void TypeConversionOperation::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
    std::string src_str = out_Arm.DispatchReg(this->src_sym);

    if(dest_str.front()== '#'){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(dest_str.substr(1));
        OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
        dest_str = tmp_tmp_str;
    }

    if(src_str.front()== '#'){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(src_str.substr(1));
        OutArm::emitLargeNumber(tmp_tmp_str,tmp_num);
        src_str = tmp_tmp_str;
    }

    if(dest_str.front()== '='){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(dest_str.substr(1));
        OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
        dest_str = tmp_tmp_str;
    }

    if(src_str.front()== '='){
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
        int tmp_num = std::stoi(src_str.substr(1));
        OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
        src_str = tmp_tmp_str;
    }

    switch (this->llvmType) {
        case llvm_trunc:
            //OutArm::outString("\tTRUNC " + dest_str + ", " + src_str);
            break;
        case zext:
            //OutArm::outString("\tZEXT " + dest_str + ", " + src_str);
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
            if(src_str.front() == 'W'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                out_Arm.outString("\tSCVTF " + tmp_tmp_str + ", " + src_str);
                src_str = tmp_tmp_str;
            }
            OutArm::outString("\tFCVTZS " + dest_str + ", " + src_str);
            break;
        case uitofp:
            OutArm::outString("\tUITOFP " + dest_str + ", " + src_str);
            break;
        case sitofp:
            OutArm::outString("\tSCVTF " + dest_str + ", " + src_str);
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
            if(src_str.front()== '=' || src_str.front()== '#'){
                VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
                std::string tmp_tmp_str = out_Arm.DispatchReg(tmp);
                int tmp_num = std::stoi(src_str.substr(1));
                OutArm::emitLoadFloat(tmp_tmp_str,tmp_num);
                src_str = tmp_tmp_str;
            }
            OutArm::outString("\tFNEG " + dest_str + ", " + src_str);
            break;
        default:
            throw std::invalid_argument("Unsupported unary operation for ARM conversion");
    }
}

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

void XRegAllocator::promoteToRegister(std::string symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    bool is_in_stack = stackAllocator.hasVariable(symbol);
    if (is_in_stack) {
        int stack_offset = stackAllocator.getOffset(symbol);
        std::string reg_name = this->getRegister(symbol);
        if (reg_name.empty()) {
            throw std::runtime_error("No free registers available for promotion");
        }
        if(stack_offset >= -256 && stack_offset <= 255){
            OutArm::outString("\tLDR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
        }else{
            OutArm::emitLargeNumber(reg_name,stack_offset);
            OutArm::outString("\tLDR " + reg_name + ", [" + reg_name + "]");
        }   
        int position = this->var_to_reg[symbol]; 
        if(!Registers[position].empty()){
            this->spillToStack(Registers[position]); // 将原寄存器内容溢出到栈
        }
        Registers[position] = symbol;
    }else{
        throw std::runtime_error("Wrong load!");
    }   
}

void XRegAllocator::spillToStack(std::string symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    //临时的直接不管了 溢出的干活
    if(stackAllocator.isTmpVar(symbol) || stackAllocator.Tmp_StackAddress_InReg.count(symbol)){
        return ;
    }
    std::string reg_name = this->getRegister(symbol);
    int stack_offset;

    if(stackAllocator.RegVar_StackVar.count(symbol)){
        std::string symbol_stack = stackAllocator.RegVar_StackVar[symbol];
        stack_offset = stackAllocator.getOffset(symbol_stack);
    }else{
        stack_offset = stackAllocator.getOffset(symbol);
    }

    if (reg_name.empty()) {
        return;//默认不用存进栈帧
        //throw std::runtime_error("No register allocated for spilling");
    }

    if(stack_offset == 0){
        OutArm::outString("\tSTR " + reg_name + ", [SP]");
    }else{
        if(stack_offset <= 255 && stack_offset>=-255){
            OutArm::outString("\tSTR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]!");
            out_Arm.stackAllocator.stack_currentOffset -= stack_offset; 
        }else if(stack_offset < -255){
            if( stack_offset >= -4095 ){
                OutArm::outString("\tMOV X8, #" + std::to_string(-stack_offset));
            }else if( stack_offset <= -65535){
                OutArm::emitLargeNumber("X8",-stack_offset);
            }else{
                OutArm::outString("\tMOVZ X8, #" + std::to_string(-stack_offset));
            }
            OutArm::outString("\tSUB SP, SP, X8");
            OutArm::outString("\tSTR " + reg_name + ", [SP]");
            out_Arm.stackAllocator.stack_currentOffset -= stack_offset; 
        }else if(stack_offset > 255){
            if( stack_offset <=4095 ){
                OutArm::outString("\tMOV X8, #" + std::to_string(stack_offset));
            }else if( stack_offset >= 65535){
                OutArm::emitLargeNumber("X8",stack_offset);
            }else{
                OutArm::outString("\tMOVZ X8, #" + std::to_string(stack_offset));
            }
            OutArm::outString("\tADD SP, SP, X8");
            OutArm::outString("\tSTR " + reg_name + ", [SP]");
            out_Arm.stackAllocator.stack_currentOffset -= stack_offset; 
        }
    }
   
    // 清除寄存器映射
    //this->freeRegister(reg_name);
}


void DRegAllocator::promoteToRegister(std::string symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    bool is_in_stack = stackAllocator.hasVariable(symbol);
    if (is_in_stack) {
        int stack_offset = stackAllocator.getOffset(symbol);
        std::string reg_name = this->getRegister(symbol);
        if (reg_name.empty()) {
            throw std::runtime_error("No free registers available for promotion");
        }
        if(stack_offset >= -256 && stack_offset <= 255){
            OutArm::outString("\tLDR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
        }else{
            OutArm::emitLargeNumber(reg_name,stack_offset);
            OutArm::outString("\tLDR " + reg_name + ", [" + reg_name + "]");
        }       
        int position = this->var_to_reg[symbol]; 
        if(!Registers[position].empty()){
            this->spillToStack(Registers[position]); // 将原寄存器内容溢出到栈
        }
        Registers[position] = symbol;
    }else{
        throw std::runtime_error("Wrong load!");
    }   
}

void DRegAllocator::spillToStack(std::string symbol) {
    OutArm& out_Arm = OutArm::getInstance();
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    if(stackAllocator.isTmpVar(symbol) || stackAllocator.Tmp_StackAddress_InReg.count(symbol)){
        return ;
    }
    std::string reg_name = this->getRegister(symbol);

    int stack_offset;

    if(stackAllocator.RegVar_StackVar.count(symbol)){
        std::string symbol_stack = stackAllocator.RegVar_StackVar[symbol];
        stack_offset = stackAllocator.getOffset(symbol_stack);
    }else{
        stack_offset = stackAllocator.getOffset(symbol);
    }
    
    if (reg_name.empty()) {
        throw std::runtime_error("No register allocated for spilling");
    }

    if(stack_offset == 0){
        OutArm::outString("\tSTR " + reg_name + ", [SP]");
    }else{
        if(-255 <= stack_offset <= 255){
            OutArm::outString("\tSTR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]!");
            out_Arm.stackAllocator.stack_currentOffset -= stack_offset; 
        }else if(stack_offset < -255){
            if( -4095 <= stack_offset ){
                OutArm::outString("\tMOV X8, #" + std::to_string(-stack_offset));
            }else if( stack_offset <= -65535){
                OutArm::emitLargeNumber("X8",-stack_offset);
            }else{
                OutArm::outString("\tMOVZ X8, #" + std::to_string(-stack_offset));
            }
            OutArm::outString("\tSUB SP, SP, X8");
            OutArm::outString("\tSTR " + reg_name + ", [SP]");
            out_Arm.stackAllocator.stack_currentOffset -= stack_offset; 
        }else if(stack_offset > 255){
            if( stack_offset <=4095 ){
                OutArm::outString("\tMOV X8, #" + std::to_string(stack_offset));
            }else if( stack_offset >= 65535){
                OutArm::emitLargeNumber("X8",stack_offset);
            }else{
                OutArm::outString("\tMOVZ X8, #" + std::to_string(stack_offset));
            }
            OutArm::outString("\tADD SP, SP, X8");
            OutArm::outString("\tSTR " + reg_name + ", [SP]");
            out_Arm.stackAllocator.stack_currentOffset -= stack_offset; 
        }
    }
   
    // 清除寄存器映射
    //this->freeRegister(reg_name);
}

void OutArm::SPmove_NO_ls(const std::string& reg, int offsets){

}

void OutArm::SPmove( bool isStore, const std::string& reg, int offsets){
    OutArm& out_Arm = OutArm::getInstance();
    int offset = this->stackAllocator.align(offsets,16);
    std::string ls_str = isStore? "STR" : "LDR";
    int diff = offset - offsets;

    if(diff == 0 && offset >= -255 && offset <= 255){
        OutArm::outString("\t" + ls_str + " " + reg + ", [SP, #" + std::to_string(offset) + "]!");
        out_Arm.stackAllocator.stack_currentOffset -= offset; 
        return ;
    }

    VarSymbol* tmp_num_sym = SymbolFactory::createTmpVarSymbol(dataType::i64);
    std::string tmp_num_str = out_Arm.DispatchReg(tmp_num_sym);
    if(offset > 0){
        OutArm::emitLargeNumber(tmp_num_str,offset);

        OutArm::outString("\tADD SP, SP, " + tmp_num_str);
        OutArm::outString("\t "+ ls_str + " " + reg + ", [SP, #" + std::to_string(diff) + "]");
        out_Arm.stackAllocator.stack_currentOffset -= offset;
    }
    else if(offset < 0){
        OutArm::emitLargeNumber(tmp_num_str,-offset);

        OutArm::outString("\tSUB SP, SP, " + tmp_num_str);
        OutArm::outString("\t"+ ls_str + " " + reg + ", [SP, #" + std::to_string(diff) + "]");
        out_Arm.stackAllocator.stack_currentOffset -= offset;
    }
    else {
        OutArm::outString("\t"+ ls_str + " " + reg + ", [SP, #" + std::to_string(diff) + "]");
    }
    
}

void OutArm::resetReg(){
    OutArm& Out_Arm = OutArm::getInstance();
    Out_Arm.dRegAllocator.reset();
    Out_Arm.xRegAllocator.reset();
}

void out_arm(std::string outputFileName, ModuleList* module_list) {
    std::string name = outputFileName;
    
    // 创建OutArm实例
    OutArm& Out_Arm = OutArm::getInstance();
    Out_Arm.setName(name);

    bool flag = false;
    
    // 遍历模块列表
    for (Module* module = module_list->head; module != nullptr; module = module->next) {
        // 输出模块名称
        if(auto* func_module = dynamic_cast<FuncDefination*> (module->head)){
            flag = true;
            Out_Arm.params.clear();
        }

        if(flag)
        OutArm::outString("\n");
        
        // 遍历每个llvm语句
        for (LLVM* llvm = module->head; llvm != nullptr; llvm = llvm->next) {
            llvm->out_arm_str();
        }
        
        if(flag)
        OutArm::outString("\n");

        flag = false;
    }
    insertContentToFileFront(name, Out_Arm.globalAllocator.emitAssemblyToString());

}