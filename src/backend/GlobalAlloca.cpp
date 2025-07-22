#include "../../include/backend/GlobalAlloca.hpp"
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

std::string GlobalAllocator::determineSection(BasicSymbol* symbol) const {
    if (symbol->getType() == constant_var || symbol->getType() == constant_nonvar) {
        return ".rodata";
    } else if (symbol->getType() == variable && symbol->data != nullptr) {
        return ".data";
    } else {
        return ".bss";
    }
}

std::string GlobalAllocator::determineSection(PointerSymbol* symbol) const {
    if (symbol->getType() == constant_var || symbol->getType() == constant_nonvar) {
        return ".rodata";
    } else if (symbol->getType() == variable && symbol->data != nullptr) {
        return ".data";
    } else {
        return ".bss";
    }
}

size_t GlobalAllocator::getTypeSize(BasicSymbol* symbol) const{
    dataType dtype = symbol->getDataType();
    switch(dtype) {
        case i32: return 4;
        case i64: return 8;
        case f32: return 4;
        case f64: return 8;
        case i1: return 1;
        case i8: return 1;
        case i16: return 2;
        default: throw std::runtime_error("Unsupported data type");
    }
}

size_t GlobalAllocator::getTypeSize(ArraySymbol* arraySymbol) const{
    size_t size = 1;
    for (int dim : arraySymbol->getDimensions()) {
        size *= dim;
    }
    dataType dtype = arraySymbol->getArrayType();
    switch(dtype) {
        case i32: return size * 4;
        case i64: return size * 8;
        case f32: return size * 4;
        case f64: return size * 8;
        default: throw std::runtime_error("Unsupported array data type");
    }
}

std::string GlobalAllocator::getAssemblyDirective(BasicSymbol* symbol) const {
    dataType dtype = symbol->getDataType();
    switch(dtype) {
        case i32: case f32: return ".word";
        case i64: case f64: return ".dword";
        case i1: case i8: return ".byte";
        case i16: return ".short";
        default: return ".word";
    }
}

std::string GlobalAllocator::getInitialValue(BasicSymbol* symbol) const {
    if (symbol->data == nullptr) return "0";
    
    switch(symbol->getDataType()) {
        case i32: return my_to_string(symbol->data);
        case i64: return my_to_string(symbol->data);
        case f32: 
            // 将float转换为IEEE754表示的整数
            return my_to_string(symbol->data);
        case f64:
            // 将double转换为IEEE754表示的整数
            return my_to_string(symbol->data);
        default: return "0";
    }
}

void GlobalAllocator::allocateGlobal(BasicSymbol* symbol) {
    std::string section = determineSection(symbol);
    globalVariables[section].push_back(symbol);
}

void GlobalAllocator::allocateGlobal(PointerSymbol* symbol){
    std::string section = determineSection(symbol);
    globalVariables2[section].push_back(symbol);
}

void GlobalAllocator::allocateArray(ArraySymbol* arraySymbol) {
    globalArrays.push_back(arraySymbol);
}

void GlobalAllocator::emitArrayInitialization(std::ostream& out, ArraySymbol* array) const {
    out << "\t.global " << array->getName() << "\n";
    out << "\t.align " << (getTypeSize(array) >= 8 ? 8 : 4) << "\n";
    out << array->getName() << ":\n";
    
    if (array->isInitialized() && array->initialedData != nullptr) {
        for (const auto& elem : array->initialedData->initializedData) {
            out << "\t.word " << my_to_string(elem.second) << "\n";
        }
    } else {
        size_t totalSize = 1;
        for (int dim : array->getDimensions()) {
            totalSize *= dim;
        }
        totalSize *= (array->getArrayType() == f32 || array->getArrayType() == i32) ? 4 : 8;
        out << "\t.space " << totalSize << "\n";
    }
}

void GlobalAllocator::emitAssembly(std::ostream& out){
    // .data段
    if (globalVariables.count(".data")) {
        out << "\t.section .data\n";
        for (BasicSymbol* var : globalVariables.at(".data")) {
            out << "\t.global " << var->getName() << "\n";
            out << "\t.align " << (getTypeSize(var) >= 8 ? 8 : 4) << "\n";
            out << var->getName() << ":\n";
            out << "\t" << getAssemblyDirective(var) << " " << getInitialValue(var) << "\n";
        }
    }
    
    // .bss段
    if (globalVariables.count(".bss")) {
        out << "\t.section .bss\n";
        for (BasicSymbol* var : globalVariables.at(".bss")) {
            out << "\t.global " << var->getName() << "\n";
            out << "\t.align " << (getTypeSize(var) >= 8 ? 8 : 4) << "\n";
            out << var->getName() << ":\n";
            out << "\t.space " << getTypeSize(var) << "\n";
        }
    }
    
    // .rodata段
    if (globalVariables.count(".rodata")) {
        out << "\t.section .rodata\n";
        for (BasicSymbol* var : globalVariables.at(".rodata")) {
            out << "\t.global " << var->getName() << "\n";
            out << "\t.align " << (getTypeSize(var) >= 8 ? 8 : 4) << "\n";
            out << var->getName() << ":\n";
            out << "\t" << getAssemblyDirective(var) << " " << getInitialValue(var) << "\n";
        }
    }
    
    // 处理数组
    if (!globalArrays.empty()) {
        out << "\t.section .data\n";
        for (ArraySymbol* array : globalArrays) {
            emitArrayInitialization(out, array);
        }
    }
}

std::string GlobalAllocator::emitAssemblyToString() {
    std::ostringstream oss;
    GlobalAllocator::emitAssembly(oss); // 原来的函数，只是现在输出到ostringstream
    return oss.str();
}

void GlobalAllocator::reset() {
    globalVariables.clear();
    globalArrays.clear();
}

void GlobalAllocator::printAllocation(std::ostream& out) const {
    out << "Global Variables Allocation:\n";
    
    for (const auto& section : globalVariables) {
        out << section.first << " section:\n";
        for (BasicSymbol* var : section.second) {
            out << "\t" << var->getName() << ": " 
                << (var->getType() == constant_var ? "const " : "")
                << var->getDataType() << " = " 
                << getInitialValue(var) << " (" 
                << getTypeSize(var) << " bytes)\n";
        }
    }
    
    out << "Global Arrays:\n";
    for (ArraySymbol* array : globalArrays) {
        out << "\t" << array->getName() << ": " << array->getArrayType() << "[";
        for (int dim : array->getDimensions()) {
            out << dim << ",";
        }
        out << "] (" << (array->isInitialized() ? "initialized" : "uninitialized") << ")\n";
    }
}
