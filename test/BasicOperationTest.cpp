#include"../include/BasicOperations.hpp"
#include"../include/LLVMFactory.hpp"
#include"../include/data.hpp"
#include<iostream>

int main(){
    //算术指令/逻辑运算指令/比较运算指令测试
    BasicSymbol* a=SymbolFactory::createVarSymbol("a",dataType::f32);
    a->setScope(1);
    BasicSymbol* b=SymbolFactory::createConstVarSymbolWithScope("b",0,createData(dataType::f32,3.0f));
    BasicSymbol* c=SymbolFactory::createConstSymbol(createData(dataType::f32,1.0f));

    ArithmeticOperationLLVM* bsollvm=LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_fadd,a,b,c);
    std::cout<<bsollvm->out_str()<<"\n";

    //无条件跳转语句测试
    LabelSymbol* label_uncond=SymbolFactory::createLabelSymbol("uncond1");
    UnconditionalBranchLLVM* br_uncond=LLVMfactory::createUnconditionalBranchLLVM(label_uncond);
    label_uncond->setScope(1);
    std::cout<<br_uncond->out_str()<<"\n";

    //条件跳转语句测试
    LabelSymbol* label_true=SymbolFactory::createLabelSymbol("cond_true");
    LabelSymbol* label_false=SymbolFactory::createLabelSymbol("cond_false");
    label_true->setScope(1);
    label_false->setScope(1);
    BasicSymbol* cond=SymbolFactory::createVarSymbol("cond",dataType::i1);
    cond->setScope(0);
    ConditionalBranchLLVM* br_cond=LLVMfactory::createConditionalBranchLLVM(cond,label_true,label_false);
    std::cout<<br_cond->out_str()<<"\n";

    //return语句测试
    ReturnLLVM* returnLLVM=LLVMfactory::createReturnLLVM(a);
    std::cout<<returnLLVM->out_str()<<"\n";

    //phi语句测试
    BasicSymbol* phi_dest=SymbolFactory::createVarSymbol("phi_dest",dataType::f32);
    std::vector<std::pair<BasicSymbol*,LabelSymbol*>> val_src;
    val_src.push_back({a,label_true});
    val_src.push_back({b,label_false});
    phi_dest->setScope(1);
    LLVM* phiLLVM=LLVMfactory::createPhiLLVM(phi_dest,val_src);
    std::cout<<phiLLVM->out_str()<<"\n";

    //call语句测试
    FuncSymbol* func=SymbolFactory::createFuncSymbolWithScope("myfunction",1,dataType::i32);
    std::vector<BasicSymbol*>bs;
    bs.push_back(a);
    bs.push_back(b);
    bs.push_back(c);
    BasicSymbol* func_dest=SymbolFactory::createTmpVarSymbolWithScope(dataType::i32,1);
    LLVM* callLLVM=LLVMfactory::createCallLLVM(func_dest,func,bs);
    std::cout<<callLLVM->out_str()<<"\n";

    //label语句测试
    LabelSymbol* label_test=SymbolFactory::createLabelSymbol("label_test");
    label_test->setScope(1);
    LLVM* labelLLVM=LLVMfactory::createLableLLVM(label_test);
    std::cout<<labelLLVM->out_str()<<"\n";

    //
}