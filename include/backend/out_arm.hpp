#include "GlobalAlloca.hpp"
#include "RegAlloca.hpp"
#include "StaAlloca.hpp"

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../SSA.hpp"

#include <fstream>
#include <string>

/*class OutArm {
    std::ofstream out;

public:
    // 构造函数打开输出文件
    OutArm(const std::string &filename);
    
    void outString(FILE* file, const std::string &str) const;

    // 输出整个模块
    void outputModule(Module *module);

    // 输出单个函数
    void outputFunction(BasicBlock *func);

    // 输出一条指令
    void outputInstruction(LLVM *llvm);

    // 输出函数入口（prologue）
    void outputPrologue(Function *func);

    // 输出函数出口（epilogue）
    void outputEpilogue(Function *func);

    std::string ArithmeticOpConvert(LLVMtype *op);
    std::string ASMDOperation(LLVM* llvm);
    std::string ComparisonOperation(ArithmeticOperationLLVM* cmpllvm);
    
    int getNumberOfOperands(ConstVarSymbol *constvarsym) const;
    int getNumberOfOperands(ConstSymbol *constsym) const;
    
    std::string getIntNumberOfOperands(ConstVarSymbol *sym) const;
    std::string getIntNumberOfOperands(ConstSymbol *sym) const;
};*/

