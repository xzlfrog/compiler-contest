#include "../../include/backend/RegAlloca.hpp"

/*
有变量操作时 
判断是否满了？
否 然后分配

是 后续有用 保存到栈帧 否则直接载入

话说回来 
1.遇到全局怎么办 直接算常数
2.两个常数运算？ 直接合并！
*/

// 检查寄存器是否已被使用

bool RegisterAllocator::isRegisterUsed(std::string symbol) const{
    auto it = this->var_to_reg.find(symbol);

    // 检查映射中是否存在symbol，并且寄存器数组中对应位置的指针是symbol
    return it != this->var_to_reg.end() && this->Registers[it->second] == symbol && it->second < this->Registers.size(); 
    // 确保索引在范围内
}

// 检查是否所有寄存器都已被使用
bool RegisterAllocator::isAllRegistersUsed() const{
    for (const auto& reg : this->Registers) {
        if (reg.empty()) {
            return false; // 只要有一个寄存器是空闲的，就返回false
        }
    }
    return true; // 所有寄存器都被使用了
}

// 释放寄存器（用于临时值）
void RegisterAllocator::freeRegister(std::string reg_name){
    if(reg_name==""){
        return;
    }

    size_t index = std::stoi(reg_name.substr(1)); // 获取寄存器索引
    
     
    if (index < 32 ) {
        if(this->var_to_reg.count(Registers[index])){
            this->var_to_reg.erase(Registers[index]); // 从映射中删除变量
        }
        this->Registers[index] = ""; // 释放寄存器
    } else {
        throw std::runtime_error("Register " + reg_name + " is not invalid");
    }
}

void XRegAllocator::reset() {
    this->lru_list.clear();
    //this->Registers.clear();
    this->Registers=std::vector<std::string>(32);
    this->var_to_reg.clear();
    this->current_reg_offset1 = 0; // 当前偏移量 0-7
    this->current_reg_offset2 = 9; // 当前偏移量 9-15
    this->current_reg_offset3 = 19; // 当前偏移量 19-28 暂时不用3 因为未区分临时变量
    
}

void DRegAllocator::reset() {
    this->lru_list.clear();
    //this->Registers.clear();
    this->Registers=std::vector<std::string>(32);
    this->var_to_reg.clear();
    this->current_reg_offset1 = 0; // 当前偏移量 0-7
    this->current_reg_offset2 = 8;
}

void XRegAllocator::allocateParamSpace(std::string symbol) {

    if(this->lru_list.size() < 8){

        this->var_to_reg[symbol] = this->current_reg_offset1; // 更新
        this->Registers[current_reg_offset1] = symbol;
        this->lru_list_param.push_back(current_reg_offset1);
        this->current_reg_offset1++; // 更新偏移量

        return;
    }else{

        int new_reg = this->lru_list.front();
        this->lru_list_param.pop_front();
        this->lru_list_param.push_back(new_reg);
        this->spillToStack(Registers[new_reg]);
        this->var_to_reg.erase(Registers[new_reg]);

        this->Registers[new_reg] = symbol;
        this->var_to_reg[symbol] = new_reg;
    }
    
}

void XRegAllocator::allocateOtherSpace(std::string symbol) {
    if(this->lru_list.size() < 17){

        this->var_to_reg[symbol] = this->current_reg_offset2; // 更新
        this->Registers[this->current_reg_offset2] = symbol;
        this->lru_list.push_back(this->current_reg_offset2);
        this->current_reg_offset2++; // 更新偏移量
        if(this->current_reg_offset2 == 16){
            this->current_reg_offset2 = 19;
        }
        return;
    }else{

        int new_reg = this->lru_list.front();
        this->lru_list.pop_front();
        this->lru_list.push_back(new_reg);
        this->spillToStack(this->Registers[new_reg]);
        this->var_to_reg.erase(this->Registers[new_reg]);

        this->Registers[new_reg] = symbol;
        this->var_to_reg[symbol] = new_reg;
        
    }

}

std::string XRegAllocator::getRegister(std::string symbol) const {
    auto it = this->var_to_reg.find(symbol);
    if (it != this->var_to_reg.end()) {
        size_t index = it->second;
        return "W" + std::to_string(index); // 返回寄存器名称
    }
    return ""; // 如果没有分配寄存器，返回空字符串
}

std::string XRegAllocator::getAddress(std::string symbol) const {
    auto it = this->var_to_reg.find(symbol);
    if (it != this->var_to_reg.end()) {
        size_t index = it->second;
        return "X" + std::to_string(index); // 返回寄存器名称
    }
    return ""; // 如果没有分配寄存器，返回空字符串
}

std::string XRegAllocator::accessVariable(std::string symbol){
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    auto it = this->var_to_reg.find(symbol);
    bool is_in_reg = true;
    if (it == this->var_to_reg.end()) {
        is_in_reg = false;
        this->allocateOtherSpace(symbol); // 如果没有分配寄存器，则分配
        it = this->var_to_reg.find(symbol); // 重新查找
    }else{
        int target_reg = it->second;  // 要删除的寄存器编号

        for (auto iter = this->lru_list.begin(); iter != this->lru_list.end(); ) {
            if (*iter == target_reg) {
                iter = this->lru_list.erase(iter);  // erase 返回下一个有效迭代器
                break;  // 找到并删除后退出（假设只出现一次）
            } else {
                ++iter;
            }
        }
        this->lru_list.push_back(it->second);     // 插入尾部
    }

    bool is_in_stack = stackAllocator.hasVariable(symbol);
    if (is_in_stack && !is_in_reg) {
        this->promoteToRegister(symbol); // 如果在栈中，先提升到寄存器
        return this->getRegister(symbol); // 返回寄存器名称
    }

    return "W" + std::to_string(it->second); // 返回寄存器名称  
}

std::string XRegAllocator::accessAddress(std::string symbol){
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    auto it = this->var_to_reg.find(symbol);
    bool is_in_reg = true;

    if (it == this->var_to_reg.end()) {
        is_in_reg = false;
        this->allocateOtherSpace(symbol); // 如果没有分配寄存器，则分配
        it = this->var_to_reg.find(symbol); // 重新查找
    }else{
        int target_reg = it->second;  // 要删除的寄存器编号

        for (auto iter = this->lru_list.begin(); iter != this->lru_list.end(); ) {
            if (*iter == target_reg) {
                iter = this->lru_list.erase(iter);  // erase 返回下一个有效迭代器
                break;  // 找到并删除后退出（假设只出现一次）
            } else {
                ++iter;
            }
        }
        this->lru_list.push_back(it->second);     // 插入尾部
    }

        return "X" + std::to_string(it->second); // 返回寄存器名称  
}

std::string XRegAllocator::accessParam(std::string symbol){
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    auto it = this->var_to_reg.find(symbol);
    bool is_in_reg = true;
    if (it == this->var_to_reg.end()) {
        is_in_reg = false;
        this->allocateParamSpace(symbol); // 如果没有分配寄存器，则分配
        it = this->var_to_reg.find(symbol); // 重新查找
    }else{
        int target_reg = it->second;  // 要删除的寄存器编号

        for (auto iter = this->lru_list.begin(); iter != this->lru_list.end(); ) {
            if (*iter == target_reg) {
                iter = this->lru_list.erase(iter);  // erase 返回下一个有效迭代器
                break;  // 找到并删除后退出（假设只出现一次）
            } else {
                ++iter;
            }
        }
        this->lru_list.push_back(it->second);     // 插入尾部
    }

    bool is_in_stack = stackAllocator.hasVariable(symbol);
    if (is_in_stack && !is_in_reg) {
        this->promoteToRegister(symbol); // 如果在栈中，先提升到寄存器
        return this->getRegister(symbol); // 返回寄存器名称
    }
    this->Registers[it->second] = symbol; // 更新寄存器
        return "W" + std::to_string(it->second); // 返回寄存器名称
    
}

std::string XRegAllocator::accessParamAddress(std::string symbol){
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    auto it = this->var_to_reg.find(symbol);
    bool is_in_reg = true;

    if (it == this->var_to_reg.end()) {
        is_in_reg = false;
        this->allocateParamSpace(symbol); // 如果没有分配寄存器，则分配
        it = this->var_to_reg.find(symbol); // 重新查找
    }else{
        int target_reg = it->second;  // 要删除的寄存器编号

        for (auto iter = this->lru_list.begin(); iter != this->lru_list.end(); ) {
            if (*iter == target_reg) {
                iter = this->lru_list.erase(iter);  // erase 返回下一个有效迭代器
                break;  // 找到并删除后退出（假设只出现一次）
            } else {
                ++iter;
            }
        }
        this->lru_list.push_back(it->second);     // 插入尾部
    }

        return "X" + std::to_string(it->second); // 返回寄存器名称 
    
}

void DRegAllocator::allocateParamSpace(std::string symbol) {
    
    if(this->lru_list.size() < 8){

        this->var_to_reg[symbol] = this->current_reg_offset1; // 更新
        this->Registers[current_reg_offset1] = symbol;
        this->lru_list_param.push_back(current_reg_offset1);
        this->current_reg_offset1++; // 更新偏移量

        return;
    }else{

        int new_reg = this->lru_list.front();
        this->lru_list_param.pop_front();
        this->lru_list_param.push_back(new_reg);
        this->spillToStack(Registers[new_reg]);
        this->var_to_reg.erase(Registers[new_reg]);

        this->Registers[new_reg] = symbol;
        this->var_to_reg[symbol] = new_reg;
    }
    
}

void DRegAllocator::allocateOtherSpace(std::string symbol) {
    if(this->lru_list.size() < 24){

        this->var_to_reg[symbol] = this->current_reg_offset2; // 更新
        this->Registers[this->current_reg_offset2] = symbol;
        this->lru_list.push_back(this->current_reg_offset2);
        this->current_reg_offset2++; // 更新偏移量

        return;
    }else{

        int new_reg = this->lru_list.front();
        this->lru_list.pop_front();
        this->lru_list.push_back(new_reg);
        this->spillToStack(this->Registers[new_reg]);
        this->var_to_reg.erase(this->Registers[new_reg]);

        this->Registers[new_reg] = symbol;
        this->var_to_reg[symbol] = new_reg;
    }
}

std::string DRegAllocator::getRegister(std::string symbol) const {
    auto it = this->var_to_reg.find(symbol);
    if (it != this->var_to_reg.end()) {
        size_t index = it->second;
        return "S" + std::to_string(index); // 返回寄存器名称
    }
    return ""; // 如果没有分配寄存器，返回空字符串
}

std::string DRegAllocator::accessVariable(std::string symbol){
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    auto it = this->var_to_reg.find(symbol);
    bool is_in_reg = true;
    if (it == this->var_to_reg.end()) {
        is_in_reg = false;
        this->allocateOtherSpace(symbol); // 如果没有分配寄存器，则分配
        it = this->var_to_reg.find(symbol); // 重新查找
    }else{
        int target_reg = it->second;  // 要删除的寄存器编号

        for (auto iter = this->lru_list.begin(); iter != this->lru_list.end(); ) {
            if (*iter == target_reg) {
                iter = this->lru_list.erase(iter);  // erase 返回下一个有效迭代器
                break;  // 找到并删除后退出（假设只出现一次）
            } else {
                ++iter;
            }
        }
        this->lru_list.push_back(it->second);     // 插入尾部
    }

    bool is_in_stack = stackAllocator.hasVariable(symbol);
    if (is_in_stack && !is_in_reg) {
        this->promoteToRegister(symbol); // 如果在栈中，先提升到寄存器
        return this->getRegister(symbol); // 返回寄存器名称
    }

    return "S" + std::to_string(it->second); // 返回寄存器名称  

}

std::string DRegAllocator::accessParam(std::string symbol){
    StackAllocator& stackAllocator = StackAllocator::getInstance();
    auto it = this->var_to_reg.find(symbol);
    bool is_in_reg = true;
    if (it == this->var_to_reg.end()) {
        is_in_reg = false;
        this->allocateParamSpace(symbol); // 如果没有分配寄存器，则分配
        it = this->var_to_reg.find(symbol); // 重新查找
    }else{
        int target_reg = it->second;  // 要删除的寄存器编号

        for (auto iter = this->lru_list.begin(); iter != this->lru_list.end(); ) {
            if (*iter == target_reg) {
                iter = this->lru_list.erase(iter);  // erase 返回下一个有效迭代器
                break;  // 找到并删除后退出（假设只出现一次）
            } else {
                ++iter;
            }
        }
        this->lru_list.push_back(it->second);     // 插入尾部
    }
}