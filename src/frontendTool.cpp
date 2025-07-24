#include"../include/frontend/frontendTool.hpp"
#include"../include/exp.hpp"

/* prepare*/
/*
#define GLOBAL_SCOPE 0

dataType getTypeFromString(const char* typeStr) {
    if (strcmp(typeStr, "int") == 0) {
        return dataType::i32;
    } else if (strcmp(typeStr, "float") == 0) {
        return dataType::f32;
    } else {
        // 处理未知类型的错误
        fprintf(stderr, "error in [frontendTool.cpp]\n不支持的数据类型哦: %s\n", typeStr);
        exit(1);
    }
}

Data* expShorten(Expression* exp) {
    // 这里可以根据需要对表达式进行简化
    // 例如，如果是常量表达式，可以直接返回其值
    exp->constFolding();
    return exp;
}

void* create_comp_unit(void* decl_or_func){
    moduleList = new ModuleList();

}

LLVM* create_const_decl(std::string type, std::string name) {
    dataType const_var_type = getTypeFromString(type);
    Symbol* const_var_sym = symbolMap[name];

    const_var_sym->data->setType(const_var_type);
    return ;
}

Symbol* create_const_def(std::string name,Data* const_exp; std::vector<int>& dimensions, std::vector<std::pair<std::vector<int>,Data*>> initializedData) {
    
    int tmp_const_exp = const_exp->getValue();
    dimensions.insert(dimensions.begin(), tmp_const_exp);

    ArraySymbol* const_Array_sym = SymbolFactory::createArraySymbolWithScope(name, dimensions, scope, dataType::data_undefined);
    ArrayInitial* arrayInitial=new ArrayInitial();

    int size = dimensions.size();
    for(int i = 0; i < size; i++) {
        
    }
    // if (const_var_sym == nullptr) {
    //     fprintf(stderr, "error in [frontendTool.cpp]\n未定义的常量变量哦: %s\n", name.c_str());
    //     exit(1);
    // }  
    ConstantArrayVarDefination* res = LLVMfactory::createConstantArrayVarDefination(const_Array_sym);
    
    llvmList->LLVMList::Inserttail(res);
    return ;
}

LLVM* create_const_def(std::string name, Data* data) {
    ConstVarSymbol* const_dest_nonarray=SymbolFactory::createConstVarSymbolWithScope(name,0,createNonInitialedData(dataType::data_undefined));
    BasicSymbol * const_src_nonarray=SymbolFactory::createConstSymbol(data->getValue());
    LLVM* constnonarraydef=LLVMfactory::createConstantNonArrayVarDefination(const_dest_nonarray,const_src_nonarray);
    llvmList->LLVMList::Inserttail(constnonarraydef);
}

void* create_var_decl(string name, std::vector<int>& dimensions) {
    VarSymbol* var_sym = symbolMap[name];
    
    if(!dimensions.empty()) {
        // 如果有维度信息，创建数组变量
        ArraySymbol* array_sym = SymbolFactory::createArraySymbolWithScope(name, scope, var_sym->getDataType());
        if(scope == GLOBAL_SCOPE){
        AllocaArrayLLVM* alloca_array = LLVMfactory::createAllocaArrayLLVM(array_sym, dimensions);
        } else {
            AllocaArrayLLVM* alloca_array = LLVMfactory::createAllocaArrayLLVM(array_sym);
        }
        llvmList->InsertTail(alloca_array);
    } else {
        // 如果没有维度信息，创建非数组变量
        var_sym = SymbolFactory::createVarSymbolWithScope(name, scope);
        symbolMap[name] = var_sym;
        AllocaNonArrayLLVM* alloca_nonarray = LLVMfactory::createAllocaNonArrayLLVM(var_sym);
        llvmList->InsertTail(alloca_nonarray);
    }
}

void* create_var_decl(string name, std::vector<int>& dimensions, std::vector<std::pair<std::vector<int>,Data*>> initializedData) {
    
}


vector<int>* do_dimensions(Data* const_exp, std::vector<int>& dimensions){
    dimensions.insert(dimensions.begin(), const_exp->getValue());
    // 检查维度是否为正整数
    if (const_exp->getValue() <= 0) {
        fprintf(stderr, "error in [frontendTool.cpp]\n数组维度必须为正整数哦: %d\n", const_exp->getValue());
        exit(1);
    }
    return &dimensions;       
}

Expression* create_primary_IDENTIFIER(std::string id) {
    VarSymbol* var_sym = symbolMap[id];
    if (var_sym == nullptr) {
        fprintf(stderr, "error in [frontendTool.cpp]\n未定义的变量哦: %s\n", id);
        exit(1);
    }
    Expression* exp = new Expression;
    exp->sym = var_sym;
    exp->llvm = nullptr; 
    return exp;
}

Expression* create_primary_INTCONST(int value) {
    Data* i32_data = createData(i32, value);
    ConstSymbol* const_sym = SymbolFactory::createConstSymbolWithScope(i32_data, scope);
    Expression* exp = new Expression;
    exp->sym = const_sym;
    exp->llvm = nullptr; // 这里可以根据需要创建对应的LLVM表达式
    return exp;
}

Expression* create_primary_FLOATCONST(float value) {
    Data_f32* f32_data = createData(f32, value);
    ConstSymbol* const_sym = SymbolFactory::createConstSymbolWithScope(f32_data, scope);
    Expression* exp = new Expression;
    exp->sym = const_sym;
    exp->llvm = nullptr; // 这里可以根据需要创建对应的LLVM表达式
    return exp;
}

Expression* create_binary_expr(int op, Expression* a, Expression* b){
   if(a->sym->getDataType()!=b->sym->getDataType()){
    
   }
}

Expression* create_unary_expr(int op, Expression* exp){
    LLVMtype llvm_type;
    // 创建一个临时变量来存储结果
    Expression* Res = new Expression;
    dataType exp_type = exp->sym->getDataType();

    // 检查操作符和表达式类型是否匹配
    if(exp_type == dataType::i32){
        switch (op)
        {
        case '+':
            llvm_type = LLVMtype::add;
            break;
        case '-':
            llvm_type = LLVMtype::sub;
            break;
        case '!':
            llvm_type = LLVMtype::icmp_eq;
            break;
        default:
            fprintf(stderr, "error in [frontendTool.cpp]\n不支持的操作符: %d\n", op);
            exit(1);
        }
        Data* i32_zero = createData(i32,0);
        ConstSymbol* const_sym = SymbolFactory::createConstSymbolWithScope(&i32_data, scope);
        Res_type = dataType::i32; // 更新表达式类型为i32
    }
    else if(exp_type == dataType::f32){
        switch (op)
        {
        case '+':
            llvm_type = LLVMtype::llvm_fadd;
            break;
        case '-':
            llvm_type = LLVMtype::llvm_fsub;
            break;
        case '!':
            llvm_type = LLVMtype::fcmp_oeq;
            break;
        default:
            fprintf(stderr, "error in [frontendTool.cpp]\n不支持的操作符: %d\n", op);
            exit(1);
        }
        Data_f32* f32_zero = createData(f32,0.0f); // 创建一个f32类型的Data对象，初始值为0.0
        ConstSymbol* const_sym = SymbolFactory::createConstSymbolWithScope(&f32_data);
        Res_type = dataType::f32; // 更新表达式类型为f32
    } else {
        fprintf(stderr, "error in [frontendTool.cpp]\n不支持的表达式类型: %s\n", exp->sym->getDataType().toString().c_str());
        exit(1);
    }
    
    VarSymbol* tmpRes = SymbolFactory::createTmpVarSymbolWithScope(exp_type);
    Res->sym = tmpRes;

    ArithmeticOperationLLVM* operation = LLVMfactory::createBasicOperationLLVM(llvm_type, tmpRes, const_sym, exp->sym);
    Res->llvm = operation;

    LLVMList::InsertAfter(exp->llvm, operation);

    return Res;
}*/