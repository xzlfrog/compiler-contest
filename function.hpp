#include"sym.hpp"
#include"llvm.hpp"

Symbol* local_sym_table;
Symbol* global_sym_table;

int tmp_symbol_count=0;

void checkType(dataType type1,dataType type2);//类型检查在设置操作数的时候进行，不需要在yacc文件中使用

void initial_program();

std::string generate_variable_name();

Symbol* get_tmp_symbol(dataType type,int scope);