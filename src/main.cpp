#include"../include/frontend/frontendTool.hpp"
#include"frontend/sysy.y.hpp"
#include"../include/backend/out_arm.hpp"
#include<stdio.h>
#include<filesystem>

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
std::vector<int>dim_array;
std::vector<int> array_init_idx;
int cnt_array_init;
dataType func_ret_type;
Symbol* sym_defining;
bool ssa_flag;
//std::stack<int>array_initial;

bool Make_llvm = true;//不输出

//compiler -S -o testcase.s testcase.sy
int main(int argc,char* argv[]){
    //if(argc != 2) printf("usage: %s filename\n", argv[0]);

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

    FILE* inputFile=fopen(inputFileName.c_str(),"r");
    if (!inputFile) {
        printf("Error: Unable to open input file %s\n", inputFileName.c_str());
        return 101;
    }

    // 如果未指定输出文件，自动生成：项目根目录下的 xxx.s
    if (outputFileName.empty()) {
        std::string filename = std::filesystem::path(inputFileName).filename().string();
        std::string stem = std::filesystem::path(inputFileName).stem().string();  // 去掉 .sy
        outputFileName = stem + ".s";  // 直接输出到当前目录（项目根目录）
    }
    
    outputArmFile.open(outputFileName, std::ios::out | std::ios::trunc);
    
    if (!outputArmFile.is_open()) {
        printf("Error: Unable to create output file %s\n", outputFileName.c_str ());
        return 102;
    }
    
    yyin = inputFile;
    begin_parser();
    yyparse();
    out_arm(outputFileName,module_list);

    return 0;
}
