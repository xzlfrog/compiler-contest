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

std::ofstream outputArmFile;
class OutArm {
public:
    std::ofstream out;
    GlobalAllocator globalAllocator;
    StackAllocator stackAllocator;
    XRegAllocator xRegAllocator;
    DRegAllocator dRegAllocator;
    // 构造函数打开输出文件
    OutArm(const std::string &filename){
        outputArmFile.open(filename, std::ios::out | std::ios::trunc);
    
    if (!outputArmFile.is_open()) {
        std::cerr << "Error: Cannot open output file '" << filename << "'\n";
        std::exit(EXIT_FAILURE);
    }
    }
    
    static void outString(const std::string &str);

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

    static std::string ArithmeticOpConvert(LLVMtype *op);
    static std::string ASMDOperation(LLVM* llvm);
    static std::string ComparisonOperation(ArithmeticOperationLLVM* cmpllvm);
    static std::string RemOperation(ArithmeticOperationLLVM* REMllvm);

    int getNumberOfOperands(ConstVarSymbol *constvarsym) const;
    int getNumberOfOperands(ConstSymbol *constsym) const;
    
    std::string getIntNumberOfOperands(ConstVarSymbol *sym) const;
    std::string getIntNumberOfOperands(ConstSymbol *sym) const;
};

void insertContentToFileFront(const std::string& filename, const std::string& contentToInsert);

void out_arm(FILE* outputFile, ModuleList* module_list) {
    OutArm out(outputFile);
    
    // 遍历模块列表
    for (Module* module = module_list->head; module != nullptr; module = module->next) {
        // 输出模块名称
        out.outString(".module start");
        
        // 遍历每个llvm语句
        for (LLVM* llvm = module->head; llvm != nullptr; llvm = llvm->next) {
            llvm->out_arm_str();
        }
        
        insertContentToFileFront(outputFile, out.globalAllocator.emitAssemblyToString());

        out.outString(".endmodule");
    }
}

void insertContentToFileFront(const std::string& filename, const std::string& contentToInsert);