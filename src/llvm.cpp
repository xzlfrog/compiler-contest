#include"../include/llvm.hpp"

//LLVM
LLVMtype LLVM::getLLVMType(){return this->llvmType;}

//LLVMList
void LLVMList::InsertTail(LLVM* llvm){
    LLVM* llvm_tail=llvm;
    while(llvm_tail->next!=nullptr){
        llvm_tail=llvm_tail->next;
    }
    if(this->tail==nullptr){
        this->head=llvm;
        this->tail=llvm_tail;
        return ;
    }
    this->tail->next=llvm;
    llvm->prev=this->tail;
    this->tail=llvm_tail;
}

void LLVMList::InsertHead(LLVM* llvm){
    LLVM* llvm_tail=llvm;
    while(llvm_tail->next!=nullptr){
        llvm_tail=llvm_tail->next;
    }
    if(this->head==nullptr){
        this->head=llvm;
        this->tail=llvm_tail;
        return ;
    }
    this->head->prev=llvm_tail;
    llvm_tail->next=this->head;
    this->head=llvm;
    llvm->prev=nullptr;
}

//insert after a specific position
void LLVMList::InsertAfter(LLVM* pos,LLVM* llvm){
    if(this->tail==pos){
        this->InsertTail(llvm);
        return;
    }
    LLVM* llvm_tail=llvm;
    while(llvm_tail->next!=nullptr){
        llvm_tail=llvm_tail->next;
    }
    llvm_tail->next=pos->next;
    if(pos->next)
        pos->next->prev=llvm_tail;
    pos->next=llvm;
    llvm->prev=pos;
}

//insert before a specific position
void LLVMList::InsertBefore(LLVM* pos,LLVM* llvm){
    if(this->head==pos){
        this->InsertHead(llvm);
        return;
    }
    LLVM* llvm_tail=llvm;
    while(llvm_tail->next!=nullptr){
        llvm_tail=llvm_tail->next;
    }
    if(pos->prev)
        pos->prev->next=llvm;
    llvm->prev=pos->prev;
    pos->prev=llvm_tail;
    llvm_tail->next=pos;
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


//ModuleList
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

Module* LLVM_to_Module(LLVM* llvm){
    LLVM* tail=llvm;
    while(tail->next){
        tail=tail->next;
    }
    Module* module=new LLVMList();
    module->head=llvm;
    module->tail=tail;
    return module;
}

void LLVMList::InsertTail(LLVMList* llvmlist){
    if(this->tail==nullptr){
        this->head=llvmlist->head;
        this->tail=llvmlist->tail;
        return;
    }
    else if(llvmlist->tail==nullptr){
        return;
    }
    this->tail->next=llvmlist->head;
    llvmlist->head->prev=this->tail;
    this->tail=llvmlist->tail;
    llvmlist->head=this->head;
}

void LLVMList::InsertHead(LLVMList* llvmlist){
    if(this->tail==nullptr){
        this->head=llvmlist->head;
        this->tail=llvmlist->tail;
        return;
    }
    else if(llvmlist->tail==nullptr){
        return;
    }
    this->head->prev=llvmlist->tail;
    llvmlist->tail->next=this->head;
    this->head=llvmlist->head;
    llvmlist->tail=this->tail;
}