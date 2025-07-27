#include"../include/BasicBlock.hpp"


std::unordered_map<std::string,BasicBlock*> label_to_basicBlock;
int function_num;
//std::unordered_map<std::string,PointerSymbol*>bs_to_ps;

std::string generate_begin_label(){
    return "var.def."+std::to_string(function_num);
}

std::string generate_entry_label(){
    return "entry."+std::to_string(function_num);
}

std::string generate_exit_label(){
    function_num++;
    return "exit.label."+std::to_string(function_num);
}

BasicBlock* BasicBlock::createBasicBlock(LLVM* start,LLVM* end, LLVMList* llvmlist){
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
        llvmlist->InsertBefore(start,label);
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
    for(int i=0;i<bbs.size();i++){
        auto & l= bbs[i];
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
                //if(l->tail->next!=nullptr&&l->tail->next->getLLVMType()!=LLVMtype::label){
                    //throw std::runtime_error("the function do not end with return.");
                //}
                if(l->tail->next!=nullptr)
                    connect(l,label_to_basicBlock[dynamic_cast<Label*>(l->tail->next)->label->name]);
                break;
            }
        }
    }
}

//只划分了基本块，但是没有得到对应的数据流图
std::vector<BasicBlock*> divideBasicBlock(LLVMList* llvmlist){
    label_to_basicBlock.clear();
    FuncDefination* func_llvm=dynamic_cast<FuncDefination*>(llvmlist->head);
    int cnt=0;
    std::vector<BasicBlock*> basicBlocks;
    Label* beginLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbolWithScope(generate_begin_label(),1));
    basicBlocks.push_back(BasicBlock::createBasicBlock(beginLabel,beginLabel,llvmlist)) ;//begin基本块
    basicBlocks[0]->idx=cnt;
    cnt++;
    //llvmlist->InsertHead(beginLabel);

    Label* entryLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbolWithScope(generate_entry_label(),1));
    llvmlist->InsertAfter(llvmlist->head,entryLabel);

    LLVM* start=entryLabel;
    BasicBlock* bb;
    Label* exitLabel=LLVMfactory::createLableLLVM(SymbolFactory::createLabelSymbolWithScope(generate_exit_label(),1));
    llvmlist->InsertAfter(func_llvm->block_tail,exitLabel);
    LLVM* llvm=llvmlist->head->next->next;

    while(llvm!=nullptr&&llvm->prev!=exitLabel){
        if(llvm->getLLVMType()==LLVMtype::load){
            LoadLLVM* loadLLVM=dynamic_cast<LoadLLVM*>(llvm);
            //bs_to_ps[loadLLVM->dest_sym->name]=loadLLVM->src_sym;
        }
        if(llvm->getLLVMType()==LLVMtype::label){
            bb=BasicBlock::createBasicBlock(start,llvm->prev,llvmlist);
            bb->idx=cnt;
            cnt++;
            basicBlocks.push_back(bb);
            start=llvm;
        }
        else if(needDivide(llvm)&&llvm->next!=nullptr&&llvm->next->getLLVMType()!=LLVMtype::label){
            llvmlist->InsertAfter(llvm,LLVMfactory::createLableLLVM(SymbolFactory::createTmpLabelSymbolWithScope(1)));
        }
        llvm=llvm->next;
    }

    llvmlist->Remove(exitLabel);
    exitLabel->prev=llvmlist->tail;
    bb=BasicBlock::createBasicBlock(exitLabel,exitLabel,llvmlist);
    bb->idx=cnt;
    cnt++;
    basicBlocks.push_back(bb);//exit基本块
    Label* label_tmp;
    for(auto &l : basicBlocks){
        label_tmp=dynamic_cast<Label*>(l->head);
        if(label_tmp==nullptr){
            throw std::runtime_error("the label of the basicBlock is nullptr!");
        }
        l->label=label_tmp;
        label_to_basicBlock.insert({label_tmp->label->name,l});
    }
    FuncDefination* head=dynamic_cast<FuncDefination*>(llvmlist->head);
    if(llvmlist->tail!=head->block_tail){
        head->block_tail=llvmlist->tail;
    }
    return basicBlocks;
}