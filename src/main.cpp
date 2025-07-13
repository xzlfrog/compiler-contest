#include"../include/frontend/frontendTool.hpp"
#include"frontend/sysy.y.hpp"
#include<stdio.h>

int scope;
ModuleList* module_list;
std::vector<std::unordered_map<std::string,int>> variable_rename_table;
std::vector<std::unordered_map<std::string,Symbol*>> variable_table;
std::unordered_map<std::string,FuncSymbol*>func_table;
std::unordered_map<std::string,BasicSymbol*> pointer_to_var;
std::stack<LabelSymbol*> break_st,continue_st;
extern FILE* yyin;
std::queue<Expression*>assign_queue;
std::stack<int>array_initial;
int array_init_idx;


int main(int argc,char* argv[]){
    if(argc != 2) printf("usage: %s filename\n", argv[0]);
    FILE* inputFile=fopen(argv[1],"r");
    yyin=inputFile;
    begin_parser();
    yyparse();
    return 0;
}