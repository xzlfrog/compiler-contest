#pragma once

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../data.hpp"
#include "../sym.hpp"

#include "../GlobalOperations.hpp"
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>
#include <ostream>
#include <sstream>


// 假设这些类型/类已经在其他头文件中定义
enum class symbolType;

class BasicSymbol;
class ArraySymbol;

class GlobalAllocator {
public:
    // 构造与重置
    GlobalAllocator(){
        reset();
    };
    void reset();

    // 全局变量分配
    void allocateGlobalArray(GlobalArrayVarDefination* GAVD);
    void allocateGlobalNonArray(GlobalNonArrayVarDefination* GNAVD);
    void allocateConstantArray(ConstantArrayVarDefination* CAVD);
    void allocateConstantNonArray(ConstantNonArrayVarDefination* CNAVD);
    void allocateFunc(std::string func_name);
    bool find_symbol(const std::string& name) const;

    // 段与数据处理
    std::string getArrayValue(const std::vector<std::pair<std::vector<int>,Data*>>& value_set, const std::vector<int>& dims);
    size_t getTypeSize(dataType dtype) const;
    size_t getArrayTypeSize(dataType dtype, std::vector<int>& dims) const;

    std::string getInitialValue(BasicSymbol* symbol) const;

    // 输出汇编代码
    void emitAssembly(std::ostream& out);
    std::string emitAssemblyToString();

    //使用全局变量时候
    void addSymbolToGlobal(std::string sym_name, std::string global_name, int offset);

    std::map<std::string,std::pair<std::string,int>> symbol_to_global; //左边为变量名 右边为其对应的全局变量（及偏移 如果有数组）
    //代表某符号实际需读取全局变量
private:
    // 存储全局变量，按段分类
    std::map<std::string,std::string> data;//前名后值
    std::map<std::string,std::string> rodata;
    std::map<std::string,std::string> bss;
    std::vector<std::string> func;
    
};
