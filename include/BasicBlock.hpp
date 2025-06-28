#pragma once

#include"llvm.hpp"
#include"sym.hpp"

class BasicBlock;

template<typename T>
class MyList{
public:
    T* head;
    T* tail;
    
    void InsertTail(T* v){
        if(this->tail==nullptr){
            this->head=v;
            this->tail=v;
            return ;
        }
        this->tail->next=v;
        v->prev=this->tail;
        this->tail=v;
        v->next=nullptr;
    }

    void InsertHead(T* v){
        if(this->head==nullptr){
            this->head=v;
            this->tail=v;
            return ;
        }
        this->head->prev=v;
        v->next=this->head;
        this->head=v;
        v->prev=nullptr;
    }

    void InsertAfter(T* pos,T* v){
        if(this->tail==pos){
            this->InsertTail(v);
            return;
        }
        v->next=pos->next;
        if(pos->next)
            pos->next->prev=v;
        pos->next=v;
        v->prev=pos;
    }

    void InsertBefore(T* pos,T* v){
        if(this->head==pos){
            this->InsertHead(v);
            return;
        }
        if(pos->prev)
            pos->prev->next=v;
        v->prev=pos->prev;
        pos->prev=v;
        v->next=pos;
    }

    void Remove(T* v){
        T* before=v->prev;
        T* after=v->next;

        if(before!=nullptr)
            before->next=after;
        else
            this->head=after;

        if(after!=nullptr)
            after->prev=before;
        else
            this->tail=before;
    }
};

typedef void (*basicBlockGen)(BasicBlock*,MyList<BasicBlock>);
typedef void (*basicBlockKill)(BasicBlock*,MyList<BasicBlock>);

class BasicBlock{
public:
    LLVM* head=nullptr;
    LLVM* tail=nullptr;
    LabelSymbol* label=nullptr;
    std::vector<int> gen=std::vector<int>(0);
    std::vector<int> kill=std::vector<int>(0);
    std::vector<int> in=std::vector<int>(0);
    std::vector<int> out=std::vector<int>(0);
    std::vector<BasicBlock*> connectIn;//this--->block
    std::vector<BasicBlock*> connectOut;//block--->this
    BasicBlock* next;
    BasicBlock* prev;

    static BasicBlock* createBasicBlock(LLVM* start,LLVM* end);
    void setGen(basicBlockGen func,MyList<BasicBlock> head);
    void setKill(basicBlockKill func,MyList<BasicBlock> head);

    ~BasicBlock(){
        //this->gen.clear();

    }
};

MyList<BasicBlock> divideBasicBlock(LLVMList llvmlist);//划分基本块
void connectBasicBlocks(MyList<BasicBlock>);//得到数据流图