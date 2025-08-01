#pragma once

#include"BasicBlock.hpp"

//void join_or(std::vector<bool>&a,std::vector<bool>&b);
//void meet_and(std::vector<bool>&a,std::vector<bool>&b);
void initial_ssa(std::vector<BasicBlock*>&bbs);
void getDom(std::vector<BasicBlock*>&bbs);
std::vector<int> getIdom(std::vector<BasicBlock*>&bbs);
std::vector<std::vector<int>> getDF(std::vector<BasicBlock*>&bbs,std::vector<int>idom);
void mem2reg_pass(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs);
void insertPhi(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs,std::vector<std::vector<int>>&df);
std::vector<Symbol*> getSrcSym(LLVM* llvm);
void rename(LLVMList* llvmlist,std::vector<BasicBlock*>&bbs,int idx);
void SSA(LLVMList* llvmlist);//主要是这个函数，这个函数调用了前面的函数，把语句的变量转化为SSA形式