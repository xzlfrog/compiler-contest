#include"../include/BasicOperations.hpp"
#include"../include/LLVMFactory.hpp"
#include"../include/data.hpp"
#include<iostream>

int main(){
    //算术指令/逻辑运算指令/比较运算指令测试
    BasicSymbol* a=SymbolFactory::createVarSymbol("a",dataType::f32);
    a->setScope(1);
    BasicSymbol* b=SymbolFactory::createConstVarSymbolWithScope("b",1,createData(dataType::f32,3.0f));
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
    cond->setScope(1);
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
    BasicSymbol* func_dest=SymbolFactory::createTmpVarSymbolWithScope(dataType::i32,0);
    LLVM* callLLVM=LLVMfactory::createCallLLVM(func_dest,func,bs);
    std::cout<<callLLVM->out_str()<<"\n";

    //label语句测试
    LabelSymbol* label_test=SymbolFactory::createLabelSymbol("label_test");
    label_test->setScope(1);
    LLVM* labelLLVM=LLVMfactory::createLableLLVM(label_test);
    std::cout<<labelLLVM->out_str()<<"\n";

    //AllocaArrayLLVM语句测试
    PointerSymbol* allca_sym=SymbolFactory::createPointerSymbolWithScope("pointer_nonarray",1,dataType::i32);
    LLVM* allocaNonarrayLLVM=LLVMfactory::createAllocaNonArrayLLVM(allca_sym);
    std::cout<<allocaNonarrayLLVM->out_str()<<"\n";

    std::vector<int> dim;
    dim.push_back(3);
    dim.push_back(4);
    dim.push_back(5);
    ArraySymbol* local_array=SymbolFactory::createArraySymbolWithScope("pointer_array",dim,1,dataType::i32);
    LLVM* allocaArrayLLVM=LLVMfactory::createAllocaArrayLLVM(local_array);
    std::cout<<allocaArrayLLVM->out_str()<<"\n";

    //LoadLLVM语句测试
    PointerSymbol* load_src=SymbolFactory::createPointerSymbolWithScope("load_src",1,dataType::i32);
    BasicSymbol* load_dest=SymbolFactory::createVarSymbolWithScope("load_dest",dataType::i32,1);
    LLVM* loadLLVM=LLVMfactory::createLoadLLVM(load_src,load_dest);
    std::cout<<loadLLVM->out_str()<<"\n";

    //StoreLLVM语句测试
    PointerSymbol* store_dest=SymbolFactory::createPointerSymbolWithScope("store_dest",1,dataType::i32);
    BasicSymbol* store_src=SymbolFactory::createVarSymbolWithScope("store_src",dataType::i32,1);
    LLVM* storeLLVM=LLVMfactory::createStoreLLVM(store_src,store_dest);
    std::cout<<storeLLVM->out_str()<<"\n";

    //GetElementPtrLLVM语句测试
    PointerSymbol* getelementptr_dest=SymbolFactory::createPointerSymbolWithScope("getelementptr_dest",1,dataType::i32);
    std::vector<std::pair<dataType,BasicSymbol*>> ty_idx;
    ty_idx.push_back({dataType::i32,SymbolFactory::createConstSymbol(createData(dataType::i32,1))});
    ty_idx.push_back({dataType::i32,SymbolFactory::createConstSymbol(createData(dataType::i32,2))});
    ty_idx.push_back({dataType::i32,SymbolFactory::createConstSymbol(createData(dataType::i32,3))});
    LLVM* getelementptr=LLVMfactory::createGetElementPtrLLVM(getelementptr_dest,local_array,ty_idx);
    std::cout<<getelementptr->out_str()<<"\n";

    //GlobalNonArrayVarDefination
    PointerSymbol* global_dest_nonarray=SymbolFactory::createPointerSymbolWithScope("global_dest_nonarray",0,dataType::f32);
    BasicSymbol * global_src_nonarray=SymbolFactory::createConstSymbol(createData(dataType::f32,3.0f));
    LLVM* globalnonarraydef=LLVMfactory::createGlobalNonArrayVarDefination(global_dest_nonarray,global_src_nonarray);
    std::cout<<globalnonarraydef->out_str()<<"\n";
    globalnonarraydef=LLVMfactory::createGlobalNonArrayVarDefination(global_dest_nonarray,initializer::zeroinitializer);
    std::cout<<globalnonarraydef->out_str()<<"\n";


    //ConstantNonArrayVarDefination
    ConstVarSymbol* const_dest_nonarray=SymbolFactory::createConstVarSymbolWithScope("const_dest_nonarray",0,createNonInitialedData(dataType::f32));
    BasicSymbol * const_src_nonarray=SymbolFactory::createConstSymbol(createData(dataType::f32,2.0f));
    LLVM* constnonarraydef=LLVMfactory::createConstantNonArrayVarDefination(const_dest_nonarray,const_src_nonarray);
    std::cout<<constnonarraydef->out_str()<<"\n";

    //FuncDeclaration
    std::vector<dataType> param;
    param.push_back(dataType::i32);
    param.push_back(dataType::f32);
    param.push_back(dataType::i1);
    FuncSymbol* func_decl=SymbolFactory::createFuncSymbolWithScope("func_decl",param,0,dataType::void_);
    FuncDeclaration* funcdeclllvm=LLVMfactory::createFuncDeclaration(func_decl);
    std::cout<<funcdeclllvm->out_str()<<"\n";

    //FuncDefination
    std::vector<BasicSymbol*>func_param;
    func_param.push_back(SymbolFactory::createVarSymbolWithScope("func_param1",dataType::i32,1));
    func_param.push_back(SymbolFactory::createVarSymbolWithScope("func_param2",dataType::f32,1));
    func_param.push_back(SymbolFactory::createVarSymbolWithScope("func_param3",dataType::i1,1));
    FuncDefination* funcdefllvm=LLVMfactory::createFuncDefination(func_decl,func_param);
    std::cout<<funcdefllvm->out_str()<<"\n";

    //GlobalArrayVarDefination
    ArraySymbol* global_array=SymbolFactory::createArraySymbolWithScope("global_array",dim,0,dataType::f32);
    ArrayInitial* arrayInitial=new ArrayInitial();
    std::vector<int>pos1={1,2,1};
    arrayInitial->initialize(pos1,createData(dataType::f32,2.0f));
    std::vector<int>pos2={2,2,1};
    arrayInitial->initialize(pos2,createData(dataType::f32,3.0f));
    std::vector<int>pos3={2,2,2};
    arrayInitial->initialize(pos3,createData(dataType::f32,5.0f));
    global_array->setInitialedData(arrayInitial);
    GlobalArrayVarDefination* globalArray=LLVMfactory::createGlobalArrayVarDefination(global_array);
    std::cout<<globalArray->out_str()<<"\n";

    //ConstantArrayVarDefination
    ArraySymbol* constant_array=SymbolFactory::createArraySymbolWithScope("global_array",dim,0,dataType::i32);
    ArrayInitial* arrayInitial2=new ArrayInitial();
    std::vector<int>pos4={0,0,1};
    arrayInitial2->initialize(pos4,createData(dataType::i32,1));
    std::vector<int>pos5={0,0,0};
    arrayInitial2->initialize(pos5,createData(dataType::i32,2));
    std::vector<int>pos6={1,1,2};
    arrayInitial2->initialize(pos6,createData(dataType::i32,3));
    constant_array->setInitialedData(arrayInitial2);
    ConstantArrayVarDefination* constArray=LLVMfactory::createConstantArrayVarDefination(constant_array);
    std::cout<<constArray->out_str()<<"\n";

    //
}