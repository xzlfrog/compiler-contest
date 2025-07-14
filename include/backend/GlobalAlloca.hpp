#pragma once

#include "../llvm.hpp"
#include "../sym.hpp"

#include "../GlobalOperations.hpp"
#include <string>
#include <map>

class GlobalAllocator {
public:
    // 初始化全局变量存储段（.data/.bss/.rodata）
    void initGlobalSection();

    //获取全局变量或常量的名称
    std::string getSymbolName(Symbol* symbol);

    // 获取未定义的全局变量的偏移
    // 返回值为偏移量，单位为字节
    int getGlobalOffset(Symbol* symbol);

    //浮点数转换为IEEE 754格式
    std::string float_to_ieee754(float f);
    
    // 分配一个全局变量或常量
    void allocateGlobal(Symbol* symbol);
    /* 涵姐这里可以写三个函数 初始化的全局 未初始化的全局 常量*/

    // 输出全局数据段到汇编文件
    void outputGlobals(std::ostream &out);
};
