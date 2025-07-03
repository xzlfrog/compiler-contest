#pragma once
#include "../BasicBlock.hpp"
#include "../LLVMFactory.hpp"
#include "../SymbolFactory.hpp"

/* 假设的语义动作函数声明 */
void* create_comp_unit(void* decl_or_func);
void* create_decl(void* const_or_var_decl);
void* create_const_decl(char* type, void* const_def_list);
void* create_var_decl(char* type, void* var_def_list);
void* create_const_def(char* id, void* dim_list, void* init_val);
void* create_var_def(char* id, void* dim_list, void* init_val);
void* create_func_def(char* ret_type, char* id, void* params, void* block);
void* create_block(void* decl_list, void* stmt_list);
void* create_if_stmt(void* cond, void* then_stmt, void* else_stmt);
void* create_while_stmt(void* cond, void* stmt);
void* create_return_stmt(void* expr);
void* create_assign_stmt(char* id, void* expr);
void* create_binary_expr(int op, void* left, void* right);
void* create_unary_expr(int op, void* expr);
void* create_func_call(char* id, void* args);
void* create_array_access(char* id, void* indices);