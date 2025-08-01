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
void connectBasicBlocks(const std::vector<BasicBlock*>& bbs){
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
                if(i!=bbs.size()-1)
                    connect(l,bbs[i+1]);
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

//通过基本块开头的label的名称查找对应的基本块
BasicBlock* getBasicBlock(std::string& bb_name,std::vector<BasicBlock*>& bbs){
    for(auto & bb : bbs){
        if(dynamic_cast<Label*>(bb->head)->label->name==bb_name)
            return bb;
    }
    return nullptr;
}

std::vector<BasicBlock*> getCFG(LLVMList* llvmlist){
    std::vector<BasicBlock*> basicBlocks=divideBasicBlock(llvmlist);
    connectBasicBlocks(basicBlocks);
    return basicBlocks;
}

std::vector<std::vector<std::pair<BasicSymbol*,BasicSymbol*>>> getMovVar(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs){
    std::vector<std::vector<std::pair<BasicSymbol*,BasicSymbol*>>> res;
    for(LLVM* llvm=llvmlist->head;llvm!=nullptr;llvm=llvm->next){
        if(llvm->getLLVMType()==LLVMtype::phi){
            PhiLLVM* phiLLVM=dynamic_cast<PhiLLVM*>(llvm);
            std::vector<std::pair<BasicSymbol*,LabelSymbol*>> & val_and_src=phiLLVM->vals_srcs;
            for(auto & a : val_and_src){
                res[getBasicBlock(a.second->name,bbs)->idx].push_back({phiLLVM->dest_sym,a.first});
            }
        }
    }
    return res;
}

void set(std::vector<bool>&a){
    for(int i=0;i<a.size();i++){
        a[i]=true;
    }
}

void set(std::vector<bool>&a,int j){
    a[j]=true;
}

void reset(std::vector<bool>&a){
    for(int i=0;i<a.size();i++){
        a[i]=false;
    }
}

void reset(std::vector<bool>&a,int j){
    a[j]=false;
}

int count_bool(std::vector<bool>&a){
    int cnt=0;
    for(int i=0;i<a.size();i++){
        if(a[i]==true){
            cnt++;
        }
    }
    return cnt;
}

//对于getelementptr这个指令，我们是自己生成一个临时变量来处理，所以不用考虑变量重复赋值的问题
BasicSymbol* getDestSym(LLVM* llvm){
    switch (llvm->getLLVMType())
    {
        case LLVMtype::add:
        case LLVMtype::sub:
        case LLVMtype::mul:
        case LLVMtype::sdiv:
        case LLVMtype::udiv:
        case LLVMtype::icmp_eq:
        case LLVMtype::icmp_ne:
        case LLVMtype::icmp_sge:
        case LLVMtype::icmp_sgt:
        case LLVMtype::icmp_sle:
        case LLVMtype::llvm_fadd:
        case LLVMtype::llvm_fsub:
        case LLVMtype::llvm_fmul:
        case LLVMtype::llvm_fdiv:
        case LLVMtype::llvm_frem:
        case LLVMtype::logical_or:
        case LLVMtype::logical_and:
        case LLVMtype::logical_xor:
        case LLVMtype::srem:
        case LLVMtype::urem:
        case LLVMtype::icmp_slt:
        case LLVMtype::icmp_uge:
        case LLVMtype::icmp_ugt:
        case LLVMtype::icmp_ule:
        case LLVMtype::icmp_ult:
        case LLVMtype::fcmp_oeq:
        case LLVMtype::fcmp_oge:
        case LLVMtype::fcmp_ogt:
        case LLVMtype::fcmp_ole:
        case LLVMtype::fcmp_olt:
        case LLVMtype::fcmp_one:
        case LLVMtype::fcmp_ord:
        {
            ArithmeticOperationLLVM* ir=dynamic_cast<ArithmeticOperationLLVM*>(llvm);
            return ir->a;
        }
        case LLVMtype::llvm_trunc:
        case LLVMtype::zext:
        case LLVMtype::sext:
        case LLVMtype::bitcast:
        case LLVMtype::fptrunc:
        case LLVMtype::fpext:
        case LLVMtype::fptoui:
        case LLVMtype::fptosi:
        case LLVMtype::uitofp:
        case LLVMtype::sitofp:
        case LLVMtype::ptrtoint:
        case LLVMtype::inttoptr:
        //case LLVMtype::addrspacecast:
        {
            TypeConversionOperation* ir=dynamic_cast<TypeConversionOperation*>(llvm);
            return ir->dest_sym;
        }
        case LLVMtype::load:
        {
            LoadLLVM* ir=dynamic_cast<LoadLLVM*>(llvm);
            return ir->dest_sym;
        }
        case LLVMtype::call:
        {
            CallLLVM* ir=dynamic_cast<CallLLVM*>(llvm);
            return ir->dest_sym;
        }
        case LLVMtype::phi:
        {
            PhiLLVM* ir=dynamic_cast<PhiLLVM*>(llvm);
            return ir->dest_sym;
        }
        case LLVMtype::llvm_neg:
        case LLVMtype::llvm_fneg:
        {
            UnaryOperationLLVM* ir=dynamic_cast<UnaryOperationLLVM*>(llvm);
            return ir->dest_sym;
        }
        default:
            return nullptr;
            break;
    }
}