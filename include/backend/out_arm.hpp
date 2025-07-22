#pragma once
#include "GlobalAlloca.hpp"
#include "RegAlloca.hpp"
#include "StaAlloca.hpp"

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../SSA.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

extern std::ofstream outputArmFile;
class  OutArm {
private:
    static OutArm* instance;
    std::string outputFileName;
    // 禁止直接创建实例

    // 禁止拷贝和赋值
    OutArm(const OutArm&) = delete;
    OutArm& operator=(const OutArm&) = delete;
    // 私有构造，外面不能直接创建
    OutArm() = default;


public:

    static OutArm& getInstance() {
        if (!instance) {
            instance = new OutArm();
        }
        return *instance;
    }

    void setName(std::string name) {
        outputFileName = name;
    }
    
    std::ofstream out;
    GlobalAllocator globalAllocator;
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    XRegAllocator xRegAllocator ;
    DRegAllocator dRegAllocator ;
    // 构造函数打开输出文件
    
    static void outString(const std::string &str);

    static std::string ArithmeticOpConvert(LLVMtype op);
    static std::string ASMDOperation(ArithmeticOperationLLVM* ASMDllvm);
    static std::string ComparisonOperation(ArithmeticOperationLLVM* cmpllvm);
    static std::string RemOperation(ArithmeticOperationLLVM* REMllvm);
    
    static std::string getIntNumberOfOperands(Symbol *sym) ;
   //static std::string getIntNumberOfOperands(ConstSymbol *sym) ;

    static std::string DispatchReg(Symbol* symbol);
    static std::string DispatchRegParam(Symbol* symbol);
    
        // 输出整个模块
   // void outputModule(Module *module);

    // 输出单个函数
   // void outputFunction(BasicBlock *func);

    // 输出一条指令
   // void outputInstruction(LLVM *llvm);

    // 输出函数入口（prologue）
   // void outputPrologue(Function *func);

    // 输出函数出口（epilogue）
    //void outputEpilogue(Function *func);
};

void insertContentToFileFront(std::ofstream& outputFile, const std::string& contentToInsert);

void out_arm(std::string outputFileName, ModuleList* module_list);