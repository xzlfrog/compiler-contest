#pragma once
#include "../../include/LLVMFactory.hpp"
#include "../../include/exp.hpp"
#include "../../include/SymbolFactory.hpp"

/*struct LoopContext {
    LabelSymbol* continueLabel;  // 跳转回循环条件
    LabelSymbol* breakLabel;     // 跳出循环
};
std::vector<LoopContext> loopStack;  // 循环上下文栈

LLVM* create_if_stmt(Expression* cond, LLVM* then_stmt, LLVM* else_stmt);
LLVM* create_if_stmt(Expression* cond, LLVM* then_stmt);
LLVM* create_while_stmt(Expression* cond, LLVM* stmt);
LLVM* create_break_stmt();
LLVM* create_continue_stmt();
LLVM* create_return_stmt(Expression* expr);
LLVM* create_return_stmt();
LLVM* create_assign_stmt(std::string id, Expression* expr);*/