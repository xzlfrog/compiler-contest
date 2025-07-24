#include "../../include/backend/RegAlloca.hpp"
//#include "../../include/backend/StaAlloca.hpp"
/*
有变量操作时 
判断是否满了？
否 然后分配

是 后续有用 保存到栈帧 否则直接载入

话说回来 
1.遇到全局怎么办 直接算常数
2.两个常数运算？ 直接合并！
*/
/*
// 检查寄存器是否已被使用
bool RegisterAllocator::isRegisterUsed(Symbol* symbol) const{
    auto it = var_to_reg.find(symbol);
    return it != var_to_reg.end() && Registers[it->second] != nullptr;
}

// 检查是否所有寄存器都已被使用
bool RegisterAllocator::isAllRegistersUsed() const{
    for (const auto& reg : Registers) {
        if (reg == nullptr) {
            return false; // 只要有一个寄存器是空闲的，就返回false
        }
    }
    return true; // 所有寄存器都被使用了
}

// 释放寄存器（用于临时值）
void RegisterAllocator::freeRegister(std::string reg_name){
    size_t index = std::stoi(reg_name.substr(1)); // 获取寄存器索引
    if (index < Registers.size() && Registers[index] != nullptr) {
        var_to_reg.erase(Registers[index]); // 从映射中删除变量
        Registers[index] = nullptr; // 释放寄存器
    } else {
        throw std::runtime_error("Register " + reg_name + " is not allocated or invalid");
    }
}

// 保存调用前需要保留的寄存器（calle-saved）
void RegisterAllocator::saveRegisters(std::ostream &out){}

// 恢复调用后需恢复的寄存器
void RegisterAllocator::restoreRegisters(std::ostream &out){}

std::string XRegAllocator::getFirstFreeRegister() const {
    for (size_t i = 0; i < Registers.size(); ++i) {
        if (Registers[i] == nullptr) {
            return "X" + std::to_string(i); // 返回第一个空闲寄存器的名称
        }
    }
    throw std::runtime_error("No free registers available");
}

std::string XRegAllocator::allocateSpace(Symbol* symbol) {
    std::string reg = getFirstFreeRegister();
    size_t index = std::stoi(reg.substr(1)); // 获取寄存器索引
    Registers[index] = symbol; // 分配寄存器
    var_to_reg[symbol] = index; // 更新映射
    return reg;
}

std::string XRegAllocator::getRegister(Symbol* symbol) const {
    auto it = var_to_reg.find(symbol);
    if (it != var_to_reg.end()) {
        size_t index = it->second;
        return "X" + std::to_string(index); // 返回寄存器名称
    }
    return ""; // 如果没有分配寄存器，返回空字符串
}

std::string SRegAllocator::getFirstFreeRegister() const {
    for (size_t i = 0; i < Registers.size(); ++i) {
        if (Registers[i] == nullptr) {
            return "S" + std::to_string(i); // 返回第一个空闲寄存器的名称
        }
    }
    throw std::runtime_error("No free registers available");
}

std::string SRegAllocator::allocateSpace(Symbol* symbol) {
    std::string reg = getFirstFreeRegister();
    size_t index = std::stoi(reg.substr(1)); // 获取寄存器索引
    Registers[index] = symbol; // 分配寄存器
    var_to_reg[symbol] = index; // 更新映射
    return reg;
}

std::string SRegAllocator::getRegister(Symbol* symbol) const {
    auto it = var_to_reg.find(symbol);
    if (it != var_to_reg.end()) {
        size_t index = it->second;
        return "S" + std::to_string(index); // 返回寄存器名称
    }
    return ""; // 如果没有分配寄存器，返回空字符串
}


std::string SRegAllocator::accessVariable(Symbol* symbol) {
    // 如果变量已存在，更新LRU位置
    if (SRegAllocator::isRegisterUsed(symbol)) {
        std::string regName = SRegAllocator::getRegister(symbol);
        lru_list.remove(regName);
        lru_list.push_front(regName);
        return regName;
    }
    
    // 新变量分配
    if (Registers.size() == VREG_SIZE) {
        // 需要替换LRU变量
        std::string lru_var = lru_list.back();
        lru_list.pop_back();
        
        // 将LRU变量溢出到栈
        //spillToStack(lru_var);
        
        // 获取释放的寄存器
        SRegAllocator::freeRegister(lru_var);
    }

    //有空闲寄存器，直接分配
    std::string regName = SRegAllocator::allocateSpace(symbol);

    lru_list.push_front(regName);

    return regName;
}

std::string XRegAllocator::accessVariable(Symbol* symbol) {
    // 如果变量已存在，更新LRU位置
    if (XRegAllocator::isRegisterUsed(symbol)) {
        std::string regName = XRegAllocator::getRegister(symbol);
        lru_list.remove(regName);
        lru_list.push_front(regName);
        return regName;
    }
    
    // 新变量分配
    if (Registers.size() == XREG_SIZE) {
        // 需要替换LRU变量
        std::string lru_var = lru_list.back();
        lru_list.pop_back();
        
        // 将LRU变量溢出到栈
        //spillToStack(lru_var);
        
        // 获取释放的寄存器
        XRegAllocator::freeRegister(lru_var);
    }

    //有空闲寄存器，直接分配
    std::string regName = XRegAllocator::allocateSpace(symbol);

    lru_list.push_front(regName);

    // if(StackAllocator::hasVariable(symbol->getName())) {
    //     StackAllocator::printAllocation(std::cout);
    // }
    /*不行 这块得放到外面 X 可以放在这 直接在此处输出而不是std::string
    翻译赋值语句时 先判断是否在栈帧上 是则加载到寄存器 */
    //return regName;
//}