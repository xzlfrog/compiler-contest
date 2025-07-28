#include "../../include/backend/out_arm.hpp"
#include "../../include/backend/StaAlloca.hpp"
#include "../../include/llvm.hpp"
#include <variant>

// extern std:ofstream outputArmFile;
OutArm* OutArm::instance = nullptr; 
std::ofstream outputArmFile;

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
    //全局变量情况
    if(out_Arm.globalAllocator.find_symbol(symbol->getName())){
        if(!out_Arm.globalAllocator.symbol_to_global.count(symbol->getName())){
            reg_name = "[" + symbol->getName() +"]";
        }else{
            std::string reg_name1 = out_Arm.globalAllocator.symbol_to_global[symbol->getName()].first ;
            int offset = out_Arm.globalAllocator.symbol_to_global[symbol->getName()].second ;
            if(!offset){
                reg_name = "[" + reg_name1 +"]";
            }else{
                reg_name = "[" + reg_name1 + ", #" + std::to_string(offset) + "]";
            }
        }
    }//计算数组offset情况
    else if(out_Arm.stackAllocator.Tmp_StackAddress_InReg.count(symbol->getName())){
            reg_name = out_Arm.stackAllocator.Tmp_StackAddress_InReg[symbol->getName()];
    }//常数情况
    else if(symbol->getType() == symType::constant_nonvar || symbol->getType() == symType::constant_var){
            reg_name = "#" + getSymOut(symbol);
    }//数组情况
    else if(auto* array_Symbol = dynamic_cast<ArraySymbol*>(symbol)) {       
        if (array_Symbol->getArrayType() == dataType::f32 || 
        array_Symbol->getArrayType() == dataType::f64) {
        reg_name = out_Arm.dRegAllocator.accessVariable(array_Symbol->getName());
    } else if (array_Symbol->getArrayType() == dataType::i32 || 
               array_Symbol->getArrayType() == dataType::i64 || 
               array_Symbol->getArrayType() == dataType::i16 || 
               array_Symbol->getArrayType() == dataType::i8 || 
               array_Symbol->getArrayType() == dataType::i1 || 
               array_Symbol->getArrayType() == dataType::array_data) {
        reg_name = out_Arm.xRegAllocator.accessVariable(array_Symbol->getName());
    }
    }else if(auto* pointer_symbol = dynamic_cast<PointerSymbol*>(symbol)){
        if (pointer_symbol->getPointedType() == dataType::f32 || 
        pointer_symbol->getPointedType() == dataType::f64) {
        reg_name = out_Arm.dRegAllocator.accessVariable(pointer_symbol->getName());
    } else if (pointer_symbol->getPointedType() == dataType::i32 || 
               pointer_symbol->getPointedType() == dataType::i64 || 
               pointer_symbol->getPointedType() == dataType::i16 || 
               pointer_symbol->getPointedType() == dataType::i8 || 
               pointer_symbol->getPointedType() == dataType::i1 || 
               pointer_symbol->getPointedType() == dataType::array_data) {
        reg_name = out_Arm.xRegAllocator.accessVariable(pointer_symbol->getName());
    }
    }
    else{
        if(symbol->data->getType() == (dataType::f32) || symbol->data->getType() == (dataType::f64)) {
            reg_name = out_Arm.dRegAllocator.accessVariable(symbol->getName());
        }else if(symbol->data->getType() == (dataType::i32) || symbol->data->getType() == (dataType::i64) || symbol->data->getType() == (dataType::i16) || symbol->data->getType() == (dataType::i8) || symbol->data->getType() == (dataType::i1)||symbol->data->getType() == (dataType::array_data)) {
            reg_name = out_Arm.xRegAllocator.accessVariable(symbol->getName());
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
    if(symbol->getArrayType() == (dataType::f32) || symbol->getArrayType() == (dataType::f64)) {
        reg_name = out_Arm.dRegAllocator.accessParam(symbol->getName());
    }else if(symbol->getArrayType() == (dataType::i32) || symbol->getArrayType() == (dataType::i64) || symbol->getArrayType() == (dataType::i16) || symbol->getArrayType() == (dataType::i8) || symbol->getArrayType() == (dataType::i1)||symbol->getArrayType() == (dataType::array_data)) {
        reg_name = out_Arm.xRegAllocator.accessParam(symbol->getName());
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
        if(this->getReturnType() == dataType::f32 || this->getReturnType() == dataType::f64) 
        {OutArm::outString("\tMOV D0, " + return_value_str); 
        }else{
            OutArm::outString("\tMOV X0, " + return_value_str);
        }
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
    std::string ori_str;//目的地 （源参数说是）
    std::vector<std::string> ori_strs = out_Arm.func_Params_Regs[func_name];
    int i = 0;
    for (const auto& arg : this->arguments) {
        if (auto* array_symbol = dynamic_cast<ArraySymbol*>(arg)) {
            ori_str = ori_strs[i];
            arg_str = out_Arm.DispatchReg(array_symbol);
        }
        else if (auto* var_symbol = dynamic_cast<VarSymbol*>(arg)) {
            ori_str = ori_strs[i];
            arg_str = out_Arm.DispatchReg(var_symbol);
        } 
        OutArm::outString("\tMOV " + arg_str + ", " + ori_str);
        ++i;
    }  
    
    std::string call_str = "BL " + func_name;
    OutArm::outString("\t"+call_str);
    if (this->dest_sym) {
        if(this->function->getReturnType() == dataType::f32 || this->function->getReturnType() == dataType::f64) {
            OutArm::outString("\tMOV " + dest_str + ", D0"); // Assuming S0 is the return register for floating point
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
    out_Arm.globalAllocator.allocateFunc(func_name);
    OutArm::outString(func_name + ":");
    
    int stack_size = out_Arm.stackAllocator.calculateStackSize();
    OutArm::outString(out_Arm.stackAllocator.emitPrologue(stack_size));

    std::string param_str;
    std::vector<std::string> param_strs;
    // 输出函数参数
        
    for (const auto& param : this->params) {
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

    //int datasize = OutArm::getDataSize(this->sym); 暂时不用了 我们统一用x寄存器 所以偏移量为8
    int size = out_Arm.stackAllocator.allocateLocal( 8 ,this->sym->getName());
    
}

void AllocaArrayLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();

    //好吧 数组还是需要的哈  额额 实际不需要
    //int datasize = OutArm::getDataSize(this->array);
    int size = out_Arm.stackAllocator.allocateArray( 8 ,this->getDimensions(),this->array->getName());
}

void LoadLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.stackAllocator.RegVar_StackVar[dest_sym->getName()] = src_sym->getName();

    std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
    if(!out_Arm.globalAllocator.find_symbol(src_sym->getName()) && !out_Arm.stackAllocator.Tmp_StackAddress_InReg.count(src_sym->getName())){
        int offset = out_Arm.stackAllocator.getOffset(this->src_sym->getName());
        OutArm::outString("\tLDR " + dest_str + ", [SP, #" + std::to_string(offset) + "]");
    }else{
        std::string src_str = out_Arm.DispatchReg(this->src_sym);
        OutArm::outString("\tLDR " + dest_str + ", " + src_str);
    }
    
}

void StoreLLVM::out_arm_str()  {
    OutArm& out_Arm = OutArm::getInstance();
    out_Arm.stackAllocator.RegVar_StackVar[src_sym->getName()] = dest_sym->getName();
    
    std::string src_str = out_Arm.DispatchReg(this->src_sym);
    //store语句特殊处理下
    if(src_str.front() == '#' && this->src_sym->getDataType()==dataType::i32){
        std::string tmp_num_str = src_str;
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::i32, 1);
        src_str = out_Arm.DispatchReg(tmp);
        OutArm::outString("\tMOV " + src_str + ", " + tmp_num_str);
    }else if(src_str.front() == '#' && this->src_sym->getDataType()==dataType::f32){
        std::string tmp_num_str = src_str;
        VarSymbol* tmp = SymbolFactory::createTmpVarSymbolWithScope(dataType::f32, 1);
        src_str = out_Arm.DispatchReg(tmp);
        OutArm::outString("\tMOV " + src_str + ", " + tmp_num_str);
    }

    if(!out_Arm.globalAllocator.find_symbol(dest_sym->getName()) && !out_Arm.stackAllocator.Tmp_StackAddress_InReg.count(dest_sym->getName())){
        int offset = out_Arm.stackAllocator.getOffset(this->dest_sym->getName());
        //store 是否 只存 -8 的情况？ 还真是好像 。。。
        OutArm::outString("\tSTR " + src_str + ", [SP, #" + std::to_string(offset) + "]!");
        out_Arm.stackAllocator.stack_currentOffset -= offset; 
    }else{
        std::string dest_str = out_Arm.DispatchReg(this->dest_sym);
        OutArm::outString("\tSTR " + src_str + ", " + dest_str);
    }
}

//直接4offset 可能有隐患
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

        // 全局变量的情况
        if(out_Arm.globalAllocator.find_symbol(this->ptrval->getName())){
            out_Arm.globalAllocator.addSymbolToGlobal(this->dest_sym->getName(),this->ptrval->getName(),offset);
        }else{
            out_Arm.stackAllocator.addPtr(this->dest_sym->getName(), offset);
            
        }
        out_Arm.stackAllocator.RegVar_StackVar[this->getSrcSymbol()->getName()] = this->getDestSymbol()->getName();
    }else{//这里是[][]含有变量的情况
        
        //获取其所在地址
        std::string arr_str = "X8";
        out_Arm.stackAllocator.Tmp_StackAddress_InReg[this->getSrcSymbol()->getName()] = arr_str;

        std::string arr_offset_str;
        if(!out_Arm.globalAllocator.find_symbol(this->ptrval->getName()) && out_Arm.stackAllocator.hasVariable(this->getSrcSymbol()->getName())){
            arr_offset_str = std::to_string(out_Arm.stackAllocator.getOffset(this->getSrcSymbol()->getName()));
            OutArm::outString("\tADD " + arr_str + ", SP, #" + arr_offset_str);
        }
        // N维数组偏移量计算（通用方法）
        int offset = 0;
        int multiplier = 4;
        std::vector<int> dims = this->getDimensions();
        int i = this->getDimensions().size() - 1;
        
        for (auto it = container.rbegin(); it != container.rend(); ++it) {
            const auto& [data_type, symbol_ptr] = *it;
                if (i >= 0) {
                    if(it->second->getType() == symType::constant_nonvar){
                        offset += (std::stoi(getSymOut(symbol_ptr))) * multiplier;
                    }else{
                        std::string tmp_str = out_Arm.DispatchReg(symbol_ptr);
                        std::string tmp_num_str = std::to_string(multiplier * 4);
                        if(multiplier == 1){
                            out_Arm.outString("\tMOV "+ tmp_str + ", #" + tmp_num_str);
                        }else{
                            out_Arm.outString("\tMUL "+ tmp_str + ", " + tmp_str + ", #" + tmp_num_str);
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
            OutArm::outString("\tADD " + arr_str + ", " + arr_str  + ", #" + tmp_num_str);
        }
            out_Arm.stackAllocator.Tmp_StackAddress_InReg[this->getDestSymbol()->getName()] = arr_str;
    }
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

void XRegAllocator::promoteToRegister(std::string symbol) {
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    bool is_in_stack = stackAllocator.hasVariable(symbol);
    if (is_in_stack) {
        int stack_offset = stackAllocator.getOffset(symbol);
        std::string reg_name = this->getRegister(symbol);
        if (reg_name.empty()) {
            throw std::runtime_error("No free registers available for promotion");
        }
        OutArm::outString("\tLDR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
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
        throw std::runtime_error("No register allocated for spilling");
    }
    // bool is_in_stack = stackAllocator.hasVariable(symbol);
    // if(is_in_stack) {
    //     stack_offset = stackAllocator.getOffset(symbol);
    // }else{
    //     stack_offset = stackAllocator.allocateLocal(symbol);
    // }
        OutArm::outString("\tSTR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
   
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
        OutArm::outString("\tLDR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
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
    // bool is_in_stack = stackAllocator.hasVariable(symbol);
    // if(is_in_stack) {
    //     stack_offset = stackAllocator.getOffset(symbol);
    // }else{
    //     stack_offset = stackAllocator.allocateLocal(symbol);
    // }
          OutArm::outString("\tSTR " + reg_name + ", [SP, #" + std::to_string(stack_offset) + "]");
   
    // 清除寄存器映射
    //this->freeRegister(reg_name);
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