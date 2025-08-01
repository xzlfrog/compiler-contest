#include "../../include/backend/StaAlloca.hpp"
#include <stdexcept>

// 静态成员定义（唯一一份）
StackAllocator* StackAllocator::stackInstance = nullptr;

void StackAllocator::set_top(int value){
    this->currentTop = value;
}

int StackAllocator::align(int value, int alignment) {
    if (alignment <= 0 || (alignment & (alignment - 1))) {
        throw std::invalid_argument("Alignment must be a power of 2");
    }
    return (value + alignment - 1) & ~(alignment - 1);
}

void StackAllocator::addUsedRegister(std::string& reg) {
    if (reg.size() < 2 || reg[0] != 'X') return;
    
    try {
        int num = std::stoi(reg.substr(1));
        if (num >= 19 && num <= 28) {
            usedRegisters.insert(reg);
        }
    } catch (...) {
        // 忽略无效寄存器名
    }
}

void StackAllocator::addUsedFloatRegister(std::string& reg) {
    if (reg.size() < 2 || reg[0] != 'D') return;
    
    try {
        int num = std::stoi(reg.substr(1));
        if (num >= 8 && num <= 31) {
            usedFloatRegisters.insert(reg);
        }
    } catch (...) {
        // 忽略无效寄存器名
    }
}

int StackAllocator::calculateRegisterSaveAreaSize() {
    int size = 16; // FP(x29)和LR(x30)必须保存
    
    // 被调用者保存的通用寄存器 (x19-x28)
    size += usedRegisters.size() * 8;
    
    // 被调用者保存的浮点寄存器 (D8-D31s)
    size += usedFloatRegisters.size() * 8;
    
    // 确保16字节对齐
    return size;
}

bool StackAllocator::isTmpVar(std::string symbol){
    auto it = this->localVarOffsets.find(symbol);
    if (it != this->localVarOffsets.end()) {
        return false;
    }
    return true;
}

int StackAllocator::getOffset(std::string symbol) {
    
    const std::string& varName = symbol;
    auto it = this->localVarOffsets.find(varName);
    if (it != this->localVarOffsets.end()) {
        return it->second - this->stack_currentOffset ;
    }
    
    throw std::runtime_error("Variable not found: " + varName);
}   



//返回地址后 偏移量变了 下面数组同理
int StackAllocator::allocateLocal(int size, std::string symbol) {
    int address = currentTop;
    std::string name = symbol;
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate variable: " + name);
    }
    
    this->currentTop -= size;
    this->localVarOffsets[name] = this->currentTop;
    
    return address;
}

//返回的是头地址
int StackAllocator::allocateArray(int elementSize, const std::vector<int>& dimensions ,std::string arraySymbol) {
    int address = currentTop;
    const std::string& name = arraySymbol;
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate variable: " + name);
    }

    int totalSize = elementSize;
    for (int dim : dimensions) {
        totalSize *= dim;
    }

    this->currentTop -= totalSize;
    this->localVarOffsets[name] = this->currentTop;

    return address;
}

//未对齐可能有隐患
void StackAllocator::addArrayPtrwithOffset(std::string symbol, std::string array_symbol, int offset) {
    const std::string& name = symbol;
    if (hasVariable(name)) {
        return; // 如果变量已经存在，则不需要重新添加
    }
    // Store the pointer with its offset
    localVarOffsets[name] = localVarOffsets[array_symbol] + offset;
     //加减指针要打印出来吧。。。 这里不是真正的栈帧顶啦！
}

int StackAllocator::calculateStackSize() {
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int totalSize = -currentTop + registerSaveSize;
    return totalSize;
}

void StackAllocator::emitRegisterSave(std::ostream& out, int offset) const {
    for (const auto& reg : usedRegisters) {
        out << "    STR " << reg << ", [SP, #" << offset << "]\n";
        offset += 8;
    }
    
    for (const auto& reg : usedFloatRegisters) {
        out << "    STR " << reg << ", [SP, #" << offset << "]\n";
        offset += 8;
    }
}

void StackAllocator::emitRegisterRestore(std::ostream& out, int offset) const {
    for (const auto& reg : usedFloatRegisters) {
        out << "    LDR " << reg << ", [SP, #" << offset << "]\n";
        offset += 8;
    }
    
    for (const auto& reg : usedRegisters) {
        out << "    LDR " << reg << ", [SP, #" << offset << "]\n";
        offset += 8;
    }
}
std::string StackAllocator::emitPrologue(int stackSize) {
    std::ostringstream out;
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int variableAreaSize = stackSize - registerSaveSize;
    
    //out << "\t; Function prologue\n";
    out << "\tSTP X29, X30, [SP, #-" << registerSaveSize << "]!\n";
    out << "\tMOV X29, SP\n";
    
    return out.str();
}

std::string StackAllocator::emitEpilogue(int stackSize) {
    std::ostringstream out;
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int current_top = this->stack_currentOffset;
    
    //out << "\n\t; Function epilogue\n";
    
    if (current_top != 0) {
        if(current_top > -4095){
            out << "\tADD SP, SP, #" << -current_top << "\n";
        }else{
            std::string reg = "X8";
            int imm = -current_top;

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
                        out << "\t" << instr << " " << reg_new << ", #" << std::to_string(parts[i]) << "\n";
                    } else {
                        out << "\t" << instr << " " << reg_new << ", #" << std::to_string(parts[i]) << ", LSL #" << std::to_string(shifts[i]) << "\n";
                    }
                    first = false;
                }
            }
            out << "\tADD SP, SP, " << reg_new << "\n";
            // 如果全为 0
        }
    }
    
    // if (!usedRegisters.empty() || !usedFloatRegisters.empty()) {
    //     out << "\t; Restore callee-saved registers\n";
    //     emitRegisterRestore(out, 16);
    // }
    
    out << "\tLDP X29, X30, [SP], #" << registerSaveSize << "\n";  
    return out.str();
}

void StackAllocator::reset() {
    localVarOffsets.clear();
    currentTop = 0;
    usedRegisters.clear();
    usedFloatRegisters.clear();
}

void StackAllocator::printAllocation(std::ostream& out) const {
    out << "Stack Allocation:\n";
    out << "Total size: " << (-currentTop) << " bytes\n";
    out << "Variables:\n";
    for (const auto& entry : localVarOffsets) {
        out << "  " << entry.first << ": " << entry.second << "\n";
    }
    out << "Used registers:\n";
    for (const auto& reg : usedRegisters) {
        out << "  " << reg << "\n";
    }
    for (const auto& reg : usedFloatRegisters) {
        out << "  " << reg << "\n";
    }
}

bool StackAllocator::hasVariable(const std::string& varName) {
    return localVarOffsets.find(varName) != localVarOffsets.end();
}

int StackAllocator::getCurrentTop() const {
    return currentTop;
}
