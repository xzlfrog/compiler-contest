#pragma once

#include"llvm.hpp"
#include"sym.hpp"
#include<boost/dynamic_bitset.hpp>
#include"../include/SymbolFactory.hpp"
#include"../include/LLVMFactory.hpp"

class BasicBlock;


typedef void (*basicBlockGen)(BasicBlock*,std::vector<BasicBlock*>);
typedef void (*basicBlockKill)(BasicBlock*,std::vector<BasicBlock*>);

class BasicBlock{
public:
    int num;
    LLVM* head=nullptr;
    LLVM* tail=nullptr;
    Label* label=nullptr;
    int idx;
    boost::dynamic_bitset<> gen;
    boost::dynamic_bitset<> kill;
    boost::dynamic_bitset<> in;
    boost::dynamic_bitset<> out;
    std::vector<BasicBlock*> prevNode;//block--->this
    std::vector<BasicBlock*> nextNode;//this--->block
    //BasicBlock* next;
    //BasicBlock* prev;

    static BasicBlock* createBasicBlock(LLVM* start,LLVM* end);
    void setGen(basicBlockGen func,std::vector<BasicBlock*> head);
    void setKill(basicBlockKill func,std::vector<BasicBlock*> head);

    ~BasicBlock()=default;
};

std::vector<BasicBlock*> divideBasicBlock(LLVMList llvmlist);//划分基本块
void connectBasicBlocks(std::vector<BasicBlock*>);//得到数据流图