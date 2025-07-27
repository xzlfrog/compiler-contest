#include "../../include/backend/StaAlloca.hpp"
#include <stdexcept>

// 静态成员定义（唯一一份）
StackAllocator* StackAllocator::stackInstance = nullptr;

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
    return align(size, 16);
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
        return it->second ;
    }
    // }else if(is_array) {
    //     return allocateArray(symbol);
    // }else{
    //     return allocateLocal(symbol);
    //x}
    throw std::runtime_error("Variable not found: " + varName);
}   

int StackAllocator::allocateLocal(int size, std::string symbol) {
    std::string name = symbol;
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate variable: " + name);
    }
    
    int alignment = size >= 8 ? 8 : 4;
    
    currentOffset = align(currentOffset - size, alignment);
    localVarOffsets[name] = currentOffset;
    
    return currentOffset;
}

int StackAllocator::allocateArray(int elementSize, const std::vector<int>& dimensions ,std::string arraySymbol) {
    const std::string& name = arraySymbol;
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate variable: " + name);
    }

    //int elementSize = getTypeSize(arraySymbol);
    //const std::vector<int>& dimensions = arraySymbol->getDimensions(); // Assuming this method exists to get the dimensions
    int totalSize = elementSize;
    for (int dim : dimensions) {
        totalSize *= dim;
    }

    // Align the total size to the largest element size
    int alignment = elementSize >= 8 ? 8 : 4;
    currentOffset = align(currentOffset - totalSize, alignment);
    localVarOffsets[name] = currentOffset;

    return currentOffset;
}

int StackAllocator::calculateStackSize() {
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int totalSize = -currentOffset + registerSaveSize;
    return align(totalSize, 16);
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
    
    out << "\t; Function prologue\n";
    out << "\tSTP X29, X30, [SP, #-" << registerSaveSize << "]!\n\t; Save FP and LR\n";
    out << "\tMOV X29, SP\n\t; Set new FP\n";
    
    if (!usedRegisters.empty() || !usedFloatRegisters.empty()) {
        out << "\t; Save callee-saved registers\n";
        emitRegisterSave(out, 16);
    }
    
    if (variableAreaSize > 0) {
        out << "\tSUB SP, SP, #" << variableAreaSize << "      // Allocate stack space\n";
    }
    
    return out.str();
}

std::string StackAllocator::emitEpilogue(int stackSize) {
    std::ostringstream out;
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int variableAreaSize = stackSize - registerSaveSize;
    
    out << "\n\t; Function epilogue\n";
    
    if (variableAreaSize > 0) {
        out << "\tADD SP, SP, #" << variableAreaSize << "\n\t; Deallocate stack space\n";
    }
    
    if (!usedRegisters.empty() || !usedFloatRegisters.empty()) {
        out << "\t; Restore callee-saved registers\n";
        emitRegisterRestore(out, 16);
    }
    
    out << "\tLDP X29, X30, [SP], #" << registerSaveSize << "\n\t; Restore FP and LR\n";  
    return out.str();
}

void StackAllocator::reset() {
    localVarOffsets.clear();
    currentOffset = 0;
    usedRegisters.clear();
    usedFloatRegisters.clear();
}

void StackAllocator::printAllocation(std::ostream& out) const {
    out << "Stack Allocation:\n";
    out << "Total size: " << (-currentOffset) << " bytes\n";
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

int StackAllocator::getCurrentOffset() const {
    return currentOffset;
}

//未对齐可能有隐患
void StackAllocator::addPtr(std::string symbol, int offset) {
    const std::string& name = symbol;
    if (hasVariable(name)) {
        return; // 如果变量已经存在，则不需要重新添加
    }
    // Store the pointer with its offset
    localVarOffsets[name] = this->currentOffset + offset;
    this->currentOffset += offset; //加减指针要打印出来吧。。。 这里不是真正的栈帧顶啦！
}