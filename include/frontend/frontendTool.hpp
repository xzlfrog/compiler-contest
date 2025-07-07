#pragma once
#include "../BasicBlock.hpp"
#include "../llvm.hpp"
#include "../LLVMFactory.hpp"
#include "../SymbolFactory.hpp"
#include "../SSA.hpp"

/* 假设的语义动作函数声明 */
dataType getTypeFromString(const char* typeStr);
std::unordered_map<std::string, Symbol*> symbolMap;
int scope = 0;
ModuleList *moduleList;
LLVMList *llvmList;

void* create_comp_unit(void* decl_or_func);
void* create_decl(void* const_or_var_decl);
void* create_const_decl(char* type, void* const_def_list);
void* create_var_decl(char* type, void* var_def_list);
void* create_const_def(char* id, void* dim_list, void* init_val);
void* create_var_def(char* id, void* dim_list, void* init_val);
void* create_func_def(char* ret_type, char* id, void* params, void* block);
void* create_block(void* decl_list, void* stmt_list);

void* create_assign_stmt(char* id, void* expr);
void* create_binary_expr(int op, void* left, void* right);
void* create_unary_expr(int op, void* expr);
void* create_func_call(char* id, void* args);
void* create_array_access(char* id, void* indices);

vector<int>* do_dimensions(int* const_exp, std::vector<int>& dimensions);
Data* expShorten(Expression* exp);

// 创建基本表达式
Expression* create_primary_IDENTIFIER(std::string id);
Expression* create_primary_INTCONST(int value);
Expression* create_primary_FLOATCONST(float value);
Expression* create_binary_expr(int op, Expression* exp1, Expression* exp2);
Expression* create_unary_expr(int op, Expression* exp);