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

    // 段与数据处理
    std::string getArrayValue(const std::vector<std::pair<std::vector<int>,Data*>>& value_set, const std::vector<int>& dims);
    size_t getTypeSize(dataType dtype) const;
    size_t getArrayTypeSize(dataType dtype, std::vector<int>& dims) const;

    std::string getInitialValue(BasicSymbol* symbol) const;

    // 输出汇编代码
    void emitAssembly(std::ostream& out);
    std::string emitAssemblyToString();


private:
    // 存储全局变量，按段分类
    std::map<std::string,std::string> data;//前名后值
    std::map<std::string,std::string> rodata;
    std::map<std::string,std::string> bss;
    std::vector<std::string> func;
};