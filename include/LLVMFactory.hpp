#pragma once

#include"BasicOperations.hpp"
#include"ControlOperations.hpp"
#include"GlobalOperations.hpp"
#include"LocalMemoryOperations.hpp"
#include"TypeConversionOperations.hpp"

//LLVMfactory类中包含了一系列静态方法，这些静态方法用于得到我们需要的llvm类
class LLVMfactory{
public:
    static ArithmeticOperationLLVM* createBasicOperationLLVM(LLVMtype type,BasicSymbol*a,BasicSymbol*b,BasicSymbol*c);
    static ConditionalBranchLLVM* createConditionalBranchLLVM(BasicSymbol* cond, LabelSymbol* trueBranch, LabelSymbol* falseBranch);
    static UnconditionalBranchLLVM* createUnconditionalBranchLLVM(LabelSymbol* target);
    static ReturnLLVM* createReturnLLVM(BasicSymbol* returnValue);
    static CallLLVM* createCallLLVM(FuncSymbol* func,std::vector<BasicSymbol*>& params);
    static SwitchLLVM* createSwitchLLVM(BasicSymbol* cond, LabelSymbol* defaultCase,std::vector<BasicSymbol*>case_val,std::vector<LabelSymbol*>case_dest);
    static PhiLLVM* createPhiLLVM(BasicSymbol* dest_sym,std::vector<BasicSymbol*> src_sym,std::vector<LabelSymbol*>src_label);
    static Label* createLableLLVM(LabelSymbol* label);
    static TypeConversionOperation* createTypeConversionOperation(LLVMtype type,BasicSymbol* src_sym,BasicSymbol* dest_sym);
    static AllocaNonArrayLLVM* createAllocaNonArrayLLVM(PointerSymbol* sym);
    static AllocaArrayLLVM* createAllocaArrayLLVM(ArraySymbol* sym,dataType type,std::vector<int>&dimensions);
    static AllocaArrayLLVM* createAllocaArrayLLVM(ArraySymbol* sym);
    static LoadLLVM* createLoadLLVM(PointerSymbol* src_sym,BasicSymbol* dest_sym);
    static StoreLLVM* createStoreLLVM(BasicSymbol* src_sym,PointerSymbol* dest_sym);
    static GetElementPtrLLVM* createGetElementPtrLLVM(BasicSymbol*dest_sym,ArraySymbol* ptrval,std::vector<dataType>type,std::vector<BasicSymbol*>idx);
    static GlobalNonArrayVarDefination* createGlobalNonArrayVarDefination(PointerSymbol* dest_sym,BasicSymbol* src_sym);
    static GlobalNonArrayVarDefination* createGlobalNonArrayVarDefination(PointerSymbol* dest_sym,initializer initMode);
    static ConstantNonArrayVarDefination* createConstantNonArrayVarDefination(BasicSymbol* dest_sym,BasicSymbol* src_sym);
    static ConstantNonArrayVarDefination* createConstantNonArrayVarDefination(BasicSymbol* dest_sym,initializer initMode);
    static FuncDeclaration* createFuncDeclaration(FuncSymbol* func,std::vector<dataType>paramTypes,dataType returnType);
    static FuncDeclaration* createFuncDeclaration(FuncSymbol* func,std::vector<dataType>paramTypes);
    static FuncDeclaration* createFuncDeclaration(FuncSymbol* func);
    static FuncDefination* createFuncDefination(FuncSymbol* func,std::vector<BasicSymbol*>param);
    static FuncDefination* createFuncDefination(FuncSymbol* func,std::vector<dataType>paramTypes,dataType returnType,std::vector<BasicSymbol*>param);
    static FuncDefination* createFuncDefination(FuncSymbol* func,std::vector<dataType>paramTypes,std::vector<BasicSymbol*>param);
};
