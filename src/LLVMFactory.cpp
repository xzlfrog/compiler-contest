#include "../include/LLVMFactory.hpp"

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
    if(returnValue==nullptr||returnValue->data==nullptr)
        return returnLLVM;
    return returnLLVM;
}

SwitchLLVM* LLVMfactory::createSwitchLLVM(BasicSymbol* cond, LabelSymbol* defaultCase,std::vector<BasicSymbol*>case_val,std::vector<LabelSymbol*>case_dest){
    SwitchLLVM* switchLLVM=new SwitchLLVM();
    switchLLVM->llvmType = LLVMtype::llvm_switch;
    switchLLVM->condition=cond;
    switchLLVM->defaultCase=defaultCase;
    std::vector<std::pair<BasicSymbol*,LabelSymbol*>> case_val_dest;
    for(int i=0;i<case_val.size();i++)
        case_val_dest.push_back({case_val[i],case_dest[i]});
    switchLLVM->case_val_dest=case_val_dest;
    return switchLLVM;
}

PhiLLVM* LLVMfactory::createPhiLLVM(BasicSymbol* dest_sym,std::vector<BasicSymbol*> src_sym,std::vector<LabelSymbol*>src_label){
    PhiLLVM* phiLLVM=new PhiLLVM();
    phiLLVM->llvmType=LLVMtype::phi;
    if(dest_sym->data==nullptr)
        return;
    phiLLVM->dest_sym=dest_sym;
    phiLLVM->addCase(src_sym,src_label);
    return phiLLVM;
}

Label* LLVMfactory::createLableLLVM(LabelSymbol* label){
    Label* labl=new Label();
    labl->llvmType=LLVMtype::label;
    labl->label=label;
    return labl;
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

AllocaArrayLLVM* LLVMfactory::createAllocaArrayLLVM(ArraySymbol* sym){
    AllocaArrayLLVM* allocaArrayLLVM=new AllocaArrayLLVM();
    allocaArrayLLVM->array=sym;
    allocaArrayLLVM->llvmType=LLVMtype::allocate_array;
    return allocaArrayLLVM;
}

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

GetElementPtrLLVM* LLVMfactory::createGetElementPtrLLVM(ArraySymbol* ptrval,std::vector<dataType>type,std::vector<BasicSymbol*>idx){
    GetElementPtrLLVM* getElementPtrLLVM=new GetElementPtrLLVM();
    getElementPtrLLVM->ptrval=ptrval;
    getElementPtrLLVM->addTyIdx(type,idx);
    getElementPtrLLVM->llvmType=LLVMtype::getelementptr;
    return getElementPtrLLVM;
}

