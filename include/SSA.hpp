#pragma once

#include"BasicBlock.hpp"
#include<boost/dynamic_bitset.hpp>
#include"LLVMFactory.hpp"
#include"SymbolFactory.hpp"
#include<set>

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
            for(auto p : bbs[i]->prevNode){
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

Symbol* getDestSym(LLVM* llvm){
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
        case LLVMtype::fadd:
        case LLVMtype::fsub:
        case LLVMtype::fmul:
        case LLVMtype::fdiv:
        case LLVMtype::frem:
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
        case LLVMtype::trunc:
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
        case LLVMtype::addrspacecast:
        {
            TypeConversionOperation* ir=dynamic_cast<TypeConversionOperation*>(llvm);
            return ir->dest_sym;
        }
        case LLVMtype::load:
        {
            LoadLLVM* ir=dynamic_cast<LoadLLVM*>(llvm);
            return ir->dest_sym;
        }
        case LLVMtype::getelementptr:
        {
            GetElementPtrLLVM* ir=dynamic_cast<GetElementPtrLLVM*>(llvm);
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

//将所有变量的对应的所有基本块放到w中,键为变量的名称，值为变量所在的基本块
void initial_phi_w(std::vector<BasicBlock*>&bbs,std::unordered_map<std::string,std::vector<BasicBlock*>>&w){
    Symbol* sym=nullptr;
    for(auto bb : bbs){
        std::set<std::string> s;
        for(LLVM*llvm=bb->head;llvm!=bb->tail;llvm=llvm->next){
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
    for(auto a:w){
        std::vector<BasicBlock*>bbs=a.second;
        int i=0;
        while(i<bbs.size()){
            n=bbs[i]->idx;
            for(auto dfn : df[n]){
                BasicSymbol* basicSymbol=SymbolFactory::createVarSymbol(a.first);
                PhiLLVM* phiLLVM=LLVMfactory::createPhiLLVM(basicSymbol,std::vector<BasicSymbol*>(0),std::vector<LabelSymbol*>(0));
                bbs[dfn]->head->next=phiLLVM;
                phiLLVM->prev=bbs[dfn]->head;
                for(int j=0;j<bbs[dfn]->prevNode.size();j++){
                    phiLLVM->addCase(SymbolFactory::createVarSymbol(a.first),SymbolFactory::createLabelSymbol(bbs[dfn]->prevNode[j]->label->label->name));
                }
                //todo
                if(dfn)
                    a.second.push_back(bbs[dfn]);
            }
            i++;
        }
        w.erase(a.first);
    }
}