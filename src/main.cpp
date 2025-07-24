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
extern FILE* yyin;
extern std::ofstream outputArmFile;
std::queue<Expression*>assign_queue;
std::stack<int>array_initial;
int array_init_idx;

//compiler -S -o testcase.s testcase.sy
int main(int argc,char* argv[]){
    //if(argc != 2) printf("usage: %s filename\n", argv[0]);
    FILE* inputFile=fopen(argv[4],"r");
    if (!inputFile) {
        printf("Error: Unable to open input file %s\n", argv[4]);
        return 1;
    }

    std::string inputFileName ;
    std::string outputFileName ;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.length() >= 3 && arg.substr(arg.length() - 3) == ".sy") {
            inputFileName = arg;
        } else if (arg.length() >= 2 && arg.substr(arg.length() - 2) == ".s") {
            outputFileName = arg;
        }
    }
    // 如果没有指定输出文件，自动生成（在输入文件同目录下）
    if (outputFileName.empty()) {
        size_t dotPos = inputFileName.find_last_of('.');
        if (dotPos != std::string::npos) {
            outputFileName = inputFileName.substr(0, dotPos) + ".s";
        } else {
            outputFileName = inputFileName + ".s";
        }
    }
    
    outputArmFile.open(outputFileName, std::ios::out | std::ios::trunc);
    
    if (!outputArmFile.is_open()) {
        printf("Error: Unable to create output file %s\n", outputFileName.c_str ());
        return 1;
    }
    
    yyin = inputFile;
    begin_parser();
    yyparse();
    out_arm(outputFileName,module_list);

    return 0;
}
