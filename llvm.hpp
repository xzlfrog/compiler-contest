#include"sym.hpp"

enum LLVMtype{
    add,//add
    sub,//subtract
    mul,//multiply
    udiv,//unsigned division
    sdiv,//unsigned division
    srem,//unsigned remainder
    urem,//unsigned remainder
    logical_and,//logical and
    logical_or,//logical or
    logical_xor,//logical xor
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
    alloca,//allocate memory
    load,//load
    store,//store
    getelementptr,//get element pointer
    br_unconditional,//unconditional branch
    br_conditional,//conditional branch
    indirectbr,//indirect branch,computed goto
    ret,//return
    call,//function call
    llvm_switch,//switch
    phi,//phi node
    trunc,//截断整数位宽，如i64转i32
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
    addrspacecast,//地址空间转换
};

class LLVM {
    public : 
    LLVMtype llvmType;
    dataType ty;//[i1,i8,i16,i32,i64,f32,f64]
    LLVM* next;
    LLVM* prev;

    virtual void setLLVMType(LLVMtype type);

    virtual std::string out_str() const;
};

class LLVMList{
public:
    LLVM* head;
    LLVM* tail;
    
    void InsertTail(LLVM* llvm);

    void InsertHead(LLVM* llvm);

    void InsertAfter(LLVM* pos,LLVM* llvm);//insert after a specific position

    void InsertBefore(LLVM* pos,LLVM* llvm);//insert before a specific position

    void Remove(LLVM* llvm); //remove a specific LLVM node
};