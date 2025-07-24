#pragma once

#include <map>
#include "../../include/sym.hpp"

#include <list>
#include <unordered_map>
#include <string>
#include <stack>
#define XREG_SIZE 29 // x0-x28
#define VREG_SIZE 29 // v0-v28


/*class RegisterAllocator {
    public:
        RegisterAllocator(const std::vector<std::string>& available_registers){}

        std::vector<Symbol*> Registers; // 寄存器数组，存储指向 变量 的指针
        std::unordered_map<Symbol*, size_t> var_to_reg; // 变量 到 索引的映射
        std::list<std::string> lru_list;

        // 为某个Symbol分配一个物理寄存器
        virtual std::string allocateSpace(Symbol* symbol) = 0;
    
        // 获取已分配寄存器
        virtual std::string getRegister(Symbol* symbol) const = 0;

        virtual std::string accessVariable(Symbol* symbol) = 0; ;

        // 检查寄存器是否已被使用
        bool isRegisterUsed(Symbol* symbol) const;
    
        // 检查是否所有寄存器都已被使用
        bool isAllRegistersUsed() const;
    
        // 释放寄存器（用于临时值）
        void freeRegister(std::string reg_name);

        // 获取第一个空闲寄存器
        virtual std::string getFirstFreeRegister() const = 0;
    
        // 保存调用前需要保留的寄存器（calle-saved）
        void saveRegisters(std::ostream &out);

        // 恢复调用后需恢复的寄存器
        void restoreRegisters(std::ostream &out);

        // 内部方法
    void promoteToRegister(const Symbol* symbol);
    void spillToStack(const Symbol* symbol);
        
    };

class XRegAllocator : public RegisterAllocator {
    public:
    std::string allocateSpace(Symbol* symbol) override ;
    std::string getRegister(Symbol* symbol) const override;;
    std::string getFirstFreeRegister() const override;

    // 访问变量（使用或分配）
    std::string accessVariable(Symbol* symbol) override ;

};

class SRegAllocator : public RegisterAllocator {
    std::string allocateSpace(Symbol* symbol) override ;
    std::string getRegister(Symbol* symbol) const override;;
    std::string getFirstFreeRegister() const override;

     // 访问变量（使用或分配）
     std::string accessVariable(Symbol* symbol) override ;
};

class ZERORegAllocator : public RegisterAllocator {
    public:
        std::string XZR = "XZR"; // ARM zero register, always zero
};*/



    