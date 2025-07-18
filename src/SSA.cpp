#include"../include/SSA.hpp"
#include<boost/dynamic_bitset.hpp>
#include"../include/LLVMFactory.hpp"
#include"../include/SymbolFactory.hpp"
#include<set>
#include<stack>
#include<iostream>

std::unordered_map<std::string,int>count;//记录每个变量的初始化次数
std::unordered_map<std::string,std::stack<int,std::vector<int>>>st;//记录每一个变量的版本号的栈
std::vector<std::vector<int>>idom_reverse;
extern std::unordered_map<std::string,PointerSymbol*>bs_to_ps;

void join_or(boost::dynamic_bitset<>&a,boost::dynamic_bitset<>&b){
    a=a|b;
}

void meet_and(boost::dynamic_bitset<>&a,boost::dynamic_bitset<>&b){
    a=a&b;
}

void initial_ssa(std::vector<BasicBlock*>&bbs){
    int n=bbs.size();
    int i=0;
    BasicBlock* bb;
    //第0个为entry
    for(int i=0;i<n;i++){
        bb=bbs[i];
        bb->in.resize(n);
        bb->out.resize(n);
        //初始时out均为1
        //must分析
        if(i!=0){
            bb->out.set();//全部赋值为1
            bb->in.set();
        }
        else{
            bb->out.reset();
            bb->out.set(0);
            bb->in.reset();
        }
        bb->gen.resize(n);
        bb->kill.resize(n);
        //对于ssa，gen为只有自己的对应位为1,其余位为0
        bb->gen.reset();
        bb->gen.set(i);
    }
}

void getDom(std::vector<BasicBlock*>&bbs){
    bool flag=false;
    int n=bbs.size();
    boost::dynamic_bitset<>old(n);
    initial_ssa(bbs);
    do{
        flag=false;
        for(int i=1;i<n;i++){
            old=bbs[i]->out;
            bbs[i]->in.set();
            if(bbs[i]->prevNode.empty()){
                bbs[i]->in.reset();
            }
            for(auto bb:bbs[i]->prevNode){
                meet_and(bbs[i]->in,bb->out);
            }
            bbs[i]->out=bbs[i]->gen;
            join_or(bbs[i]->out,bbs[i]->in);
            if(bbs[i]->out!=old){
                flag=true;
            }
        }
    }while(flag);
    std::cout<<"getDom is done\n";
}

std::vector<int> getIdom(std::vector<BasicBlock*>&bbs){
    int n=bbs.size();
    boost::dynamic_bitset<> tmp(n);
    std::vector<int> ret;
    ret.push_back(0);//第一个是没有意义的，只是为了和bbs的序号对应，如果真要看的话，可以当作是entry节点的直接支配点，也是它自己
    int max;
    for(int i=1;i<n;i++){
        max=-1;
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            tmp.reset();
            tmp.set(j);
            tmp&=bbs[i]->out;
            if(tmp.count()==1){
                if(max==-1||bbs[max]->out.count()<bbs[j]->out.count())
                    max=j;
            }
        }
        ret.push_back(max);
    }
    for(int i=0;i<n;i++)
    {
        int runner=ret[i];
        while(runner>0){
            runner=ret[runner];
        }
        if(runner==-1)
            ret[i]=-1;
    }
    std::cout<<"getIdom is done!\n";
    return ret;
}

std::vector<std::vector<int>> getDF(std::vector<BasicBlock*>&bbs,std::vector<int>idom){
    int n=bbs.size();
    std::vector<std::vector<int>>df=std::vector<std::vector<int>>(n,std::vector<int>(0));
    int runner;
    for(int i=1;i<n;i++){
        if(idom[i]!=-1&&bbs[i]->prevNode.size()>=2){
            for(auto& p : bbs[i]->prevNode){
                runner=p->idx;
                while(runner!=idom[i]){
                    df[runner].push_back(i);
                    runner=idom[runner];
                }
            }
        }
    }
    std::cout<<"getDF is done"<<"\n";
    return df;
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

std::vector<Symbol*> getSrcSym(LLVM* llvm){
    std::vector<Symbol*> ret;
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
            ret.push_back(ir->b);
            ret.push_back(ir->c);
            return ret;
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
            ret.push_back(ir->getSrcSymbol());
            return ret;
        }
        case LLVMtype::store:
        {
            StoreLLVM* ir=dynamic_cast<StoreLLVM*>(llvm);
            ret.push_back(ir->getSrcSymbol());
            return ret;
        }
        case LLVMtype::ret:
        {
            ReturnLLVM* ir=dynamic_cast<ReturnLLVM*>(llvm);
            ret.push_back(ir->getReturnValue());
            return ret;
        }
        case LLVMtype::call:
        {
            CallLLVM* ir=dynamic_cast<CallLLVM*>(llvm);
            for(auto & a : ir->getArguments()){
                if(a->getType()!=symType::constant_nonvar&&a->getType()!=symType::array){
                    ret.push_back(a);
                }
            }
            return ret;
        }
        case LLVMtype::phi:
        {
            PhiLLVM* ir=dynamic_cast<PhiLLVM*>(llvm);
            for(auto &a : ir->getValAndSrc()){
                ret.push_back(a.first);
            }
            return ret;
        }
        case LLVMtype::llvm_neg:
        case LLVMtype::llvm_fneg:
        {
            UnaryOperationLLVM* ir=dynamic_cast<UnaryOperationLLVM*>(llvm);
            ret.push_back(ir->src_sym);
            return ret;
        }
        case LLVMtype::br_conditional:
        {
            ConditionalBranchLLVM* ir=dynamic_cast<ConditionalBranchLLVM*>(llvm);
            ret.push_back(ir->condition);
            return ret;
        }
        case LLVMtype::func_def:
        {
            FuncDefination* ir=dynamic_cast<FuncDefination*>(llvm);
            for(auto & a : ir->params){
                ret.push_back(a);
            }
            return ret;
        }
        default:
            return std::vector<Symbol*>(0);
            break;
    }
}

//将所有变量的对应的所有基本块放到w中,键为变量的名称，值为变量所在的基本块
void initial_phi_w(std::vector<BasicBlock*>&bbs,std::unordered_map<std::string,std::pair<BasicSymbol*,std::vector<BasicBlock*>>>&w){
    BasicSymbol* sym=nullptr;
    for(auto& bb : bbs){
        std::set<std::string> s;
        for(LLVM*llvm=bb->head;llvm!=nullptr&&llvm->prev!=bb->tail;llvm=llvm->next){
            sym=getDestSym(llvm);
            if(sym!=nullptr){
                if(s.find(sym->name)!=s.end())
                    continue;
                w[sym->name].first=sym;
                w[sym->name].second.push_back(bb);
                s.insert(sym->name);
            }
        }
    }
}

void insertPhi(std::vector<BasicBlock*>&bbs,std::vector<std::vector<int>>&df){
    std::unordered_map<std::string,std::pair<BasicSymbol*,std::vector<BasicBlock*>>>w;
    initial_phi_w(bbs,w);
    int n;
    std::vector<std::set<std::string>>node_phi=std::vector<std::set<std::string>>(bbs.size());

    std::vector<BasicSymbol*> vals;
    std::vector<LabelSymbol*> srcs;

    for(auto& a:w){
        std::vector<BasicBlock*>bbs1=a.second.second;
        BasicSymbol* sym=a.second.first;
        int i=0;
        int sz=bbs1.size();
        std::set<BasicBlock*>s1;
        for(int j=0;j<sz;j++){
            s1.insert(bbs1[j]);
        }
        while(i<bbs1.size()){
            n=bbs1[i]->idx;
            for(auto& dfn : df[n]){
                if(node_phi[dfn].find(a.first)==node_phi[dfn].end()){
                    BasicSymbol* basicSymbol=a.second.first;
                    vals=std::vector<BasicSymbol*>(0);
                    srcs=std::vector<LabelSymbol*>(0);
                    PhiLLVM* phiLLVM=LLVMfactory::createPhiLLVM(basicSymbol,vals,srcs);
                    StoreLLVM* storeLLVM=nullptr;
                    if(bs_to_ps.find(a.second.first->name)!=bs_to_ps.end())
                        storeLLVM=LLVMfactory::createStoreLLVM(a.second.first,bs_to_ps[a.second.first->name]);
                    if(storeLLVM!=nullptr){
                        phiLLVM->next=storeLLVM;
                        storeLLVM->prev=phiLLVM;
                        storeLLVM->next=bbs[dfn]->head->next;
                        if(bbs[dfn]->head->next==nullptr)
                            bbs[dfn]->tail=storeLLVM;
                        else
                            bbs[dfn]->head->next->prev=storeLLVM;
                    }
                    else{
                        phiLLVM->next=bbs[dfn]->head->next;
                        if(bbs[dfn]->head->next==nullptr)
                            bbs[dfn]->tail=phiLLVM;
                        else
                            bbs[dfn]->head->next->prev=phiLLVM;
                    }
                    bbs[dfn]->head->next=phiLLVM;
                    phiLLVM->prev=bbs[dfn]->head;
                    for(int j=0;j<bbs[dfn]->prevNode.size();j++){
                        phiLLVM->addCase(a.second.first,bbs[dfn]->prevNode[j]->label->label);
                    }
                    node_phi[dfn].insert(a.first);
                    //todo.make it faster?use set?
                    bool flag=true;
                    if(s1.find(bbs[dfn])!=s1.end())
                        flag=false;
                    if(flag){
                        bbs1.push_back(bbs[dfn]);
                        s1.insert(bbs[dfn]);
                    }
                }
            }
            i++;
        }
    }
    std::cout<<"insert Phi is done"<<"\n";
}

void rename(std::vector<BasicBlock*>&bbs,int idx){
    BasicBlock* bb=bbs[idx];
    std::vector<std::string>defs;

    //给phi指令的目的操作数改名
    for(LLVM* llvm=bb->head;llvm!=nullptr&&llvm->prev!=bb->tail;llvm=llvm->next){
        if(llvm->getLLVMType()==LLVMtype::phi){
            BasicSymbol* basicSymbol=getDestSym(llvm);
            count[basicSymbol->name]++;
            st[basicSymbol->name].push(count[basicSymbol->name]);
            basicSymbol->ssa_name=basicSymbol->name+"."+std::to_string(count[basicSymbol->name]);
            defs.push_back(basicSymbol->name);
        }
    }

    //重命名当前块内的除了phi指令以外的变量
    for(LLVM* llvm=bb->head;llvm!=nullptr&&llvm->prev!=bb->tail;llvm=llvm->next){
        if(llvm->getLLVMType()!=LLVMtype::phi){
            //先修改表达式右值
            std::vector<Symbol*> bs=getSrcSym(llvm);
            for(auto& b : bs){
                if(b!=nullptr&&b->getType()==symType::variable){
                    if(st[b->name].empty())
                        throw std::runtime_error("the name is not in the unordered map");
                    if(b->getType()!=symType::array){
                        BasicSymbol* src_bs=dynamic_cast<BasicSymbol*>(b);
                        src_bs->ssa_name=src_bs->name+"."+std::to_string(st[src_bs->name].top());
                    }
                }
            }
            //再先修改表达式左值
            BasicSymbol* basicSymbol=getDestSym(llvm);
            if(basicSymbol==nullptr)
                continue;
            count[basicSymbol->name]++;
            st[basicSymbol->name].push(count[basicSymbol->name]);
            basicSymbol->ssa_name=basicSymbol->name+"."+std::to_string(count[basicSymbol->name]);
            defs.push_back(basicSymbol->name);
        }
    }

    //修改后继节点的phi指令的右值
    for(auto nxt_bb : bb->nextNode){
        for(LLVM* llvm=nxt_bb->head;llvm!=nullptr&&llvm->prev!=nxt_bb->tail;llvm=llvm->next){
            if(llvm->getLLVMType()==LLVMtype::phi){
                PhiLLVM* phiLLVM=dynamic_cast<PhiLLVM*>(llvm);
                std::vector<std::pair<BasicSymbol*,LabelSymbol*>> srcAndLabel=phiLLVM->getValAndSrc();
                for(auto &p : srcAndLabel){
                    if(p.second->name==bb->label->label->name){
                        p.first->ssa_name=p.first->name+"."+std::to_string(st[p.first->name].top());
                    }
                }
            }
        }
    }

    //修改被当前基本块支配的基本块的变量名称
    for(int nxt : idom_reverse[bb->idx]){
        if(nxt==idx)
            continue;
        rename(bbs,nxt);
    }

    //该基本块中新创建的变量需要出栈
    for(auto &a:defs){
        if(!st[a].empty())
            st[a].pop();
    }
}

void dead_code_eliminate(std::vector<BasicBlock*>& bbs,LLVMList* llvmlist,std::vector<int>&idom){
    for(int i=0;i<bbs.size();i++){
        if(idom[i]==-1){
            LLVM* next_llvm;
            for(LLVM*llvm=bbs[i]->head;llvm!=bbs[i]->tail;llvm=next_llvm){
                next_llvm=llvm->next;
                llvmlist->Remove(llvm);
            }
            if(bbs[i]->head!=bbs[i]->tail)
                llvmlist->Remove(bbs[i]->tail);
        }
    }
}

void SSA(LLVMList* llvmlist){
    count.clear();
    st.clear();
    bs_to_ps.clear();
    int count_sz=count.size();
    int st_sz=st.size();
    std::vector<Symbol*>params=getSrcSym(llvmlist->head);
    for(auto & a : params){
        if(a->getType()!=symType::array){
            BasicSymbol* func_param_bs=dynamic_cast<BasicSymbol*>(a);
            func_param_bs->ssa_name=func_param_bs->ssa_name+".0";
        }
    }
    std::vector<BasicBlock*>bbs=divideBasicBlock(llvmlist);
    connectBasicBlocks(bbs);
    initial_ssa(bbs);
    getDom(bbs);
    std::vector<int>idom=getIdom(bbs);
    std::vector<std::vector<int>> df=getDF(bbs,idom);
    insertPhi(bbs,df);
    idom_reverse=std::vector<std::vector<int>>(idom.size(),std::vector<int>(0));

    //idom是支配树的反向边，这里需要得到正向边来dfs
    for(int i=0;i<idom.size();i++){
        if(idom[i]!=-1)
            idom_reverse[idom[i]].push_back(i);
    }
    
    //初始化count和st
    for(auto& bb : bbs){
        for(LLVM* llvm=bb->head;llvm!=nullptr&&llvm->prev!=bb->tail;llvm=llvm->next){
            BasicSymbol* basicSymbol=getDestSym(llvm);
            std::vector<Symbol*> symbol_vector=getSrcSym(llvm);
            for(auto & a : symbol_vector){
                if(a==nullptr||a->getType()==symType::constant_var||a->getType()==symType::constant_nonvar)
                    continue;
                count[a->name]=0;
                if(st[a->name].empty())
                    st[a->name].push(0);
            }
            if(basicSymbol==nullptr)
                continue;
            count[basicSymbol->name]=0;
            if(st[basicSymbol->name].empty())
                st[basicSymbol->name].push(0);
        }
    }
    rename(bbs,0);
    //dead_code_eliminate(bbs,llvmlist,idom);
    std::cout<<"ssa is done!"<<"\n";
}