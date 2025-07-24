#pragma once

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../BasicBlock.hpp"
#include <string>
#include <map>
#include <set>

class StackAllocator {
    private:
        static StackAllocator* stackInstance; // 单例模式
        std::map<std::string, int> localVarOffsets; // 变量名 -> 栈偏移
        int currentOffset = 0;                      // 当前栈指针偏移值
        
        // 辅助函数
        int align(int value, int alignment);
        int getTypeSize(Symbol* symbol);

        // 构造函数
        StackAllocator() = default;
        
    public:
        std::set<std::string> usedFloatRegisters;
        std::set<std::string> usedRegisters;
        
        static StackAllocator& getInstance() {
            if (!stackInstance) {
                stackInstance = new StackAllocator();
            }
            return *stackInstance;
        }

        // 核心功能函数
        int allocateLocal(Symbol *symbol);
        int allocateArray(ArraySymbol* arraySymbol);
        void addPtr(Symbol *symbol, int offset);

        int calculateRegisterSaveAreaSize();
        void emitRegisterSave(std::ostream& out, int offset) const;
        void emitRegisterRestore(std::ostream& out, int offset) const;

        int calculateStackSize();
        int getOffset(Symbol *symbol);
        std::string emitPrologue(int stackSize) ;
        std::string emitEpilogue(int stackSize) ;
        int getCurrentOffset() const;
        
        // 辅助功能x
        void addUsedRegister(std::string& reg);
        void addUsedFloatRegister(std::string& reg);
        void printAllocation(std::ostream& out) const;

        void reset();
        std::string getStackPointer(Symbol *symbol) const;
        void printAllocation(std::ostream &out);
        bool hasVariable(const std::string &varName) ;
        
    };