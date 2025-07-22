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

int StackAllocator::getTypeSize(Symbol* symbol) {
    dataType dtype = symbol->getDataType();
    switch(dtype) {
        case i32: case f32: return 4;
        case i64: case f64: return 8;
        case i1: case i8: return 1;
        case i16: return 2;
        default: return 4; // 默认4字节
    }
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

int StackAllocator::getOffset(const std::string &varName) {
    auto it = localVarOffsets.find(varName);
    if (it != localVarOffsets.end()) {
        return it->second;
    }
    throw std::runtime_error("Variable not found: " + varName);
}   

int StackAllocator::allocateLocal(Symbol* symbol) {
    std::string name = symbol->getName();
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate variable: " + name);
    }
    
    int size = getTypeSize(symbol);
    int alignment = size >= 8 ? 8 : 4;
    
    currentOffset = align(currentOffset - size, alignment);
    localVarOffsets[name] = currentOffset;
    
    return currentOffset;
}

int StackAllocator::allocateArray(ArraySymbol* arraySymbol) {
    const std::string& name = arraySymbol->getName();
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate variable: " + name);
    }

    int elementSize = getTypeSize(arraySymbol);
    const std::vector<int>& dimensions = arraySymbol->getDimensions(); // Assuming this method exists to get the dimensions
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
        out << "    str " << reg << ", [sp, #" << offset << "]\n";
        offset += 8;
    }
    
    for (const auto& reg : usedFloatRegisters) {
        out << "    str " << reg << ", [sp, #" << offset << "]\n";
        offset += 8;
    }
}

void StackAllocator::emitRegisterRestore(std::ostream& out, int offset) const {
    for (const auto& reg : usedFloatRegisters) {
        out << "    ldr " << reg << ", [sp, #" << offset << "]\n";
        offset += 8;
    }
    
    for (const auto& reg : usedRegisters) {
        out << "    ldr " << reg << ", [sp, #" << offset << "]\n";
        offset += 8;
    }
}
std::string StackAllocator::emitPrologue(int stackSize) {
    std::ostringstream out;
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int variableAreaSize = stackSize - registerSaveSize;
    
    out << "    ;Function prologue\n";
    out << "    stp x29, x30, [sp, #-" << registerSaveSize << "]!  // Save FP and LR\n";
    out << "    mov x29, sp                                    // Set new FP\n";
    
    if (!usedRegisters.empty() || !usedFloatRegisters.empty()) {
        out << "    ;Save callee-saved registers\n";
        emitRegisterSave(out, 16);
    }
    
    if (variableAreaSize > 0) {
        out << "    sub sp, sp, #" << variableAreaSize << "      // Allocate stack space\n";
    }
    
    return out.str();
}

std::string StackAllocator::emitEpilogue(int stackSize) {
    std::ostringstream out;
    int registerSaveSize = calculateRegisterSaveAreaSize();
    int variableAreaSize = stackSize - registerSaveSize;
    
    out << "    // Function epilogue\n";
    
    if (variableAreaSize > 0) {
        out << "    add sp, sp, #" << variableAreaSize << "      // Deallocate stack space\n";
    }
    
    if (!usedRegisters.empty() || !usedFloatRegisters.empty()) {
        out << "    // Restore callee-saved registers\n";
        emitRegisterRestore(out, 16);
    }
    
    out << "    ldp x29, x30, [sp], #" << registerSaveSize << " // Restore FP and LR\n";
    out << "    ret                                            // Return\n";
    
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
void StackAllocator::addPtr(Symbol *symbol, int offset) {
    const std::string& name = symbol->getName();
    if (hasVariable(name)) {
        throw std::runtime_error("Duplicate pointer: " + name);
    }
    
    // Store the pointer with its offset
    localVarOffsets[name] = offset;
}