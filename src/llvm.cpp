#include"../include/llvm.hpp"

//LLVM
LLVMtype LLVM::getLLVMType(){return this->llvmType;}

//LLVMList
void LLVMList::InsertTail(LLVM* llvm){}
void LLVMList::InsertHead(LLVM* llvm){}
void LLVMList::InsertAfter(LLVM* pos,LLVM* llvm){}//insert after a specific position
void LLVMList::InsertBefore(LLVM* pos,LLVM* llvm){}//insert before a specific position
void LLVMList::Remove(LLVM* llvm){} //remove a specific LLVM node