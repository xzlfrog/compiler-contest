#pragma once

#include <map>
#include "../../include/sym.hpp"
#include "../../include/backend/StaAlloca.hpp"

#include <list>
#include <unordered_map>
#include <string>
#include <stack>

#define XREG_SIZE_START1 0
#define XREG_SIZE_END1   7 // X0-X7
#define XREG_SIZE_START2 9 
#define XREG_SIZE_END2   15 // X9-X15 本该为 易失寄存器 此处同样为 调用时保存寄存器
#define XREG_SIZE_START3 19
#define XREG_SIZE_END3   28 // X19-X28 被调用者保存寄存器

#define DREG_SIZE_START1 0
#define DREG_SIZE_END1   7 // D0-D7
#define DREG_SIZE_START2 8
#define DREG_SIZE_END2   31 // D8-D31 被调用者保存浮点寄存器

extern std::ofstream outputArmFile;
class RegisterAllocator {
    public:
        RegisterAllocator(const std::vector<std::string>& available_registers){}

        std::vector<Symbol*> Registers; // 实际情况 寄存器数组，存储指向 变量 的指针
        std::unordered_map<Symbol*, int> var_to_reg; // 理论映射 变量 到 索引的映射

        // 为某个Symbol分配一个物理寄存器
        virtual void allocateParamSpace(Symbol* symbol) = 0;
        virtual void allocateOtherSpace(Symbol* symbol) = 0;
    
        // 获取已分配寄存器
        virtual std::string getRegister(Symbol* symbol) const = 0;

        virtual std::string accessVariable(Symbol* symbol) = 0;
        virtual std::string accessParam(Symbol* symbol) = 0;

        // 检查寄存器是否装载对应symbol
        bool isRegisterUsed(Symbol* symbol) const;
    
        // 检查是否所有寄存器都已被使用
        // 感觉没啥用但暂时保留
        bool isAllRegistersUsed() const;
    
        // 释放寄存器（用于临时值）
        void freeRegister(std::string reg_name);

        // 获取第一个空闲寄存器
        //virtual std::string getFirstFreeRegister() const = 0;
    
        // 保存调用前需要保留的寄存器（calle-saved）
       //void saveRegisters(std::ostream &out);

        //涵姐在栈帧staalloca.hpp里写了

        // 恢复调用后需恢复的寄存器
        //void restoreRegisters(std::ostream &out);

        void reset();

        // 内部方法
    virtual void promoteToRegister( Symbol* symbol) = 0;
    virtual void spillToStack(Symbol* symbol) = 0;
        
    };

class XRegAllocator : public RegisterAllocator {
    public:

        XRegAllocator() : RegisterAllocator({"X0", "X1", "X2", "X3", "X4", "X5", "X6", "X7",
                                              "X9", "X10", "X11", "X12", "X13", "X14", "X15",
                                              "X19", "X20", "X21", "X22", "X23", "X24", "X25",
                                              "X26", "X27", "X28"}) {}

        int current_reg_offset1 = 0; // 当前偏移量 0-7
        int current_reg_offset2 = 9; // 当前偏移量 9-15
        int current_reg_offset3 = 19; // 当前偏移量 19-28 暂时不用3 因为未区分临时变量
    
        void allocateParamSpace(Symbol* symbol) override ;
        void allocateOtherSpace(Symbol* symbol) override ;
        std::string getRegister(Symbol* symbol) const override;;


        // 访问变量（使用或分配）
        std::string accessVariable(Symbol* symbol) override ;
        std::string accessParam(Symbol* symbol) override;
        
        void promoteToRegister(Symbol* symbol) override ;
        void spillToStack(Symbol* symbol) override ;
};

class DRegAllocator : public RegisterAllocator {
    public:
        DRegAllocator() : RegisterAllocator({"D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7",
                                              "D8", "D9", "D10", "D11", "D12", "D13", "D14",
                                              "D15", "D16", "D17", "D18", "D19", "D20", "D21",
                                              "D22", "D23", "D24", "D25", "D26", "D27", "D28",
                                              "D29", "D30", "D31"}) {}

        int current_reg_offset1 = 0; // 当前偏移量 0-7
        int current_reg_offset2 = 0; // 当前偏移量 8-31
        void allocateParamSpace(Symbol* symbol) override ;
        void allocateOtherSpace(Symbol* symbol) override ;
        std::string getRegister(Symbol* symbol) const override;;
        

        // 访问变量（使用或分配）
        std::string accessVariable(Symbol* symbol) override ;
        std::string accessParam(Symbol* symbol) override;

        void promoteToRegister(Symbol* symbol) override ;
        void spillToStack(Symbol* symbol) override ;
};

class ZERORegAllocator : public RegisterAllocator {
    public:
        std::string XZR = "XZR"; // ARM zero register, always zero
};




    