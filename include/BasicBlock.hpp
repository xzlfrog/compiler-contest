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
void connectBasicBlocks(const std::vector<BasicBlock*>& bbs);//得到数据流图

//按照顺序（不是控制
//流的顺序，就从上面的基本块到下面的基本块的顺序），每一个基本块需要在最后添加mov指令作为源操作数寄存器的变量，比如
//%result = phi i32 [ %a, %block0 ], [ %b, %block1 ], [ %c, %block2 ]
//那么就会在返回的std::vector<std::vector<BasicBlock*>> res中，res[0]这个vector就会包含一个std::pair,这个pair的first是result,second是a
//res[1]这个vector就会包含一个std::pair,这个pair的first是result,second是b
//res[2]这个vector就会包含一个std::pair,这个pair的first是result,second是c
std::vector<std::vector<std::pair<BasicSymbol*,BasicSymbol*>>> getMovVar(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs);
std::vector<BasicBlock*> getCFG(LLVMList* llvmlist);//得到控制流图
BasicBlock* getBasicBlock(std::string& bb_name,std::vector<BasicBlock*>& bbs);//通过基本块开头的label的名称查找对应的基本块


void set(std::vector<bool>&a);
void set(std::vector<bool>&a,int j);
void reset(std::vector<bool>&a);
void reset(std::vector<bool>&a,int j);
int count_bool(std::vector<bool>&a);
void join_or(std::vector<bool>&a,std::vector<bool>&b);
void meet_and(std::vector<bool>&a,std::vector<bool>&b);

BasicSymbol* getDestSym(LLVM* llvm);