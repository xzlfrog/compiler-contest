#include"../include/TypeConversionOperations.hpp"

//TypeConversionOperation::
BasicSymbol* TypeConversionOperation::getSrcSymbol(){return this->src_sym;}
BasicSymbol* TypeConversionOperation::getDestSymbol(){return this->dest_sym;}
dataType TypeConversionOperation::getSrcType(){return this->src_sym->getDataType();}
dataType TypeConversionOperation::getDestType(){return this->dest_sym->getDataType();}

std::string TypeConversionOperation::out_str() const {
    // 获取源和目标类型的字符串表示
    std::string src_name = "%" + src_sym->name;   // 假设 BasicSymbol 有 name 成员
    std::string dest_name = "%" + dest_sym->name;

    // 获取源和目标数据类型
    dataType src_type = src_sym->getDataType();
    dataType dest_type = dest_sym->getDataType();

    // 根据类型匹配正确的 LLVM 转换指令
    std::string inst;

    if (src_type == i32 && dest_type == f32) {
        inst = "sitofp";  // 有符号整数转浮点
    } else if (src_type == f32 && dest_type == i32) {
        inst = "fptosi";  // 浮点转有符号整数
    } 
    // else if (src_type == INT && dest_type == DOUBLE) {
    //     inst = "sitofp";  // 同样使用 sitofp，LLVM 允许 i32 -> double
    // } else if (src_type == DOUBLE && dest_type == INT) {
    //     inst = "fptosi";  // double -> int
    // } else if (src_type == FLOAT && dest_type == DOUBLE) {
    //     inst = "fpext";   // 单精度浮点扩展为双精度
    // } else if (src_type == DOUBLE && dest_type == FLOAT) {
    //     inst = "fptrunc"; // 双精度截断为单精度
    // } else if (src_type == INT && dest_type == INT) {
    //     // 如果是不同位宽整数之间转换，需要判断是否扩展还是截断
    //     // 这里简化处理，假设目标比源大
    //     inst = "sext";    // 默认有符号扩展
    // } 
    else {
        // 不支持的类型转换
        throw std::runtime_error("Unsupported type conversion from " +
                             std::to_string(src_type) + " to " +
                             std::to_string(dest_type));
    }

    // 获取 LLVM 类型字符串
    std::string src_llvm_type = "";  // 可以写函数映射 dataType 到 LLVM 类型字符串
    std::string dest_llvm_type = "";

    if (src_type == i32) src_llvm_type = "i32";
    else if (src_type == f32) src_llvm_type = "f32";
    //else if (src_type == DOUBLE) src_llvm_type = "double";

    if (dest_type == i32) dest_llvm_type = "i32";
    else if (dest_type == f32) dest_llvm_type = "f32";
    //else if (dest_type == DOUBLE) dest_llvm_type = "double";

    // 构造 LLVM IR 指令字符串
    return dest_name + " = " + inst + " " + src_llvm_type + " " + src_name +
           " to " + dest_llvm_type;
}

// std::string typeToString(dataType t) {
//     switch (t) {
//         case i32:     return "i32";
//         case f32:   return "f32";

//     }
// }