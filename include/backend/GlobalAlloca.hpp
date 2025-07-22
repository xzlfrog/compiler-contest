#pragma once

#include "../llvm.hpp"
#include "../sym.hpp"
#include "../data.hpp"
#include "../sym.hpp"

#include "../GlobalOperations.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

// 假设这些类型/类已经在其他头文件中定义
enum class symbolType;

class BasicSymbol;
class ArraySymbol;

class GlobalAllocator {
public:
    // 构造与重置
    GlobalAllocator();
    void reset();

    // 全局变量分配
    void allocateGlobal(BasicSymbol* symbol);
    void allocateArray(ArraySymbol* arraySymbol);

    // 段与数据处理
    std::string determineSection(BasicSymbol* symbol) const;
    size_t getTypeSize(BasicSymbol* symbol) const;
    size_t getTypeSize(ArraySymbol* arraySymbol) const;
    std::string getAssemblyDirective(BasicSymbol* symbol) const;
    std::string getInitialValue(BasicSymbol* symbol) const;

    // 输出汇编代码
    void emitAssembly(std::ostream& out);
    std::string emitAssemblyToString();
    void emitArrayInitialization(std::ostream& out, ArraySymbol* array) const;

    // 打印调试信息
    void printAllocation(std::ostream& out = std::cerr) const;

private:
    // 存储全局变量，按段分类
    std::unordered_map<std::string, std::vector<BasicSymbol*>> globalVariables;

    // 存储全局数组
    std::vector<ArraySymbol*> globalArrays;
};