#include"../include/llvm.hpp"

//LLVM
LLVMtype LLVM::getLLVMType(){return this->llvmType;}

//LLVMList
void LLVMList::InsertTail(LLVM* llvm){
    if(this->tail==nullptr){
        this->head=llvm;
        this->tail=llvm;
        return ;
    }
    this->tail->next=llvm;
    llvm->prev=this->tail;
    this->tail=llvm;
    llvm->next=nullptr;
}

void LLVMList::InsertHead(LLVM* llvm){
    if(this->head==nullptr){
            this->head=llvm;
            this->tail=llvm;
            return ;
        }
    this->head->prev=llvm;
    llvm->next=this->head;
    this->head=llvm;
    llvm->prev=nullptr;
}

//insert after a specific position
void LLVMList::InsertAfter(LLVM* pos,LLVM* llvm){
    if(this->tail==pos){
        this->InsertTail(llvm);
        return;
    }
    llvm->next=pos->next;
    if(pos->next)
        pos->next->prev=llvm;
    pos->next=llvm;
    llvm->prev=pos;
}

//insert before a specific position
void LLVMList::InsertBefore(LLVM* pos,LLVM* llvm){
    if(this->head==pos){
        this->InsertHead(llvm);
        return;
    }
    if(pos->prev)
        pos->prev->next=llvm;
    llvm->prev=pos->prev;
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
        after->prev=before;
    else
        this->tail=before;
} 


//LLVMList
void ModuleList::InsertTail(Module* module){
    if(this->tail==nullptr){
        this->head=module;
        this->tail=module;
        return ;
    }
    this->tail->next=module;
    module->prev=this->tail;
    this->tail=module;
    module->next=nullptr;
}

void ModuleList::InsertHead(Module* module){
    if(this->head==nullptr){
            this->head=module;
            this->tail=module;
            return ;
        }
    this->head->prev=module;
    module->next=this->head;
    this->head=module;
    module->prev=nullptr;
}

//insert after a specific position
void ModuleList::InsertAfter(Module* pos,Module* module){
    if(this->tail==pos){
        this->InsertTail(module);
        return;
    }
    module->next=pos->next;
    if(pos->next)
        pos->next->prev=module;
    pos->next=module;
    module->prev=pos;
}

//insert before a specific position
void ModuleList::InsertBefore(Module* pos,Module* module){
    if(this->head==pos){
        this->InsertHead(module);
        return;
    }
    if(pos->prev)
        pos->prev->next=module;
    module->prev=pos->prev;
    pos->prev=module;
    module->next=pos;
}

//remove a specific LLVM node
void ModuleList::Remove(Module* module){
    Module* before=module->prev;
    Module* after=module->next;

    if(before!=nullptr)
        before->next=after;
    else
        this->head=after;

    if(after!=nullptr)
        after->prev=before;
    else
        this->tail=before;
} 