#include"../include/frontend/frontendTool.hpp"
#include"frontend/sysy.y.hpp"
#include"../include/backend/out_arm.hpp"
#include<stdio.h>

int scope;
ModuleList* module_list;
std::vector<std::unordered_map<std::string,int>> variable_rename_table;
std::vector<std::unordered_map<std::string,Symbol*>> variable_table;
std::unordered_map<std::string,FuncSymbol*>func_table;
std::unordered_map<std::string,BasicSymbol*> pointer_to_var;
std::stack<LabelSymbol*> break_st,continue_st;
extern FILE* yyin,* outputArmFile;
std::queue<Expression*>assign_queue;
std::stack<int>array_initial;
int array_init_idx;

//compiler -S -o testcase.s testcase.sy
int main(int argc,char* argv[]){
    if(argc != 2) printf("usage: %s filename\n", argv[0]);
    FILE* inputFile=fopen(argv[5],"r");
    std::string inputFileName = argv[5];
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of('.')) + ".s";
    outputArmFile = fopen(outputFileName.c_str(), "w");
    if (!outputArmFile) {
        printf("Error: Unable to create output file %s\n", outputFileName.c_str());
        return 1;
    }
    
    yyin = inputFile;
    begin_parser();
    yyparse();
    out_arm(outputArmFile,module_list);

    return 0;
}
