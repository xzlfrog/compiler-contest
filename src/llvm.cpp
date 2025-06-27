#include"../include/llvm.hpp"

//LLVM
LLVMtype LLVM::getLLVMType(){return this->llvmType;}

//LLVMList
void LLVMList::InsertTail(LLVM* llvm){
    this->tail->next=llvm;
    llvm->prev=this->tail;
    this->tail=llvm;
    llvm->next=nullptr;
}

void LLVMList::InsertHead(LLVM* llvm){
    this->head->prev=llvm;
    llvm->next=this->head;
    this->head=llvm;
    llvm->prev=nullptr;
}

//insert after a specific position
void LLVMList::InsertAfter(LLVM* pos,LLVM* llvm){
    if(this->tail==pos){
        this->InsertHead(llvm);
        return;
    }
    pos->next=llvm;
    llvm->prev=pos;
}

//insert before a specific position
void LLVMList::InsertBefore(LLVM* pos,LLVM* llvm){
    if(this->head==pos){
        this->InsertHead(llvm);
        return;
    }
    pos->prev=llvm;
    llvm->next=pos;
}

//remove a specific LLVM node
void LLVMList::Remove(LLVM* llvm){
    LLVM* before=llvm->prev;
    LLVM* after=llvm->next;

    if(before!=nullptr)
        before->next=after;
    else
        this->head=after;

    if(after!=nullptr)
        after->next=before;
    else
        this->tail=before;
} 