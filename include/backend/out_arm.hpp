#pragma once
#include "GlobalAlloca.hpp"
#include "RegAlloca.hpp"
#include "StaAlloca.hpp"

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../SSA.hpp"

#include <fstream>
#include <string>

FILE* outputArmFile;
class OutArm {
    std::ofstream out;
    GlobalAllocator globalAllocator;
    StackAllocator stackAllocator;
    RegisterAllocator registerAllocator;

public:
    // 构造函数打开输出文件
    OutArm(const std::string &filename);
    
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

    std::string ArithmeticOpConvert(LLVMtype *op);
    std::string ASMDOperation(LLVM* llvm);
    std::string ComparisonOperation(ArithmeticOperationLLVM* cmpllvm);
    
    int getNumberOfOperands(ConstVarSymbol *constvarsym) const;
    int getNumberOfOperands(ConstSymbol *constsym) const;
    
    std::string getIntNumberOfOperands(ConstVarSymbol *sym) const;
    std::string getIntNumberOfOperands(ConstSymbol *sym) const;
};

void out_arm(FILE* outputFile, ModuleList* module_list) {
    OutArm out(outputFile);
    
    // 遍历模块列表
    for (Module* module = module_list->head; module != nullptr; module = module->next) {
        // 输出模块名称
        out.outString(outputFile, ".module start");
        
        // 遍历每个llvm语句
        for (LLVM* llvm = module->head; llvm != nullptr; llvm = llvm->next) {
            llvm->out_arm_str();
        }
        
        insertContentToFileFront(outputFile, GlobalAllocator::emitAssemblyToString());

        out.outString(outputFile, ".endmodule");
    }
}

void insertContentToFileFront(const std::string& filename, const std::string& contentToInsert);