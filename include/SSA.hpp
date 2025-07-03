#pragma once

#include"BasicBlock.hpp"

void join_or(boost::dynamic_bitset<>&a,boost::dynamic_bitset<>&b);
void meet_and(boost::dynamic_bitset<>&a,boost::dynamic_bitset<>&b);
void initial_ssa(std::vector<BasicBlock*>&bbs);
void getDom(std::vector<BasicBlock*>&bbs);
std::vector<int> getIdom(std::vector<BasicBlock*>&bbs);
std::vector<std::vector<int>> getDF(std::vector<BasicBlock*>&bbs,std::vector<int>idom);
//对于getelementptr这个指令，我们是自己生成一个临时变量来处理，所以不用考虑变量重复赋值的问题
BasicSymbol* getDestSym(LLVM* llvm);
//将所有变量的对应的所有基本块放到w中,键为变量的名称，值为变量所在的基本块
void initial_phi_w(std::vector<BasicBlock*>&bbs,std::unordered_map<std::string,std::vector<BasicBlock*>>&w);
void insertPhi(std::vector<BasicBlock*>&bbs,std::vector<std::vector<int>>&df);
std::vector<BasicSymbol*> getSrcSym(LLVM* llvm);
void rename(std::vector<BasicBlock*>&bbs,int idx);
void SSA(std::vector<BasicBlock*>&bbs);//主要是这个函数，这个函数调用了前面的函数，把语句的变量转化为SSA形式