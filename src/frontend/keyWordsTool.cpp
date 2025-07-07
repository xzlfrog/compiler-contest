#include "../../include/frontend/keyWordsTool.hpp"
#include "../../include/frontend/frontendTool.hpp"


LLVM* create_if_stmt(Expression* cond, LLVM* then_stmt) {
    // Create a new if statement with the given condition and then statement
    LabelSymbol* trueBranch = SymbolFactory::createTmpLabelSymbol();
    LabelSymbol* endBranch = SymbolFactory::createTmpLabelSymbol();
    
    // Create the conditional branch LLVM instruction
    ConditionalBranchLLVM* condBranch = LLVMfactory::createConditionalBranchLLVM(cond->sym, trueBranch, endBranch);

    Label* trueLabel = LLVMfactory::createLableLLVM(trueBranch);
    condBranch->LLVM::InsertTail(trueLabel);

    condBranch->LLVM::InsertTail(then_stmt);

    // Create the end label
    Label* endLabel = LLVMfactory::createLableLLVM(endBranch);
    condBranch->LLVM::InsertTail(endLabel);
    
    // Return the complete if statement as an LLVM instruction
    return condBranch;
}

LLVM* create_if_stmt(Expression* cond, LLVM* then_stmt, LLVM* else_stmt){
    
    LabelSymbol* trueBranch = SymbolFactory::createTmpLabelSymbol();
    LabelSymbol* falseBranch = SymbolFactory::createTmpLabelSymbol();
    LabelSymbol* endBranch = SymbolFactory::createTmpLabelSymbol();

    // Create the conditional branch LLVM instruction
    ConditionalBranchLLVM* condBranch = LLVMfactory::createConditionalBranchLLVM(cond->sym, trueBranch, falseBranch);

    // Create the true branch label
    Label* trueLabel = LLVMfactory::createLableLLVM(trueBranch);
    condBranch->LLVM::InsertTail(trueLabel);

    // Insert the then block
    condBranch->LLVM::merge(then_stmt);
    
    UnconditionalBranchLLVM* EndBranch = LLVMfactory::createUnconditionalBranchLLVM(endBranch);
    condBranch->LLVM::InsertTail(EndBranch);

    // Create the false branch label
    Label* falseLabel = LLVMfactory::createLableLLVM(falseBranch);   
    condBranch->LLVM::InsertTail(falseLabel);

    condBranch->LLVM::InsertTail(else_stmt);    
    
    return condBranch;
}

LLVM* create_while_stmt(Expression* cond, LLVM* stmt){
    LabelSymbol* condBranch = SymbolFactory::createTmpLabelSymbol();
    LabelSymbol* startBranch = SymbolFactory::createTmpLabelSymbol();
    LabelSymbol* endBranch = SymbolFactory::createTmpLabelSymbol();

    loopStack.push_back({startBranch, endBranch}); // Push the loop context onto the stack
    // Create an unconditional branch to the start of the while loop
    UnconditionalBranchLLVM* uncondBranch = LLVMfactory::createUnconditionalBranchLLVM(condBranch);
    
    // Create the conditional branch for the while loop
    Label* condLabel = LLVMfactory::createLableLLVM(condBranch);
    ConditionalBranchLLVM* condBranchLLVM = LLVMfactory::createConditionalBranchLLVM(cond->sym, startBranch, endBranch);
    uncondBranch->LLVM::InsertTail(condLabel);

    Label* startLabel = LLVMfactory::createLableLLVM(startBranch);
    uncondBranch->LLVM::InsertTail(startLabel);
    uncondBranch->LLVM::InsertTail(stmt);
    uncondBranch->LLVM::InsertTail(condLabel);

    // Create the end label for the while loop
    Label* endLabel = LLVMfactory::createLableLLVM(endBranch);
    uncondBranch->LLVM::InsertTail(endLabel);

    loopStack.pop_back(); // Pop the loop context from the stack

    return uncondBranch;
}

LLVM* create_break_stmt() {
    if (loopStack.empty()) {
        throw std::invalid_argument("break statement outside loop");
        return nullptr;
    }
    LoopContext& currentLoop = loopStack.back();
    return LLVMfactory::createUnconditionalBranchLLVM(currentLoop.breakLabel);
}

LLVM* create_continue_stmt() {
    if (loopStack.empty()) {
        throw std::invalid_argument("continue statement outside loop");
        return nullptr;
    }
    LoopContext& currentLoop = loopStack.back();
    return LLVMfactory::createUnconditionalBranchLLVM(currentLoop.continueLabel);
}

LLVM* create_return_stmt(Expression* expr) {
    return LLVMfactory::createReturnLLVM(expr->sym);
}

LLVM* create_return_stmt(){
    return LLVMfactory::createReturnLLVM(nullptr);
}

LLVM* create_assign_stmt(std::string name, Expression* expr){
    PointerSymbol* pointer_sym = symbolMap[name];
    return ;
}