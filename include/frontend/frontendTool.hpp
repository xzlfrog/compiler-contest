#pragma once
#include "../BasicBlock.hpp"
#include "../llvm.hpp"
#include "../LLVMFactory.hpp"
#include "../SymbolFactory.hpp"
#include "../SSA.hpp"
#include "../exp.hpp"
#include <stack>
#include <fstream>
#include <string>
#include<queue>

#define VOID_TYPE 0
#define INT_TYPE 1
#define FLOAT_TYPE 2

#define BINARY_OR 0
#define BINARY_AND 1
#define BINARY_EQ 2
#define BINARY_NE 3
#define BINARY_LT 4
#define BINARY_GT 5
#define BINARY_LE 6
#define BINARY_GE 7
#define BINARY_ADD 8
#define BINARY_SUB 9
#define BINARY_MUL 10
#define BINARY_DIV 11
#define BINARY_REM 12

#define SINGLE_POSITIVE 0
#define SINGLE_NEGTIVE 1
#define SINGLE_NOT 2

extern int scope;
extern int array_init_idx;
extern ModuleList* module_list;
extern std::vector<std::unordered_map<std::string,int>> variable_rename_table;
extern std::vector<std::unordered_map<std::string,Symbol*>> variable_table;
extern std::unordered_map<std::string,FuncSymbol*>func_table;
extern std::unordered_map<std::string,BasicSymbol*> pointer_to_var;
extern std::stack<LabelSymbol*> break_st,continue_st;
extern std::queue<Expression*>assign_queue;
extern std::stack<int>array_initial;//在面对数组变量初始化时，维护一个大小为当前嵌套大括号数量的栈，
//栈中每一个元素对应目前时嵌套的大括号中的第几个元素，比如int a[5]={1,2,3};
//此时栈里元素取决于当前规约到哪一个元素,规约到1时为0,规约到2时为1,规约到3时为2

/* 假设的语义动作函数声明 */
//dataType getTypeFromString(const char* typeStr);

BasicSymbol* isInReg(PointerSymbol* ps);
Expression* create_binary_expr(int op, Expression* a, Expression* b);//双元运算
Expression* create_unary_expr(int op, Expression* a);//单元运算
Expression* create_primary_IDENTIFIER(std::string name);//通过变量名称，将对应的变量加载到寄存器中
Symbol* findVar(std::string name);//查找某个名称的标识符
Expression* create_primary_INTCONST(int value);//根据某个值创建对应的expression
Expression* create_primary_FLOATCONST(float value);//根据某个值创建对应的expression
FuncSymbol* findFunc(std::string name);//根据函数名称查找对应的函数
Expression* create_func_call(std::string name, Expression* exp);//调用函数
std::vector<std::pair<dataType,BasicSymbol*>>& getIdxFromExp(std::vector<Expression*>* exps);//这个不重要，用于get_array_item函数中生成getelementptr的指令
Expression* get_element(std::string name,std::vector<Expression*>* exps);//取出某个数组中的某个元素
LLVMList* create_if_stmt(Expression* exp,LLVMList* llvmlist);//if语句llvm ir生成
LLVMList* create_if_else_stmt(Expression* exp,LLVMList* llvmlist1,LLVMList* llvmlist2);//if-else语句llvm ir生成
LLVMList* create_while(Expression* exp);//while语句的llvm ir生成
LLVMList* create_while_stmt(LLVMList* llvmlist,LLVMList* stmt);//while语句的llvm ir生成
LLVMList* create_return_stmt(Expression* exp);//return语句的llvm ir生成
LLVMList* create_const_decl(int btype,std::vector<Symbol*>* syms);
Symbol* create_array_const_def(std::string name,std::vector<int>* idxs,Expression* exp,ArrayInitial* arrayInitial);//常量数组声明
Symbol* create_const_def(std::string name,Expression* exp);
Symbol* create_var_def(std::string name,std::vector<int>* idxs);
Symbol* create_var_def(std::string name,std::vector<int>* idxs,Expression* exp);
LLVMList* create_var_decl(int btype,std::vector<Symbol*>* syms);
LLVMList* create_func_def(int btype,std::string name,std::vector<Symbol*>* syms,LLVMList* llvmlist);
Symbol* create_param_nonarray(int btype,std::string name);
Symbol* create_param_array(int btype,std::string name,std::vector<int>* dims);
dataType intToDataType(int btype);
LLVMList* create_continue_stmt();
LLVMList* create_break_stmt();
LLVMList* assign_array_item(Expression* LVal,Expression* exp);
void end_parser();
void begin_parser();
void create_var_init_list(Expression* exp);
void create_var_init_list(Expression* exp1,Expression* exp2);
void reduce_var_init_list(Expression* exp);
