#include"../include/SSA.hpp"
#include"../include/LLVMFactory.hpp"
#include"../include/SymbolFactory.hpp"
#include<set>
#include<stack>
#include<iostream>

std::unordered_map<std::string,int>count;//记录每个变量的初始化次数
std::unordered_map<std::string,std::stack<int,std::vector<int>>>st;//记录每一个变量的版本号的栈
std::vector<std::vector<int>>idom_reverse;
std::unordered_map<std::string,PointerSymbol*>bs_to_ps;
std::unordered_map<std::string,std::unordered_map<BasicBlock*,BasicSymbol*>> worklists;
std::unordered_map<std::string,std::stack<BasicSymbol*>>last_store;
std::unordered_map<std::string,std::stack<BasicSymbol*>>last_load;
std::set<std::string> array_item_pointer;

void join_or(std::vector<bool>&a,std::vector<bool>&b){
    for(int i=0;i<a.size();i++){
        a[i]=a[i]|b[i];
    }
}

void meet_and(std::vector<bool>&a,std::vector<bool>&b){
    for(int i=0;i<a.size();i++){
        a[i]=a[i]&b[i];
    }
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

void initial_ssa(std::vector<BasicBlock*>&bbs){
    int n=bbs.size();
    int i=0;
    BasicBlock* bb;
    //第0个为entry
    for(int i=0;i<n;i++){
        bb=bbs[i];
        bb->in=std::vector<bool>(n);
        bb->out=std::vector<bool>(n);
        //初始时out均为1
        //must分析
        if(i!=0){
            set(bb->out);//全部赋值为1
            set(bb->in);
        }
        else{
            reset(bb->out);
            set(bb->out,0);
            reset(bb->in);
        }
        bb->gen=std::vector<bool>(n);
        bb->kill=std::vector<bool>(n);
        //对于ssa，gen为只有自己的对应位为1,其余位为0
        reset(bb->gen);
        set(bb->gen,i);
    }
}

void getDom(std::vector<BasicBlock*>&bbs){
    bool flag=false;
    int n=bbs.size();
    std::vector<bool>old(n);
    initial_ssa(bbs);
    do{
        flag=false;
        for(int i=1;i<n;i++){
            old=bbs[i]->out;
            set(bbs[i]->in);
            for(auto bb:bbs[i]->prevNode){
                meet_and(bbs[i]->in,bb->out);
            }
            bbs[i]->out=bbs[i]->in;
            set(bbs[i]->out,i);
            if(bbs[i]->out!=old){
                flag=true;
            }
        }
    }while(flag);
    /*for(int i=0;i<n;i++){
        std::vector<int>dom;
        std::cout<<"dom["<<i<<"] = ";
        for(int j=0;j<n;j++){
            if(bbs[i]->out[j]==1){
                dom.push_back(j);
                std::cout<<j<<" , ";
            }
        }
        std::cout<<"\n";
    }
    std::cout<<"getDom is done\n";*/
}

std::vector<int> getIdom(std::vector<BasicBlock*>&bbs){
    int n=bbs.size();
    std::vector<bool> tmp=std::vector<bool>(n);
    std::vector<int> ret;
    ret.push_back(0);//第一个是没有意义的，只是为了和bbs的序号对应，如果真要看的话，可以当作是entry节点的直接支配点，也是它自己
    int max;
    for(int i=1;i<n;i++){
        max=-1;
        if(count_bool(bbs[i]->out)==n){
            if(i!=n-1){
                ret.push_back(-1);
            }
            else{
                for(int j=1;j<n-1;j++){
                    if(ret[j]!=j-1){
                        ret.push_back(-1);
                        break;
                    }
                }
                if(ret.size()!=n){
                    ret.push_back(n-2);
                }
            }
            continue;
        }
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            reset(tmp);
            set(tmp,j);
            meet_and(tmp,bbs[i]->out);
            if(count_bool(tmp)==1){
                if(max==-1||count_bool(bbs[max]->out)<count_bool(bbs[j]->out))
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
    /*for(int i=0;i<n;i++){
        std::cout<<"idom["<<i<<"] = "<<ret[i]<<"\n";
    }
    std::cout<<"getIdom is done!\n";*/
    return ret;
}

std::vector<std::vector<int>> getDF(std::vector<BasicBlock*>&bbs,std::vector<int>idom){
    int n=bbs.size();
    std::vector<std::set<int>> df_set(n);
    std::vector<std::vector<int>>df(n);
    int runner;
    for(int i=1;i<n;i++){
        if(idom[i]!=-1&&bbs[i]->prevNode.size()>=2){
            for(auto& p : bbs[i]->prevNode){
                runner=p->idx;
                while(runner!=-1&&runner!=idom[i]){
                    df_set[runner].insert(i);
                    runner=idom[runner];
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        df[i].assign(df_set[i].begin(), df_set[i].end());
    }
    //std::cout<<"getDF is done"<<"\n";
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
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
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
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
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
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
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
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
            return ret;
        }
        /*case LLVMtype::phi:
        {
            PhiLLVM* ir=dynamic_cast<PhiLLVM*>(llvm);
            for(auto &a : ir->getValAndSrc()){
                ret.push_back(a.first);
            }
            return ret;
        }*/
        case LLVMtype::llvm_neg:
        case LLVMtype::llvm_fneg:
        {
            UnaryOperationLLVM* ir=dynamic_cast<UnaryOperationLLVM*>(llvm);
            ret.push_back(ir->src_sym);
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
            return ret;
        }
        case LLVMtype::br_conditional:
        {
            ConditionalBranchLLVM* ir=dynamic_cast<ConditionalBranchLLVM*>(llvm);
            ret.push_back(ir->condition);
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
            return ret;
        }
        case LLVMtype::func_def:
        {
            FuncDefination* ir=dynamic_cast<FuncDefination*>(llvm);
            for(auto & a : ir->params){
                if(a->getType()==symType::variable)
                    ret.push_back(a);
            }
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
            return ret;
        }
        case LLVMtype::getelementptr:
        {
            GetElementPtrLLVM* ir=dynamic_cast<GetElementPtrLLVM*>(llvm);
            for(auto & a : ir->ty_idx){
                if(a.second->getType()==symType::variable){
                    ret.push_back(a.second);
                }
            }
            /*for(auto & a : ret){
                if(a!=nullptr&&a->getType()==symType::variable&&last_load.find(a->name)!=last_load.end())
                    a=last_load[a->name].top();
            }*/
        }
        default:
            return std::vector<Symbol*>(0);
            break;
    }
}

void mem2reg_pass_pre(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs){
    for(auto & bb : bbs){
        for(LLVM* llvm=bb->head;llvm!=bb->tail->next;llvm=llvm->next){
            switch (llvm->getLLVMType())
            {
                case LLVMtype::allocate_nonarray:{
                    AllocaNonArrayLLVM* alloca=dynamic_cast<AllocaNonArrayLLVM*>(llvm);
                    worklists[alloca->sym->name]=std::unordered_map<BasicBlock*,BasicSymbol*>();
                    break;
                }
                case LLVMtype::store:{
                    StoreLLVM* storeLLVM=dynamic_cast<StoreLLVM*>(llvm);
                    worklists[storeLLVM->dest_sym->name][bb]=storeLLVM->src_sym;
                    break;
                }
                case LLVMtype::load:{
                    //LoadLLVM* loadLLVM=dynamic_cast<LoadLLVM*>(llvm);
                    //loadLLVM->dest_sym=worklists[loadLLVM->src_sym->name][bb];
                    break;
                }
                case LLVMtype::getelementptr:{
                    GetElementPtrLLVM* getelementptr=dynamic_cast<GetElementPtrLLVM*>(llvm);
                    array_item_pointer.insert(getelementptr->dest_sym->name);
                }
                default:{
                    break;
                }
            }
        }
    }
}

std::string remove_scope_idx_from_name(std::string name){
    for(int i=0;i<name.length();i++){
        if(name.substr(i,6)==".scope"){
            return name.substr(0,i);
        }
    }
    return "";
}

void insertPhi(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs,std::vector<std::vector<int>>&df){
    std::unordered_map<std::string,std::vector<BasicBlock*>>w;
    mem2reg_pass_pre(llvmlist,bbs);
    int n;
    for(auto & worklist : worklists){
        for( auto & a : worklist.second){
            w[worklist.first].push_back(a.first);
        }
    }

    std::vector<BasicSymbol*> vals;
    std::vector<LabelSymbol*> srcs;

    for(auto& a:w){
        std::vector<BasicBlock*>&bbs1=a.second;
        std::string sym_name=a.first;
        BasicSymbol* bs;
        int sz=bbs1.size();
        std::set<int>s1;
        std::queue<int> worklist;
        for(int j=0;j<sz;j++){
            worklist.push(bbs1[j]->idx);
        }
        while(!worklist.empty()){
            n=worklist.front();
            worklist.pop();
            if(s1.find(n)!=s1.end())
                continue;
            for(auto& dfn : df[n]){
                if(s1.find(dfn)==s1.end()){
                    dataType bs_type=worklists[sym_name].begin()->second->getDataType();
                    s1.insert(dfn);
                    vals=std::vector<BasicSymbol*>(0);
                    srcs=std::vector<LabelSymbol*>(0);
                    bs=SymbolFactory::createVarSymbolWithScope(remove_scope_idx_from_name(sym_name)+".loader",bs_type,2);
                    PhiLLVM* phiLLVM=LLVMfactory::createPhiLLVM(SymbolFactory::createVarSymbolWithScope(remove_scope_idx_from_name(sym_name)+".loader",bs_type,2),vals,srcs);
                    StoreLLVM* storeLLVM=nullptr;
                    PointerSymbol* ps=new PointerSymbol();
                    ps->pointedData=bs->data;
                    ps->name=sym_name;
                    ps->PointedType=bs->getDataType();
                    storeLLVM=LLVMfactory::createStoreLLVM(bs,ps);
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
                        //bs=worklists[sym_name][bbs[bbs[dfn]->prevNode[j]->idx]];
                        phiLLVM->addCase(SymbolFactory::createVarSymbolWithScope(remove_scope_idx_from_name(sym_name)+".loader",bs_type,2),bbs[dfn]->prevNode[j]->label->label);
                    }
                    s1.insert(dfn);
                }
            }
        }
    }
    std::cout<<"insert Phi is done"<<"\n";
}

void replace_symbol(LLVM* llvm){
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
    case LLVMtype::fcmp_ord:{
        ArithmeticOperationLLVM* ir =dynamic_cast<ArithmeticOperationLLVM*>(llvm);
        if(bs_to_ps.end()!=bs_to_ps.find(ir->a->name)){
            ir->a=copy(last_load[ir->a->name].top());
        }
        if(bs_to_ps.end()!=bs_to_ps.find(ir->b->name)){
            ir->b=copy(last_load[ir->b->name].top());
        }
        break;
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
    case LLVMtype::inttoptr:{
        TypeConversionOperation* ir=dynamic_cast<TypeConversionOperation*>(llvm);
        if(bs_to_ps.find(ir->src_sym->name)!=bs_to_ps.end()){
            ir->src_sym=copy(last_load[ir->src_sym->name].top());
        }
        break;
    }
    case LLVMtype::getelementptr:{
        GetElementPtrLLVM* ir=dynamic_cast<GetElementPtrLLVM*>(llvm);
        for(auto & a : ir->ty_idx){
            if(bs_to_ps.find(a.second->name)!=bs_to_ps.end()){
                a.second=copy(last_load[a.second->name].top());
            }
        }
        break;
    }
    case LLVMtype::llvm_fneg:{
        UnaryOperationLLVM* ir=dynamic_cast<UnaryOperationLLVM*>(llvm);
        if(bs_to_ps.find(ir->src_sym->name)!=bs_to_ps.end()){
            ir->src_sym=copy(last_load[ir->src_sym->name].top());
        }
        break;
    }
    case LLVMtype::ret:{
        ReturnLLVM* ir=dynamic_cast<ReturnLLVM*>(llvm);
        if(ir->returnValue!=nullptr&&bs_to_ps.find(ir->returnValue->name)!=bs_to_ps.end()){
            ir->returnValue=copy(last_load[ir->returnValue->name].top());
        }
        break;
    }
    case LLVMtype::call:{
        CallLLVM* ir=dynamic_cast<CallLLVM*>(llvm);
        for(auto & a : ir->arguments){
            if(a->getType()==symType::variable&&bs_to_ps.find(a->name)!=bs_to_ps.end()){
                a=copy(last_load[a->name].top());
            }
        }
        break;
    }
    case LLVMtype::phi:{
        PhiLLVM* ir=dynamic_cast<PhiLLVM*>(llvm);
        for(auto & a : ir->vals_srcs){
            if(bs_to_ps.find(a.first->name)!=bs_to_ps.end()){
                a.first=copy(last_load[a.first->name].top());
            }
        }
        break;
    }
    default:
        break;
    }
}

void rename(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs,int idx){
    BasicBlock* bb=bbs[idx];
    std::vector<std::string>defs;
    std::unordered_map<std::string,int>loads;
    std::unordered_map<std::string,int>stores;

    //给phi指令的目的操作数改名
    for(LLVM* llvm=bb->head;llvm!=bb->tail->next;llvm=llvm->next){
        if(llvm->getLLVMType()==LLVMtype::phi){
            BasicSymbol* basicSymbol=getDestSym(llvm);
            count[basicSymbol->name]++;
            st[basicSymbol->name].push(count[basicSymbol->name]);
            basicSymbol->ssa_name=basicSymbol->name+"."+std::to_string(count[basicSymbol->name]);
            defs.push_back(basicSymbol->name);
        }
    }

    bool flag_break=false;
    LLVM* nxt_llvm;
    //重命名当前块内的除了phi指令以外的变量
    for(LLVM* llvm=bb->head;llvm!=bb->tail->next&&!flag_break;llvm=nxt_llvm){
        nxt_llvm=llvm->next;
        if(llvm->getLLVMType()!=LLVMtype::phi){
            if(llvm->getLLVMType()==LLVMtype::load){
                LoadLLVM* loadLLVM=dynamic_cast<LoadLLVM*>(llvm);
                if(loadLLVM->src_sym->scope!=GLOBAL_SCOPE&&worklists.find(loadLLVM->src_sym->name)!=worklists.end()){
                    if(array_item_pointer.find(loadLLVM->src_sym->name)!=array_item_pointer.end())
                        continue;
                    if(llvm==bb->tail){
                        bb->tail=llvm->prev;
                        flag_break=true;
                    }
                    llvmlist->Remove(llvm);
                    bs_to_ps[loadLLVM->dest_sym->name]=loadLLVM->src_sym;
                    last_load[loadLLVM->dest_sym->name].push(last_store[loadLLVM->src_sym->name].top());
                    //replace_symbol(llvmlist,llvm,last_store[loadLLVM->src_sym->name].top(),loadLLVM->src_sym);
                    loads[loadLLVM->dest_sym->name]++;
                }
            }
            else{
                //先修改表达式右值
                replace_symbol(llvm);
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
            }

            if(llvm->getLLVMType()==LLVMtype::store){
                StoreLLVM* storeLLVM=dynamic_cast<StoreLLVM*>(llvm);
                if(storeLLVM->dest_sym->scope!=GLOBAL_SCOPE&&worklists.find(storeLLVM->dest_sym->name)!=worklists.end()){
                    if(array_item_pointer.find(storeLLVM->dest_sym->name)!=array_item_pointer.end())
                        continue;
                    if(llvm==bb->tail){
                        bb->tail=llvm->prev;
                        flag_break=true;
                    }
                    llvmlist->Remove(llvm);
                    last_store[storeLLVM->dest_sym->name].push(storeLLVM->src_sym);
                    stores[storeLLVM->dest_sym->name]++;
                }
            }
            else{
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
    }

    //修改后继节点的phi指令的右值
    for(auto nxt_bb : bb->nextNode){
        for(LLVM* llvm=nxt_bb->head;llvm!=nullptr&&llvm->prev!=nxt_bb->tail;llvm=llvm->next){
            if(llvm->getLLVMType()==LLVMtype::phi){
                PhiLLVM* phiLLVM=dynamic_cast<PhiLLVM*>(llvm);
                std::vector<std::pair<BasicSymbol*,LabelSymbol*>> srcAndLabel=phiLLVM->getValAndSrc();
                for(auto &p : srcAndLabel){
                    if(p.first->getType()==symType::constant_nonvar||p.first->getType()==symType::constant_var)
                        continue;
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
        rename(llvmlist,bbs,nxt);
    }

    //该基本块中新创建的变量需要出栈
    for(auto &a:defs){
        if(!st[a].empty())
            st[a].pop();
    }

    for(auto &a:loads){
        for(int i=0;i<a.second;i++){
            last_load[a.first].pop();
        }
    }

    for(auto &a:stores){
        for(int i=0;i<a.second;i++){
            last_store[a.first].pop();
        }
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
            llvmlist->Remove(bbs[i]->tail);
        }
    }
}

void delete_alloca(LLVMList* llvmlist){
    LLVM* nxt_llvm;
    FuncDefination* func=dynamic_cast<FuncDefination*>(llvmlist->head);
    for(LLVM* llvm=llvmlist->head;llvm!=func->block_tail;llvm=nxt_llvm){
        nxt_llvm=llvm->next;
        if(llvm->getLLVMType()==LLVMtype::allocate_nonarray){
            llvmlist->Remove(llvm);
        }
    }
}

void SSA(LLVMList* llvmlist){
    count.clear();
    st.clear();
    last_store.clear();
    last_load.clear();
    bs_to_ps.clear();
    int count_sz=count.size();
    array_item_pointer.clear();
    int st_sz=st.size();
    std::vector<Symbol*>params=getSrcSym(llvmlist->head);
    worklists.clear();
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
    insertPhi(llvmlist,bbs,df);
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
    rename(llvmlist,bbs,0);
    delete_alloca(llvmlist);
    dead_code_eliminate(bbs,llvmlist,idom);
    //std::cout<<"ssa is done!"<<"\n";
}