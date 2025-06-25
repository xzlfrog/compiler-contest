#pragma once

#include"sym.hpp"
#include"llvm.hpp"


void checkType(dataType type1,dataType type2);//类型检查在设置操作数的时候进行，不需要在yacc文件中使用
void initial_program();//初始化程序
std::string generate_variable_name();//生成一个临时变量的名称
LabelSymbol* get_tmp_label();//生成一个临时标签
int getDataSize(dataType type);//通过数据类型得到数据大小
std::string DataTypeToString(dataType type);//从数据类型转化为可以输出的字符串