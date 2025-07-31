#include "../../include/backend/StaAlloca.hpp"
#include <stdexcept>

// 静态成员定义（唯一一份）
StackAllocator* StackAllocator::stackInstance = nullptr;


// int StackAllocator::align(int value, int alignment) {
//     if (alignment <= 0 || (alignment & (alignment - 1))) {
//         throw std::invalid_argument("Alignment must be a power of 2");
//     }
//     return (value + alignment - 1) & ~(alignment - 1);
// }

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
        return this->stack_currentOffset - it->second;
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
    
    this->localVarOffsets[name] = this->currentTop;
    this->currentTop += size;
    
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

    this->localVarOffsets[name] = this->currentTop;
    this->currentTop += totalSize;

    return address;
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
    
    // if (!usedRegisters.empty() || !usedFloatRegisters.empty()) {
    //     out << "\t; Save callee-saved registers\n";
    //     emitRegisterSave(out, 16);
    // }
    
    // if (variableAreaSize > 0) {
    //     out << "\tSUB SP, SP, #" << variableAreaSize << "      // Allocate stack space\n";
    // }
    
    return out.str();
}

std::string StackAllocator::emitEpilogue(int stackSize) {
    std::ostringstream out;
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int variableAreaSize = stackSize - registerSaveSize;
    
    //out << "\n\t; Function epilogue\n";
    
    if (variableAreaSize > 0) {
        out << "\tADD SP, SP, #" << variableAreaSize << "\n";
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

//未对齐可能有隐患
void StackAllocator::addArrayPtrwithOffset(std::string symbol, std::string array_symbol, int offset) {
    const std::string& name = symbol;
    if (hasVariable(name)) {
        return; // 如果变量已经存在，则不需要重新添加
    }
    // Store the pointer with its offset
    localVarOffsets[name] = this->currentTop - localVarOffsets[array_symbol] + offset;
     //加减指针要打印出来吧。。。 这里不是真正的栈帧顶啦！
}