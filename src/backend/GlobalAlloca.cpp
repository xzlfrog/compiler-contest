#include "../../include/backend/GlobalAlloca.hpp"
#include <ostream>
#include <iostream>
#include <sstream>

size_t GlobalAllocator::getTypeSize(dataType dtype) const{
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

size_t GlobalAllocator::getArrayTypeSize(dataType dtype,std::vector<int>& dims) const {
    size_t size = 1;
    for (int dim : dims) {
        size *= dim;
    }
    switch(dtype) {
        case i32: return size * 4;
        case i64: return size * 8;
        case f32: return size * 4;
        case f64: return size * 8;
        default: throw std::runtime_error("Unsupported array data type");
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

void GlobalAllocator::allocateFunc(std::string func_name){
    this->func.push_back(func_name);
}

void GlobalAllocator::allocateConstantNonArray(ConstantNonArrayVarDefination* CNAVD){
    std::string dest_str = (CNAVD->dest_sym->getName());
     
    std::vector<Data*> value_set;
    Data* res = CNAVD->getSrcSymbol()->data;
    value_set.push_back(res);
    this->rodata[dest_str] = value_set;
}

void GlobalAllocator::allocateGlobalNonArray(GlobalNonArrayVarDefination* GNAVD){
    std::string dest_str = (GNAVD->dest_sym->getName());
    std::string value ;
    if(GNAVD->getPointedType()==dataType::f32){
        switch (GNAVD->dest_sym->pointedData->getInitMode())
    {
    case initializer::zeroinitializer:
        value = "\t.float\t0";
        this->data[dest_str] = value;
        break;
    case initializer::undef:
        value = "\t.space\t" + std::to_string(this->getTypeSize(GNAVD->getPointedType()));
        this->bss[dest_str] = value;
        break;
    case initializer::assignment:
        value = "\t.float\t" + getSymOut(GNAVD->src_sym);
        this->data[dest_str] = value;
        break;
    default:
        throw std::runtime_error("the global variable initializer is wrong");
        break;
    }
    }else{
        switch (GNAVD->dest_sym->pointedData->getInitMode())
    {
    case initializer::zeroinitializer:
        value = "\t.word\t0";
        this->data[dest_str] = value;
        break;
    case initializer::undef:
        value = "\t.space\t" + std::to_string(this->getTypeSize(GNAVD->getPointedType()));
        this->bss[dest_str] = value;
        break;
    case initializer::assignment:
        value = "\t.word\t" + getSymOut(GNAVD->src_sym);
        this->data[dest_str] = value;
        break;
    default:
        throw std::runtime_error("the global variable initializer is wrong");
        break;
    }
    }
}

void GlobalAllocator::allocateConstantArray(ConstantArrayVarDefination* CAVD){
    std::string dest_str = CAVD->dest_sym->getName();
    std::vector<Data*> value_set;
    for(auto value : CAVD->getInitializedData()){
    Data* res = value.second;
    value_set.push_back(res);
    }
    this->rodata[dest_str] = value_set;
}

//这个没写
void GlobalAllocator::allocateGlobalArray(GlobalArrayVarDefination* GAVD){
    std::string dest_str = (GAVD->dest_sym->getName());
    std::string value;
    if(GAVD->getArrayType()==dataType::f32){
        value = "\n\t.float\t";
    }else{
        value = "\n\t.word\t";
    }
    value += this->getArrayValue(GAVD->getInitializedData(),GAVD->getDimensions());
    this->data[dest_str] = value;
}

//默认space为4 硬编码了！！！
std::string GlobalAllocator::getArrayValue(const std::vector<std::pair<std::vector<int>,Data*>>& value_sets, const std::vector<int>& dims){
    int totoal_size = 1;
    std::string res = "";
    for(auto dim: dims){
        totoal_size *= dim; 
    }
    int initialed_value_count = 0;
    for (const auto& pair : value_sets) {
        if (pair.second) {
            // 使用 pair.second
            res += my_to_string(pair.second);
            res += ", ";
            initialed_value_count++;
        }
    }
    // 移除最后的 ", "
    if (!res.empty() && res.length() >= 2) {
        res = res.substr(0, res.length() - 2);
    }
    if(initialed_value_count<totoal_size){
        int uninitialed_size = 4 ; //可能是巨大的隐患
        uninitialed_size *= (totoal_size - initialed_value_count);
        res += "\n";
        res += "\t.space\t";
        res += std::to_string(uninitialed_size);
    }

    return res;
}

void GlobalAllocator::emitAssembly(std::ostream& out){
    if (!this->data.empty()){
        for (auto varname : this->data) {
            std::string varnametmp = varname.first;
            varnametmp = varnametmp.substr(1);
            out << "\t.global\t" << varnametmp << "\n";       
        }
    }
    if (!this->bss.empty()){
        for (auto varname : this->bss) {
            std::string varnametmp = varname.first;
            varnametmp = varnametmp.substr(1);
            out << "\t.global\t" << varnametmp << "\n";        
        }
    }
    if (!this->rodata.empty()){
        for (auto varname : this->rodata) {
            std::string varnametmp = varname.first;
            varnametmp = varnametmp.substr(1);
            out << "\t.global\t" << varnametmp << "\n";         
        }
    }
    if (!this->func.empty()){
        for (auto varname : func) {
            out << "\t.global\t" << varname << "\n";       
        }
    }
    // .data段
    if (!this->data.empty()) {
        out << "\n\t.section .data\n.align\t4\n";
        for (auto varname : this->data) {
            std::string varnametmp = varname.first;
            varnametmp = varnametmp.substr(1);  
            out << varnametmp << ":\t";
            out << varname.second <<"\n";       
        }
    }
    
    // .bss段
    if (!this->bss.empty()) {
        out << "\n\t.section .bss\n.align\t4\n";
        for (auto varname : this->bss) {
            std::string varnametmp = varname.first;
            varnametmp = varnametmp.substr(1);  
            out << varnametmp << ":\t";
            out << varname.second <<"\n";       
        }
    }
    
    // .rodata段
    if (!this->rodata.empty()) {
        out << "\n\t.section .rodata\n.align\t4\n";
        for (auto varname : this->rodata) {
            std::string varnametmp = varname.first;
            varnametmp = varnametmp.substr(1);  
            if(varname.second.front()->getType() == dataType::i32){
                out << varnametmp << ":\t.word\t";
            }else{
                out << varnametmp << ":\t.float\t";
            }    
            auto data_value = varname.second.begin();
            out << my_to_string(*data_value);
            ++data_value;
            for (; data_value != varname.second.end(); ++data_value) {
                out << ", " << my_to_string(*data_value);
            }
            out << "\n" ; 
        }
    }
       out <<   "\n.text\n";
    
}

std::string GlobalAllocator::emitAssemblyToString() {
    std::ostringstream oss;
    GlobalAllocator::emitAssembly(oss); // 原来的函数，只是现在输出到ostringstream
    return oss.str();
}

bool GlobalAllocator::find_symbol(const std::string& name) const {
    return bss.count(name) || data.count(name) || rodata.count(name) || symbol_to_global.count(name);
}

//
void GlobalAllocator::addSymbolToGlobal(std::string sym_name, std::string global_name, int offset){
    this->symbol_to_global[sym_name] = std::make_pair(global_name, offset);
}

void GlobalAllocator::reset() {
    data.clear();
    rodata.clear();
    bss.clear();
    func.clear();
}

