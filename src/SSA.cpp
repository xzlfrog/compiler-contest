#include"../include/SSA.hpp"
#include<boost/dynamic_bitset.hpp>
#include"../include/LLVMFactory.hpp"
#include"../include/SymbolFactory.hpp"
#include<set>
#include<stack>

std::unordered_map<std::string,int>count;//记录每个变量的初始化次数
std::unordered_map<std::string,std::stack<int,std::vector<int>>>st;//记录每一个变量的版本号的栈
std::vector<std::vector<int>>idom_reverse;

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
}

std::vector<int> getIdom(std::vector<BasicBlock*>&bbs){
    int n=bbs.size();
    boost::dynamic_bitset<> tmp(n);
    std::vector<int> ret;
    ret.push_back(0);//第一个是没有意义的，只是为了和bbs的序号对应，如果真要看的话，可以当作是entry节点的直接支配点，也是它自己
    int max=-1;
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
    return ret;
}

std::vector<std::vector<int>> getDF(std::vector<BasicBlock*>&bbs,std::vector<int>idom){
    int n=bbs.size();
    std::vector<std::vector<int>>df=std::vector<std::vector<int>>(n,std::vector<int>(0));
    int runner;
    for(int i=1;i<n;i++){
        if(bbs[i]->prevNode.size()>=2){
            for(auto& p : bbs[i]->prevNode){
                runner=p->idx;
                while(runner!=idom[i]){
                    df[runner].push_back(i);
                    runner=idom[runner];
                }
            }
        }
    }
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
        default:
            return nullptr;
            break;
    }
}

std::vector<BasicSymbol*> getSrcSym(LLVM* llvm){
    std::vector<BasicSymbol*> ret;
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
       // case LLVMtype::addrspacecast:
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
        case LLVMtype::call:
        {
            CallLLVM* ir=dynamic_cast<CallLLVM*>(llvm);
            return ir->getArguments();
        }
        case LLVMtype::phi:
        {
            PhiLLVM* ir=dynamic_cast<PhiLLVM*>(llvm);
            for(auto &a : ir->getValAndSrc()){
                ret.push_back(a.first);
            }
            return ret;
        }
        default:
            return std::vector<BasicSymbol*>(0);
            break;
    }
}

//将所有变量的对应的所有基本块放到w中,键为变量的名称，值为变量所在的基本块
void initial_phi_w(std::vector<BasicBlock*>&bbs,std::unordered_map<std::string,std::vector<BasicBlock*>>&w){
    Symbol* sym=nullptr;
    for(auto& bb : bbs){
        std::set<std::string> s;
        for(LLVM*llvm=bb->head;llvm!=nullptr;llvm=llvm->next){
            sym=getDestSym(llvm);
            if(sym!=nullptr){
                if(s.find(sym->name)!=s.end())
                    continue;
                w[sym->name].push_back(bb);
                s.insert(sym->name);
            }
        }
    }
}

void insertPhi(std::vector<BasicBlock*>&bbs,std::vector<std::vector<int>>&df){
    std::unordered_map<std::string,std::vector<BasicBlock*>>w;
    initial_phi_w(bbs,w);
    int n;
    std::vector<std::set<std::string>>node_phi=std::vector<std::set<std::string>>(bbs.size());

    std::vector<BasicSymbol*> vals;
    std::vector<LabelSymbol*> srcs;

    for(auto& a:w){
        std::vector<BasicBlock*>bbs1=a.second;
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
                    BasicSymbol* basicSymbol=SymbolFactory::createVarSymbolWithScope(a.first,1);
                    vals=std::vector<BasicSymbol*>(0);
                    srcs=std::vector<LabelSymbol*>(0);
                    PhiLLVM* phiLLVM=LLVMfactory::createPhiLLVM(basicSymbol,vals,srcs);
                    phiLLVM->next=bbs[dfn]->head->next;
                    if(bbs[dfn]->head->next==nullptr)
                        bbs[dfn]->tail=phiLLVM;
                    else
                        bbs[dfn]->head->next->prev=phiLLVM;
                    bbs[dfn]->head->next=phiLLVM;
                    phiLLVM->prev=bbs[dfn]->head;
                    for(int j=0;j<bbs[dfn]->prevNode.size();j++){
                        phiLLVM->addCase(SymbolFactory::createVarSymbolWithScope(a.first,1),SymbolFactory::createLabelSymbolWithScope(bbs[dfn]->prevNode[j]->label->label->name,1));
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
}

void rename(std::vector<BasicBlock*>&bbs,int idx){
    BasicBlock* bb=bbs[idx];
    std::vector<std::string>defs;

    //给phi指令的目的操作数改名
    for(LLVM* llvm=bb->head;llvm!=nullptr;llvm=llvm->next){
        if(llvm->getLLVMType()==LLVMtype::phi){
            BasicSymbol* basicSymbol=getDestSym(llvm);
            count[basicSymbol->name]++;
            st[basicSymbol->name].push(count[basicSymbol->name]);
            basicSymbol->ssa_name=basicSymbol->name+"."+std::to_string(count[basicSymbol->name]);
            defs.push_back(basicSymbol->name);
        }
    }

    //重命名当前块内的除了phi指令以外的变量
    for(LLVM* llvm=bb->head;llvm!=nullptr;llvm=llvm->next){
        if(llvm->getLLVMType()!=LLVMtype::phi){
            //先修改表达式右值
            std::vector<BasicSymbol*> bs=getSrcSym(llvm);
            for(auto& b : bs){
                if(b->getType()==symType::variable){
                    b->ssa_name=b->name+"."+std::to_string(st[b->name].top());
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
        for(LLVM* llvm=nxt_bb->head;llvm!=nullptr;llvm=llvm->next){
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
    for(int nxt : idom_reverse[bb->idx])
        rename(bbs,nxt);

    //该基本块中新创建的变量需要出栈
    for(auto &a:defs){
        if(!st[a].empty())
            st[a].pop();
    }
}


void SSA(std::vector<BasicBlock*>&bbs){
    initial_ssa(bbs);
    getDom(bbs);
    std::vector<int>idom=getIdom(bbs);
    std::vector<std::vector<int>> df=getDF(bbs,idom);
    insertPhi(bbs,df);
    idom_reverse=std::vector<std::vector<int>>(idom.size(),std::vector<int>(0));

    //idom是支配树的反向边，这里需要得到正向边来dfs
    for(int i=0;i<idom.size();i++){
        idom_reverse[idom[i]].push_back(i);
    }
    
    //初始化count和st
    for(auto& bb : bbs){
        for(LLVM* llvm=bb->head;llvm!=nullptr;llvm=llvm->next){
            BasicSymbol* basicSymbol=getDestSym(llvm);
            if(basicSymbol==nullptr)
                continue;
            count[basicSymbol->name]=0;
            if(st[basicSymbol->name].empty())
                st[basicSymbol->name].push(0);
        }
    }
    rename(bbs,0);
}