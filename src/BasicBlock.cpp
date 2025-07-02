#include"../include/BasicBlock.hpp"


LLVMList* llvmList;
std::unordered_map<std::string,BasicBlock*> label_to_basicBlock;
int function_num;

std::string generate_begin_label(){
    return "entry.label."+std::to_string(function_num);
}

std::string generate_entry_label(){
    return "entry."+std::to_string(function_num);
}

std::string generate_exit_label(){
    function_num++;
    return "exit.label."+std::to_string(function_num);
}

BasicBlock* BasicBlock::createBasicBlock(LLVM* start,LLVM* end){
    BasicBlock* basicBlock=new BasicBlock();
    if(start==nullptr&&end==nullptr){
        return basicBlock;
    }
    if(start->getLLVMType()==LLVMtype::label){
        basicBlock->head=start;
        LabelSymbol* labelSymbol=dynamic_cast<LabelSymbol*>(start);
    }
    else{
        LabelSymbol* labelSymbol=SymbolFactory::createTmpLabelSymbolWithScope(1);
        Label* label=LLVMfactory::createLableLLVM(labelSymbol);
        llvmList->InsertBefore(start,label);
        basicBlock->head=label;
    }
    basicBlock->tail=end;
    return basicBlock;
}

void BasicBlock::setGen(basicBlockGen func,std::vector<BasicBlock*> head){
    func(this,head);
}

void BasicBlock::setKill(basicBlockKill func,std::vector<BasicBlock*> head){
    func(this,head);
}

bool needDivide(LLVM* llvm){
    if(llvm->getLLVMType()==LLVMtype::ret||llvm->getLLVMType()==LLVMtype::br_conditional
    ||llvm->getLLVMType()==LLVMtype::br_unconditional)
        return true;
    return false;
}

void connect(BasicBlock* bb1,BasicBlock* bb2){
    bb1->nextNode.push_back(bb2);
    bb2->prevNode.push_back(bb1);
}

//得到数据流图
void connectBasicBlocks(const std::vector<BasicBlock*> bbs){
    for(auto& l : bbs){
        switch(l->tail->getLLVMType()){
            case LLVMtype::br_conditional:{
                ConditionalBranchLLVM* br_cond=dynamic_cast<ConditionalBranchLLVM*>(l->tail);
                connect(l,label_to_basicBlock[br_cond->getTrueBranch()->name]);
                connect(l,label_to_basicBlock[br_cond->getFalseBranch()->name]);
                break;
            }
            case  LLVMtype::br_unconditional:{
                UnconditionalBranchLLVM* br_uncond=dynamic_cast<UnconditionalBranchLLVM*>(l->tail);
                connect(l,label_to_basicBlock[br_uncond->getTarget()->name]);
                break;
            }
            case LLVMtype::label:{
                if(l==bbs[0])
                    connect(l,bbs[1]);
                break;
            }
            case LLVMtype::ret:{
                connect(l,bbs[bbs.size()-1]);
                break;
            }
            default:{
                throw std::runtime_error("basic block dividing is wrong");
            }
        }
    }
}

//只划分了基本块，但是没有得到对应的数据流图
std::vector<BasicBlock*> divideBasicBlock(LLVMList* llvmlist){
    int cnt=0;
    llvmlist->InsertHead(LLVMfactory::createLableLLVM(SymbolFactory::createTmpLabelSymbolWithScope(1)));
    std::vector<BasicBlock*> basicBlocks;
    Label* beginLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbolWithScope(generate_begin_label(),1));
    basicBlocks.push_back(BasicBlock::createBasicBlock(beginLabel,beginLabel)) ;//begin基本块
    basicBlocks[0]->idx=cnt;
    cnt++;

    Label* entryLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbolWithScope(generate_entry_label(),1));
    llvmlist->InsertHead(entryLabel);

    LLVM* start=entryLabel;
    LLVM* llvm=llvmlist->head->next;
    BasicBlock* bb;
    Label* exitLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbolWithScope(generate_exit_label(),1));
    llvmlist->InsertTail(exitLabel);

    while(llvm!=nullptr){
        if(llvm->getLLVMType()==LLVMtype::label){
            BasicBlock* bb;
            if(llvm->prev)
                bb=BasicBlock::createBasicBlock(start,llvm->prev);
            else
                bb=BasicBlock::createBasicBlock(start,start);
            bb->idx=cnt;
            cnt++;
            basicBlocks.push_back(bb);
            start=llvm;
            }
        else if(needDivide(llvm)&&(llvm->next==nullptr||llvm->next->getLLVMType()!=LLVMtype::label)){
            llvmlist->InsertAfter(llvm,LLVMfactory::createLableLLVM(SymbolFactory::createTmpLabelSymbolWithScope(1)));
        }
        llvm=llvm->next;
    }

    llvmlist->Remove(exitLabel);
    exitLabel->prev=llvmlist->tail;
    bb=BasicBlock::createBasicBlock(exitLabel,exitLabel);
    bb->idx=cnt;
    cnt++;
    basicBlocks.push_back(bb);//exit基本块
    Label* label_tmp;
    for(auto l : basicBlocks){
        label_tmp=dynamic_cast<Label*>(l->head);
        label_to_basicBlock.insert({label_tmp->label->name,l});
    }
    return basicBlocks;
}