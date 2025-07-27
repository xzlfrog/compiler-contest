#pragma once

#include"llvm.hpp"
#include"sym.hpp"
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
    std::vector<bool> gen;
    std::vector<bool> kill;
    std::vector<bool> in;
    std::vector<bool> out;
    std::vector<BasicBlock*> prevNode=std::vector<BasicBlock*>(0);//block--->this
    std::vector<BasicBlock*> nextNode=std::vector<BasicBlock*>(0);//this--->block
    //BasicBlock* next;
    //BasicBlock* prev;

    static BasicBlock* createBasicBlock(LLVM* start,LLVM* end, LLVMList* llvmlist);
    void setGen(basicBlockGen func,std::vector<BasicBlock*> head);
    void setKill(basicBlockKill func,std::vector<BasicBlock*> head);

    ~BasicBlock()=default;
};

std::vector<BasicBlock*> divideBasicBlock(LLVMList* llvmlist);//划分基本块
void connectBasicBlocks(std::vector<BasicBlock*>);//得到数据流图