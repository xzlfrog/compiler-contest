#pragma once
#include"data.hpp"
#include"sym.hpp"

enum LLVMtype{
    llvm_fadd,
    llvm_fsub,
    llvm_fmul,
    llvm_fdiv,
    llvm_frem,
    add,//add
    sub,//subtract
    mul,//multiply
    udiv,//unsigned division
    sdiv,//signed division
    srem,//signed remainder
    urem,//unsigned remainder
    frem,
    logical_and,//logical and
    logical_or,//logical or
    logical_xor,//logical xor 非可以用异或来实现，y=x xor 1即可实现异或操作
    icmp_eq,//integer equal
    icmp_ne,//integer not equal
    icmp_ugt,//integer unsigned greater than
    icmp_uge,//integer unsigned greater than or equal
    icmp_ult,//integer unsigned less than
    icmp_ule,//integer unsigned less than or equal
    icmp_sgt,//integer signed greater than
    icmp_sge,//integer signed greater than or equal
    icmp_slt,//integer signed less than
    icmp_sle,// integer signed less than or equal
    fcmp_oeq,//float equal
    fcmp_ogt,//float greater than
    fcmp_oge,//float greater than or equal
    fcmp_olt,//float less than
    fcmp_ole,//float less than or equal
    fcmp_one,//float not equal
    fcmp_ord,// float ordered
    allocate_nonarray,//allocate memory
    allocate_array,//allocate memory
    load,//load
    store,//store
    getelementptr,//get element pointer
    label,//label
    br_unconditional,//unconditional branch
    br_conditional,//conditional branch
    indirectbr,//indirect branch,computed goto
    ret,//return
    call,//function call
    //llvm_switch,//switch
    phi,//phi node
    llvm_trunc,//截断整数位宽，如i64转i32
    zext,//zero extend
    sext,// sign extend
    bitcast,//等位宽类型间位级转换
    fptrunc,//截断浮点精度，如double转float
    fpext,//扩展浮点精度，如float转double
    fptoui,//浮点转无符号整数
    fptosi,//浮点转有符号整数
    uitofp,//无符号整数转浮点
    sitofp,//有符号整数转浮点
    ptrtoint,//指针转整数，如原来地址为0x1000的指针，转为整数后为4096
    inttoptr,//整数转指针,同上，反之
    //addrspacecast,//地址空间转换
    global_nonarray,//全局变量(非数组)定义
    global_array,//全局变量(数组)定义
    const_nonarray,//常量定义
    const_array,
    func_def,//函数定义
    func_decl,//函数声明
    llvm_neg,
    llvm_fneg,
    getelementptr_pointer_to_var
};

class LLVM {
    public : 
    LLVMtype llvmType;//llvm指令类型
    LLVM* next;//下一条llvm指令
    LLVM* prev;//上一条llvm指令

    //输出成文本
    virtual std::string out_str() const{
        return "";
    };

    //输出成文本
    virtual void out_arm_str();
    LLVMtype getLLVMType();//得到llvm指令类型
    virtual ~LLVM() = default;
};

class LLVMList{
public:
    LLVM* head=nullptr;
    LLVM* tail=nullptr;
    LLVMList* next=nullptr;
    LLVMList* prev=nullptr;
    
    void InsertTail(LLVM* llvm);//在尾节点插入
    void InsertHead(LLVM* llvm);//在头节点插入
    void InsertAfter(LLVM* pos,LLVM* llvm);//insert after a specific position
    void InsertBefore(LLVM* pos,LLVM* llvm);//insert before a specific position
    void Remove(LLVM* llvm); //remove a specific LLVM node

    void InsertTail(LLVMList* llvmlist);//在尾节点插入
    void InsertHead(LLVMList* llvmlist);//在头节点插入 

    LLVMList(){
        this->head=nullptr;
        this->tail=nullptr;
        this->next=nullptr;
        this->prev=nullptr;
    }
};

typedef LLVMList Module;

class ModuleList{
public:
    Module* head=nullptr;
    Module* tail=nullptr;
    
    void InsertTail(Module* module);//在尾节点插入
    void InsertHead(Module* module);//在头节点插入
    void InsertAfter(Module* pos,Module* module);//insert after a specific position
    void InsertBefore(Module* pos,Module* module);//insert before a specific position
    void Remove(Module* module); //remove a specific LLVM node
};

Module* LLVM_to_Module(LLVM* llvm);

BasicSymbol* copy(BasicSymbol* bs);