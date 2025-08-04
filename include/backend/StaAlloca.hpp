#pragma once

#include "../llvm.hpp"
#include "../sym.hpp"
//#include "../BasicBlock.hpp"
#include <string>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <climits>
#include <list>

class StackAllocator {
    private:
        static StackAllocator* stackInstance; // 单例模式
        std::unordered_map<std::string, int> localVarOffsets;
        int currentTop = 4;                      // 栈顶
        int getTypeSize(Symbol* symbol);
        


        // 构造函数
        StackAllocator() = default;
        
    public:
        
        //前为函数名 后为 溢出参数对应的（按顺序）栈帧位置
        std::unordered_map<std::string, int> func_Params_Stacks;

        //前为溢出参数  总栈帧大小
        std::unordered_map<std::string,int> func_overflowstacksize;

        std::vector<std::pair<std::string, int>> func_xregister_save; //0为x 1为d
        std::vector<std::pair<std::string, int>> func_sregister_save;
        int stack_currentOffset = 0;    // 栈帧指针；
        std::unordered_map<std::string, std::string> RegVar_StackVar; //寄存器 栈帧 映射
        std::unordered_set<std::string> Tmp_StackAddress_InReg; //前变量 后 寄存器（统一为X8） ；getelem时候 临时存一下  

        std::set<std::string> usedFloatRegisters;
        std::set<std::string> usedRegisters;
        
        static StackAllocator& getInstance() {
            if (!stackInstance) {
                stackInstance = new StackAllocator();
            }
            return *stackInstance;
        }
        void set_top(int value);
        // 核心功能函数
        int align(int value, int alignment);
        int allocateLocal(int size, std::string symbol);
        int allocateArray(int elementSize, const std::vector<int>& dimensions ,std::string arraySymbol);
        void addArrayPtrwithOffset(std::string symbol, std::string array_symbol, int offset);

        int calculateRegisterSaveAreaSize(int overflowsize);
        void emitRegisterSave(std::ostream& out, int offset) const;
        void emitRegisterRestore(std::ostream& out, int offset) const;

        int calculateStackSize(int overflowsize);
        int getOffset(std::string symbol);
        int getParamOffset(std::string symbol);
        bool isTmpVar(std::string symbol);
        std::string emitPrologue(int stackSize) ;
        std::string emitEpilogue(int stackSize) ;
        int getCurrentTop() const;
        
        // 辅助功能x
        void addUsedRegister(std::string& reg);
        void addUsedFloatRegister(std::string& reg);
        void printAllocation(std::ostream& out) const;

        void reset();
        std::string getStackPointer(std::string symbol) const;
        void printAllocation(std::ostream &out);
        bool hasVariable(const std::string &varName) ;
        
    };
