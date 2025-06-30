#include"../include/BasicBlock.hpp"
#include"SymbolFactory.hpp"
#include"../include/LLVMFactory.hpp"


LLVMList* llvmList;
std::unordered_map<std::string,BasicBlock*> label_to_basicBlock;
int function_num;

std::string generate_begin_label(){
    return "entry.label."+std::to_string(function_num);
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
        LabelSymbol* labelSymbol=SymbolFactory::createTmpLabelSymbol();
        Label* label=LLVMfactory::createLableLLVM(labelSymbol);
        llvmList->InsertBefore(start,label);
        basicBlock->head=label;
    }
    basicBlock->tail=end;
    return basicBlock;
}

void BasicBlock::setGen(basicBlockGen func,MyList<BasicBlock> head){
    func(this,head);
}

void BasicBlock::setKill(basicBlockKill func,MyList<BasicBlock> head){
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
void connectBasicBlocks(const MyList<BasicBlock> bbs){
    for(auto l=bbs.head;l!=nullptr;l=l->next){
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
                if(l==bbs.head)
                    connect(l,l->next);
                break;
            }
            case LLVMtype::ret:{
                connect(l,bbs.tail);
                break;
            }
            default:{
                throw std::runtime_error("basic block dividing is wrong");
            }
            l->label==dynamic_cast<Label*>(l->head);
            if(l->label==nullptr){
                throw std::runtime_error("the basic block is not start with a label");
            }
        }
    }
}

//只划分了基本块，但是没有得到对应的数据流图
std::vector<BasicBlock*> divideBasicBlock(LLVMList* llvmlist){
    int cnt=1;
    llvmlist->InsertHead(LLVMfactory::createLableLLVM(SymbolFactory::createTmpLabelSymbol()));
    LLVM* llvm=llvmlist->head;
    std::vector<BasicBlock*> basicBlocks;
    Label* beginLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbol(generate_begin_label()));
    beginLabel->next=llvmlist->head;
    basicBlocks.push_back(BasicBlock::createBasicBlock(beginLabel,beginLabel)) ;//begin基本块
    basicBlocks[0]->idx=0;
    LLVM* start=nullptr;
    bool flag=false;
    BasicBlock* bb;
    while(llvm!=nullptr){
        if(llvm->getLLVMType()==LLVMtype::label){
            if(!flag)
                start=llvm,flag=true;
            else{
                BasicBlock* bb=BasicBlock::createBasicBlock(start,llvm);
                bb->idx=cnt;
                cnt++;
                basicBlocks.push_back(bb);
                start=llvm->next;
                flag=false;
            }
        }
        else if(needDivide(llvm)&&(llvm->next->getLLVMType()!=LLVMtype::label||llvm->next==nullptr)){
            llvmlist->InsertAfter(llvm,LLVMfactory::createLableLLVM(SymbolFactory::createTmpLabelSymbol()));
        }
        llvm=llvm->next;
    }
    Label* exitLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbol(generate_exit_label()));
    exitLabel->prev=llvmlist->tail;
    bb=BasicBlock::createBasicBlock(exitLabel,exitLabel);
    bb->idx=cnt;
    cnt++;
    basicBlocks.push_back(bb);//exit基本块
    for(auto l : basicBlocks){
        label_to_basicBlock.insert({l->label->label->name,l});
    }
    return basicBlocks;
}