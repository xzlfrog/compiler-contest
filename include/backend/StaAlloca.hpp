#pragma once

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../BasicBlock.hpp"
#include <string>
#include <map>

class StackAllocator {
    private:
        std::map<std::string, int> localVarOffsets; // 变量名 -> 栈偏移
        int currentOffset = 0;                      // 当前栈指针偏移值
        
        // 辅助函数
        int align(int value, int alignment);
        int getTypeSize(const std::string& type);
        
    public:
        // 构造函数
        StackAllocator() = default;
        
        // 核心功能函数
        int allocateLocal(Symbol *symbol);
        int calculateStackSize(BasicBlock *block);
        int getOffset(const std::string &varName);
        void emitPrologue(std::ostream &out, int stackSize);
        void emitEpilogue(std::ostream &out, int stackSize);
        int getCurrentOffset() const;
        
        // 辅助功能x
        void reset();
        std::string getStackPointer(Symbol *symbol) const;
        void printAllocation(std::ostream &out);
        bool hasVariable(const std::string &varName) const;
    };
