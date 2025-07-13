#include "../include/LLVMFactory.hpp"
#include"../include/SymbolFactory.hpp"

ArithmeticOperationLLVM* LLVMfactory::createBasicOperationLLVM(LLVMtype type,BasicSymbol*a,BasicSymbol*b,BasicSymbol*c){
    ArithmeticOperationLLVM* basicOperationLLVM =new ArithmeticOperationLLVM();
    basicOperationLLVM->setOperand(a,b,c);
    basicOperationLLVM->setLLVMType(type);
    return basicOperationLLVM;
}

ConditionalBranchLLVM* LLVMfactory::createConditionalBranchLLVM(BasicSymbol* cond, LabelSymbol* trueBranch, LabelSymbol* falseBranch){ 
    ConditionalBranchLLVM* conditionalBranchLLVM=new ConditionalBranchLLVM();
    conditionalBranchLLVM->llvmType=LLVMtype::br_conditional; 
    conditionalBranchLLVM->setCondition(cond);
    conditionalBranchLLVM->setFalseBranch(falseBranch);
    conditionalBranchLLVM->setTrueBranch(trueBranch);
    return conditionalBranchLLVM;
}

UnconditionalBranchLLVM* LLVMfactory::createUnconditionalBranchLLVM(LabelSymbol* target){
    UnconditionalBranchLLVM* unconditionalBranchLLVM=new UnconditionalBranchLLVM();
    unconditionalBranchLLVM->llvmType=LLVMtype::br_unconditional;
    unconditionalBranchLLVM->target=target;
    return unconditionalBranchLLVM;
}

ReturnLLVM* LLVMfactory::createReturnLLVM(BasicSymbol* returnValue){
    ReturnLLVM* returnLLVM=new ReturnLLVM();
    returnLLVM->llvmType=LLVMtype::ret;
    returnLLVM->setReturnValue(returnValue);
    return returnLLVM;
}

/*SwitchLLVM* LLVMfactory::createSwitchLLVM(BasicSymbol* cond, LabelSymbol* defaultCase,std::vector<BasicSymbol*>case_val,std::vector<LabelSymbol*>case_dest){
    SwitchLLVM* switchLLVM=new SwitchLLVM();
    switchLLVM->llvmType = LLVMtype::llvm_switch;
    switchLLVM->condition=cond;
    switchLLVM->defaultCase=defaultCase;
    std::vector<std::pair<BasicSymbol*,LabelSymbol*>> case_val_dest;
    for(int i=0;i<case_val.size();i++)
        case_val_dest.push_back({case_val[i],case_dest[i]});
    switchLLVM->case_val_dest=case_val_dest;
    return switchLLVM;
}*/

PhiLLVM* LLVMfactory::createPhiLLVM(BasicSymbol* dest_sym,std::vector<BasicSymbol*>& src_sym,std::vector<LabelSymbol*>&src_label){
    PhiLLVM* phiLLVM=new PhiLLVM();
    phiLLVM->llvmType=LLVMtype::phi;
    phiLLVM->dest_sym=dest_sym;
    phiLLVM->addCase(src_sym,src_label);
    return phiLLVM;
}

PhiLLVM* LLVMfactory::createPhiLLVM(BasicSymbol* dest_sym,std::vector<std::pair<BasicSymbol*,LabelSymbol*>>& val_src){
    PhiLLVM* phiLLVM=new PhiLLVM();
    phiLLVM->llvmType=LLVMtype::phi;
    phiLLVM->dest_sym=dest_sym;
    phiLLVM->vals_srcs=val_src;
    return phiLLVM;
}

Label* LLVMfactory::createLableLLVM(LabelSymbol* label){
    Label* labl=new Label();
    labl->llvmType=LLVMtype::label;
    labl->label=label;
    return labl;
}

CallLLVM* LLVMfactory::createCallLLVM(BasicSymbol*dest_sym,FuncSymbol* func,std::vector<BasicSymbol*>& params){
    CallLLVM* callLLVM=new CallLLVM();
    callLLVM->dest_sym=dest_sym;
    callLLVM->function=func;
    callLLVM->arguments=params;
    callLLVM->llvmType=LLVMtype::call;
    return callLLVM;
}


TypeConversionOperation* LLVMfactory::createTypeConversionOperation(LLVMtype type,BasicSymbol* src_sym,BasicSymbol* dest_sym){
    TypeConversionOperation* typeConversionOperation=new TypeConversionOperation();
    typeConversionOperation->llvmType=type;
    typeConversionOperation->dest_sym=dest_sym;
    typeConversionOperation->src_sym=src_sym;
    return typeConversionOperation;
}

AllocaNonArrayLLVM* LLVMfactory::createAllocaNonArrayLLVM(PointerSymbol* sym){
    AllocaNonArrayLLVM* allocaNonArrayLLVM=new AllocaNonArrayLLVM();
    allocaNonArrayLLVM->sym=sym;
    allocaNonArrayLLVM->llvmType=LLVMtype::allocate_nonarray;
    return allocaNonArrayLLVM;
}

AllocaArrayLLVM* LLVMfactory::createAllocaArrayLLVM(ArraySymbol* sym,dataType type,std::vector<int>&dimensions){
    AllocaArrayLLVM* allocaArrayLLVM=new AllocaArrayLLVM();
    allocaArrayLLVM->array=sym;
    allocaArrayLLVM->llvmType=LLVMtype::allocate_array;
    allocaArrayLLVM->array->allocateMemory(type,dimensions);
    return allocaArrayLLVM;
}

/*
AllocaArrayLLVM* LLVMfactory::createAllocaArrayLLVM(ArraySymbol* sym){
    AllocaArrayLLVM* allocaArrayLLVM=new AllocaArrayLLVM();
    allocaArrayLLVM->array=sym;
    allocaArrayLLVM->llvmType=LLVMtype::allocate_array;
    return allocaArrayLLVM;
}
*/

LoadLLVM* LLVMfactory::createLoadLLVM(PointerSymbol* src_sym,BasicSymbol* dest_sym){
    LoadLLVM* loadLLVM=new LoadLLVM();
    loadLLVM->src_sym=src_sym;
    loadLLVM->dest_sym=dest_sym;
    loadLLVM->llvmType=LLVMtype::load;
    return loadLLVM;
}

StoreLLVM* LLVMfactory::createStoreLLVM(BasicSymbol* src_sym,PointerSymbol* dest_sym){
    StoreLLVM* storeLLVM=new StoreLLVM();
    storeLLVM->src_sym=src_sym;
    storeLLVM->dest_sym=dest_sym;
    storeLLVM->llvmType=LLVMtype::store;
    return storeLLVM;
}

GetElementPtrLLVM* LLVMfactory::createGetElementPtrLLVM(PointerSymbol*dest_sym,ArraySymbol* ptrval,const std::vector<dataType>&type,const std::vector<BasicSymbol*>&idx){
    GetElementPtrLLVM* getElementPtrLLVM=new GetElementPtrLLVM();
    getElementPtrLLVM->ptrval=ptrval;
    getElementPtrLLVM->addTyIdx(type,idx);
    getElementPtrLLVM->llvmType=LLVMtype::getelementptr;
    getElementPtrLLVM->ptrval=ptrval;
    getElementPtrLLVM->dest_sym=dest_sym;
    return getElementPtrLLVM;
}

GetElementPtrLLVM* LLVMfactory::createGetElementPtrLLVM(PointerSymbol*dest_sym,ArraySymbol* ptrval,const std::vector<std::pair<dataType,BasicSymbol*>>&ty_idx){
    GetElementPtrLLVM* getElementPtrLLVM=new GetElementPtrLLVM();
    getElementPtrLLVM->ptrval=ptrval;
    getElementPtrLLVM->ty_idx=ty_idx;
    getElementPtrLLVM->llvmType=LLVMtype::getelementptr;
    getElementPtrLLVM->ptrval=ptrval;
    getElementPtrLLVM->dest_sym=dest_sym;
    return getElementPtrLLVM;
}

GlobalNonArrayVarDefination* LLVMfactory::createGlobalNonArrayVarDefination(PointerSymbol* dest_sym,BasicSymbol* src_sym){
    GlobalNonArrayVarDefination* globalNonArrayVarDefination=new GlobalNonArrayVarDefination();
    globalNonArrayVarDefination->dest_sym=dest_sym;
    globalNonArrayVarDefination->src_sym=src_sym;
    globalNonArrayVarDefination->llvmType=LLVMtype::global_nonarray;
    return globalNonArrayVarDefination;
 }

GlobalNonArrayVarDefination* LLVMfactory::createGlobalNonArrayVarDefination(PointerSymbol* dest_sym,initializer initMode){
    GlobalNonArrayVarDefination* globalNonArrayVarDefination=LLVMfactory::createGlobalNonArrayVarDefination(dest_sym,nullptr);
    globalNonArrayVarDefination->dest_sym->pointedData->setInitMode(initMode);
    if(initMode==initializer::undef)
        globalNonArrayVarDefination->dest_sym->pointedData->setIsInitialize(false);
    else if(initMode==initializer::zeroinitializer){
        //globalNonArrayVarDefination->dest_sym->pointedData->setValue(0);
        globalNonArrayVarDefination->dest_sym->pointedData->setIsInitialize(true);
    }
    return globalNonArrayVarDefination;
}

static CallLLVM* createCallLLVM(FuncSymbol* func,std::vector<BasicSymbol*>& params){
    CallLLVM* callLLVM=new CallLLVM();
    callLLVM->addArguments(params);
    callLLVM->function=func;
    callLLVM->llvmType=LLVMtype::call;
    dataType arg_ty1,arg_ty2;
    for(int i=0;i<callLLVM->arguments.size();i++)
    {
        arg_ty1=callLLVM->arguments[i]->data->getType();
        arg_ty2=func->paramTypes[i];
        if(arg_ty1!=arg_ty2)
            throw std::invalid_argument("function parameters type not match");
    }
    return callLLVM;
}

ConstantNonArrayVarDefination* LLVMfactory::createConstantNonArrayVarDefination(BasicSymbol* dest_sym,BasicSymbol* src_sym){
    ConstantNonArrayVarDefination* constantNonArrayVarDefination=new ConstantNonArrayVarDefination();
    constantNonArrayVarDefination->dest_sym=dest_sym;
    constantNonArrayVarDefination->src_sym=src_sym;
    constantNonArrayVarDefination->llvmType=LLVMtype::const_nonarray;
    constantNonArrayVarDefination->dest_sym->type=symType::constant_var;
    constantNonArrayVarDefination->dest_sym->data->setInitMode(initializer::assignment);
    return constantNonArrayVarDefination;
}

ConstantNonArrayVarDefination* LLVMfactory::createConstantNonArrayVarDefination(BasicSymbol* dest_sym,initializer initMode){
    ConstantNonArrayVarDefination* constantNonArrayVarDefination=new ConstantNonArrayVarDefination();
    constantNonArrayVarDefination->dest_sym=dest_sym;
    constantNonArrayVarDefination->dest_sym->data->setInitMode(initMode);
    constantNonArrayVarDefination->llvmType=LLVMtype::const_nonarray;
    constantNonArrayVarDefination->dest_sym->type=symType::constant_var;
    return constantNonArrayVarDefination;
}

FuncDeclaration* LLVMfactory::createFuncDeclaration(FuncSymbol* func,std::vector<dataType>paramTypes,dataType returnType){
    FuncDeclaration* funcDeclaration=LLVMfactory::createFuncDeclaration(func,paramTypes);
    funcDeclaration->func->returnType=returnType;
    return funcDeclaration;
}

FuncDeclaration* LLVMfactory::createFuncDeclaration(FuncSymbol* func,std::vector<dataType>paramTypes){
    FuncDeclaration* funcDeclaration = new FuncDeclaration();
    funcDeclaration->func=func;
    funcDeclaration->func->paramTypes=paramTypes;
    funcDeclaration->llvmType=LLVMtype::func_decl;
    return funcDeclaration;
}

FuncDeclaration* LLVMfactory::createFuncDeclaration(FuncSymbol* func){
    FuncDeclaration* funcDeclaration = new FuncDeclaration();
    funcDeclaration->func=func;
    funcDeclaration->llvmType=LLVMtype::func_decl;
    return funcDeclaration;
}

FuncDefination* LLVMfactory::createFuncDefination(FuncSymbol* func,std::vector<Symbol*>param){
    FuncDefination* funcDefination = new FuncDefination();
    funcDefination->func=func;
    funcDefination->llvmType=LLVMtype::func_def;
    funcDefination->params=param;
    return funcDefination;
}

FuncDefination* LLVMfactory::createFuncDefination(FuncSymbol* func,std::vector<dataType>paramTypes,dataType returnType,std::vector<Symbol*>param){
    FuncDefination* funcDefination=LLVMfactory::createFuncDefination(func,param);
    funcDefination->func->paramTypes=paramTypes;
    funcDefination->func->returnType=returnType;
    funcDefination->func->isDef=true;
    return funcDefination;
}

FuncDefination* LLVMfactory::createFuncDefination(FuncSymbol* func,std::vector<dataType>paramTypes,std::vector<Symbol*>param){
    FuncDefination* funcDefination=LLVMfactory::createFuncDefination(func,param);
    funcDefination->func->paramTypes=paramTypes;
    funcDefination->func->isDef=true;
    return funcDefination;
}

GlobalArrayVarDefination* LLVMfactory::createGlobalArrayVarDefination(ArraySymbol* dest_sym){
    GlobalArrayVarDefination* globalArrayVarDefination=new GlobalArrayVarDefination();
    globalArrayVarDefination->llvmType=LLVMtype::global_array;
    globalArrayVarDefination->dest_sym=dest_sym;
    return globalArrayVarDefination;
}

GlobalArrayVarDefination* LLVMfactory::createGlobalArrayVarDefination(ArraySymbol* dest_sym,initializer initMode){
    GlobalArrayVarDefination* globalArrayVarDefination=new GlobalArrayVarDefination();
    globalArrayVarDefination->llvmType=LLVMtype::global_array;
    globalArrayVarDefination->dest_sym=dest_sym;
    globalArrayVarDefination->dest_sym->data->setInitMode(initMode);
    return globalArrayVarDefination;
}

ConstantArrayVarDefination* LLVMfactory::createConstantArrayVarDefination(ArraySymbol* dest_sym){
    ConstantArrayVarDefination* constantArrayVarDefination=new ConstantArrayVarDefination();
    constantArrayVarDefination->llvmType=LLVMtype::global_array;
    constantArrayVarDefination->dest_sym=dest_sym;
    return constantArrayVarDefination;
}

ConstantArrayVarDefination* LLVMfactory::createConstantArrayVarDefination(ArraySymbol* dest_sym,initializer initMode){
    ConstantArrayVarDefination* constantArrayVarDefination=new ConstantArrayVarDefination();
    constantArrayVarDefination->llvmType=LLVMtype::global_array;
    constantArrayVarDefination->dest_sym=dest_sym;
    constantArrayVarDefination->dest_sym->data->setInitMode(initMode);
    return constantArrayVarDefination;
}

AllocaArrayLLVM* LLVMfactory::createAllocaArrayLLVM(ArraySymbol* sym){
    AllocaArrayLLVM* allocaArrayLLVM=new AllocaArrayLLVM();
    allocaArrayLLVM->array=sym;
    return allocaArrayLLVM;
}

UnaryOperationLLVM* LLVMfactory::createUnaryOperationLLVM(BasicSymbol* dest_sym,BasicSymbol* src_sym,LLVMtype type){
    UnaryOperationLLVM* unaryOperationLLVM=new UnaryOperationLLVM();
    unaryOperationLLVM->llvmType=type;
    unaryOperationLLVM->dest_sym=dest_sym;
    unaryOperationLLVM->src_sym=src_sym;
    if(dest_sym->getDataType()!=src_sym->getDataType()||(dest_sym->getDataType()==dataType::i32&&type==LLVMtype::llvm_fneg)||(dest_sym->getDataType()==dataType::f32&&type==LLVMtype::llvm_neg)){
        throw std::runtime_error("error occurs when trying to create an UnaryOperationLLVM class");
    }
}