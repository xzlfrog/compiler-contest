#include"../../include/frontend/frontendTool.hpp"
#include"../../include/exp.hpp"
#include<iostream>

extern std::vector<int> array_init_idx;
extern int cnt_array_init;
extern std::vector<int>dim_array;

bool isConst(Symbol* sym){
    if(sym->getType()==symType::constant_var||sym->getType()==symType::constant_nonvar){
        return true;
    }
    return false;
}

Expression* constFolding(constExpType type,Symbol* sym1,Symbol* sym2){
    if(isConst(sym1)&&isConst(sym2)){
        ConstExp* constExp=new ConstExp(type,sym1->data,sym2->data);
        Data* data=constExp->constFolding();
        BasicSymbol* sym=SymbolFactory::createConstSymbol(data);
        return new Expression(new LLVMList(),sym);
    }
    else
        return nullptr;
}

Expression* create_binary_expr(int op, Expression* a, Expression* b){
    if(a->sym->data->getType()!=b->sym->data->getType())
        throw std::runtime_error("the type of the binary expression is wrong");
    LLVMList* llvmlist=new LLVMList();
    BasicSymbol* res=SymbolFactory::createTmpVarSymbolWithScope(a->sym->data->getType(),scope);
    BasicSymbol* logical_tmp=SymbolFactory::createTmpVarSymbolWithScope(dataType::i1,scope);
    BasicSymbol* resi=SymbolFactory::createTmpVarSymbolWithScope(dataType::i32,scope);
    bool flag=false;
    Expression* exp;
    if(a->sym->data->getType()==dataType::i32){
        switch(op){
            case BINARY_ADD:
                exp=constFolding(constExpType::const_exp_add,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::add,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_SUB:
                exp=constFolding(constExpType::const_exp_sub,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::sub,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_MUL:
                exp=constFolding(constExpType::const_exp_mul,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::mul,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_DIV:
                exp=constFolding(constExpType::const_exp_sdiv,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::sdiv,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_REM:
                exp=constFolding(constExpType::const_exp_srem,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym));
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::srem,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_AND:
                exp=constFolding(constExpType::const_exp_and,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::logical_and,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_OR:
                exp=constFolding(constExpType::const_exp_or,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::logical_or,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_EQ:
                exp=constFolding(constExpType::const_exp_icmp_eq,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::icmp_eq,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_NE:
                exp=constFolding(constExpType::const_exp_icmp_ne,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::icmp_ne,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_LT:
                exp=constFolding(constExpType::const_exp_icmp_slt,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::icmp_slt,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_LE:
                exp=constFolding(constExpType::const_exp_icmp_sle,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym));
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::icmp_sle,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_GT:
                exp=constFolding(constExpType::const_exp_icmp_sgt,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::icmp_sgt,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_GE:
                exp=constFolding(constExpType::const_exp_icmp_sge,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::icmp_sge,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            default:
                throw std::runtime_error("binary expression operation is wrong");
        }
    }
    else if(a->sym->data->getType()==dataType::f32){
        switch(op){
            case BINARY_ADD:
                exp=constFolding(constExpType::const_exp_fadd,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_fadd,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_SUB:
                exp=constFolding(constExpType::const_exp_fsub,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_fsub,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_MUL:
                exp=constFolding(constExpType::const_exp_fmul,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_fmul,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_DIV:
                exp=constFolding(constExpType::const_exp_fdiv,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_fdiv,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_REM:
                exp=constFolding(constExpType::const_exp_frem,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::llvm_frem,res,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                break;
            case BINARY_AND:
                throw std::runtime_error("float type does not support logical calculation");
                break;
            case BINARY_OR:
                throw std::runtime_error("float type does not support logical calculation");
                break;
            case BINARY_EQ:
                exp=constFolding(constExpType::const_exp_fcmp_oeq,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::fcmp_oeq,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_NE:
                exp=constFolding(constExpType::const_exp_fcmp_one,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::fcmp_one,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_LT:
                exp=constFolding(constExpType::const_exp_fcmp_olt,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::fcmp_olt,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_LE:
                exp=constFolding(constExpType::const_exp_fcmp_ole,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::fcmp_ole,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_GT:
                exp=constFolding(constExpType::const_exp_fcmp_ogt,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::fcmp_ogt,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            case BINARY_GE:
                exp=constFolding(constExpType::const_exp_fcmp_oge,a->sym,b->sym);
                if(exp!=nullptr){
                    return exp;
                }
                flag=true;
                llvmlist->InsertTail(LLVMfactory::createBasicOperationLLVM(LLVMtype::fcmp_oge,logical_tmp,dynamic_cast<BasicSymbol*>(a->sym),dynamic_cast<BasicSymbol*>(b->sym)));
                llvmlist->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::zext,logical_tmp,resi));
                break;
            default:
                throw std::runtime_error("binary expression operation is wrong");
        }
    }
    else
        throw std::runtime_error("the type is not allowed in symY");
    Expression* ret;
    llvmlist->InsertHead(a->llvmlist);
    llvmlist->InsertHead(b->llvmlist);
    if(flag)
        ret=new Expression(llvmlist,resi);
    else
        ret=new Expression(llvmlist,res);
    return ret;
}

Expression* create_unary_expr(int op, Expression* a){
    BasicSymbol* res=SymbolFactory::createTmpVarSymbolWithScope(a->sym->data->getType(),scope);
    if(a->sym->data->getType()!=dataType::i32)
        throw std::runtime_error("unary calculation can only be used in int32 type");
    LLVMList* llvmlist=new LLVMList();
    Expression* exp;
    switch (op)
    {
        case SINGLE_NOT:
            exp=constFolding(constExpType::const_exp_add,a->sym,SymbolFactory::createConstSymbol(createData(dataType::i32,-1)));
            if(exp!=nullptr){
                return exp;
            }
            llvmlist->InsertHead(LLVMfactory::createBasicOperationLLVM(LLVMtype::logical_xor,res,dynamic_cast<BasicSymbol*>(a->sym),SymbolFactory::createConstSymbol(createData(dataType::i32,-1))));
            break;
        case SINGLE_NEGTIVE:
            if(a->sym->data->getType()==dataType::i32){
                exp=constFolding(constExpType::const_exp_sub,SymbolFactory::createConstSymbol(createData(dataType::i32,0)),a->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertHead(LLVMfactory::createBasicOperationLLVM(LLVMtype::sub,res,SymbolFactory::createConstSymbol(createData(dataType::i32,0)),dynamic_cast<BasicSymbol*>(a->sym)));
            }
            else if(a->sym->data->getType()==dataType::f32){
                exp=constFolding(constExpType::const_exp_fsub,SymbolFactory::createConstSymbol(createData(dataType::f32,0)),a->sym);
                if(exp!=nullptr){
                    return exp;
                }
                llvmlist->InsertHead(LLVMfactory::createUnaryOperationLLVM(res,dynamic_cast<BasicSymbol*>(a->sym),LLVMtype::llvm_fneg));
            }
    }
    exp=new Expression(llvmlist,res);
    return exp;
}

Symbol* findVar(std::string name){
    for(int i=scope;i>=0;i--){
        if(variable_table[i].find(name)!=variable_table[i].end()){
            return variable_table[i][name];
        }
    }
    return nullptr;
}

Expression* create_primary_IDENTIFIER(std::string name){
    BasicSymbol* sym;
    Expression* exp;
    LLVMList* llvmlist=new LLVMList();
    Symbol* identifier=findVar(name);
    if(identifier!=nullptr){
        if(identifier->getType()==symType::pointer){
            PointerSymbol* ps=dynamic_cast<PointerSymbol*>(identifier);
            sym=SymbolFactory::createVarSymbolWithScope(name+".loader",scope);
            llvmlist->InsertHead(LLVMfactory::createLoadLLVM(ps,sym));
            exp=new Expression(llvmlist,sym);
        }
        else if(identifier->getType()==symType::variable){
            sym=dynamic_cast<VarSymbol*>(identifier);
            exp=new Expression(llvmlist,sym);
        }
        else{
            throw std::runtime_error("error occurs at create_primary_IDENTIFIER."
                "the identifer is neither a pointer symbol nor vairable symbol.");
        }
    }
    else{
        throw std::runtime_error("error occurs at create_primary_IDENTIFIER."
            "the identifier was not defined before!");
    }
    return exp;
}

Expression* create_primary_INTCONST(int value){
    return new Expression(new LLVMList(),SymbolFactory::createConstSymbol(createData(dataType::i32,value)));
}

Expression* create_primary_FLOATCONST(float value){
    return new Expression(new LLVMList(),SymbolFactory::createConstSymbol(createData(dataType::f32,value)));
}

FuncSymbol* findFunc(std::string name){
    if(func_table.find(name)!=func_table.end())
        return func_table[name];
    else
        return nullptr;
}

Expression* create_func_call(std::string name, Expression* exp){
    FuncSymbol* fs=findFunc(name);
    LLVMList* llvmlist=new LLVMList();
    BasicSymbol* bs=nullptr;
    if(fs->returnType!=dataType::void_)
        bs=SymbolFactory::createTmpVarSymbolWithScope(fs->returnType,scope);
    std::vector<Symbol*>args;
    if(fs!=nullptr){
        int i;
        for(i=0;exp!=nullptr;exp=exp->next,i++){
            if(exp->sym->getType()==symType::array){
                ArraySymbol* array1=dynamic_cast<ArraySymbol*>(exp->sym);
                if(array1->getArrayType()!=fs->getParamTypes()[i]){
                    throw std::invalid_argument("error occurs at create_func_call."
                "the function parameters type is wrong!");
                }
            }
            else if(exp->sym->data->getType()!=fs->getParamTypes()[i]){
                throw std::invalid_argument("error occurs at create_func_call."
                "the function parameters type is wrong!");
            }
            llvmlist->InsertTail(exp->llvmlist);
            args.push_back(exp->sym);
        }
        if(i!=fs->getParamTypes().size()){
            throw std::invalid_argument("error occurs at create_func_call."
            "the number of the function parameters is wrong!");
        }
        llvmlist->InsertTail(LLVMfactory::createCallLLVM(bs,fs,args));
    }
    else{
        throw std::runtime_error("error occurs at create_func_call."
            "the function was not defined before!");
    }
    return new Expression(llvmlist,bs);
}

std::vector<std::pair<dataType,BasicSymbol*>>& getIdxFromExp(std::vector<Expression*>* exps){
    static std::vector<std::pair<dataType,BasicSymbol*>> res;
    res.clear();
    for(auto &exp : (*exps)){
        res.push_back({exp->sym->data->getType(),dynamic_cast<BasicSymbol*>(exp->sym)});
    }
    return res;
}

Expression* get_element(std::string name,std::vector<Expression*>* exps){
    Symbol* sym=findVar(name);
    LLVMList* llvmlist=new LLVMList();
    BasicSymbol* bs;
    if(sym!=nullptr){
        if(exps->size()!=0){
            if(sym->getType()!=symType::array){
                throw std::runtime_error("error occurs at get_element."
                    "the identifer is not a array symbol.");
            }
            ArraySymbol* array=dynamic_cast<ArraySymbol*>(sym);
            bs=SymbolFactory::createTmpVarSymbolWithScope(array->getArrayType(),scope);
            PointerSymbol* ps=SymbolFactory::createTmpPointerSymbolWithScope(array->getArrayType(),scope);
            ps->isConst=array->isConst;
            llvmlist->InsertHead(LLVMfactory::createGetElementPtrLLVM(ps,array,getIdxFromExp(exps)));
            llvmlist->InsertTail(LLVMfactory::createLoadLLVM(ps,bs));
            for(auto &exp : (*exps)){
                llvmlist->InsertHead(exp->llvmlist);
            }
        }
        else if(sym->getType()==symType::array){
            return new Expression(llvmlist,sym);
        }
        else if(sym->getType()==symType::pointer){
            PointerSymbol* ps=dynamic_cast<PointerSymbol*>(sym);
            bs=SymbolFactory::createVarSymbolWithScope(name+".loader",scope,createInitialedData(ps->PointedType));
            llvmlist->InsertTail(LLVMfactory::createLoadLLVM(ps,bs));
        }
        else if(sym->getType()==symType::variable){
            bs=dynamic_cast<VarSymbol*>(sym);
        }
        else if(sym->getType()==symType::constant_var){
            ConstVarSymbol* cvs=dynamic_cast<ConstVarSymbol*>(sym);
            bs=cvs;
        }
    }
    else{
        throw std::runtime_error("error occurs at get_item."
            "the variable was not defined before!");
    }
    return new Expression(llvmlist,bs);
}

LLVMList* create_if_stmt(Expression* exp,LLVMList* llvmlist){
    LLVMList* res=new LLVMList();
    res->InsertTail(exp->llvmlist);
    BasicSymbol* condi=dynamic_cast<BasicSymbol*>(exp->sym);
    if(condi->getDataType()==dataType::i32){
        condi=SymbolFactory::createTmpVarSymbolWithScope(dataType::i1,scope);
        res->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::llvm_trunc,dynamic_cast<BasicSymbol*>(exp->sym),condi));
    }
    LabelSymbol* label1=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    LabelSymbol* label2=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    res->InsertTail(LLVMfactory::createConditionalBranchLLVM(condi,label1,label2));
    res->InsertTail(LLVMfactory::createLableLLVM(label1));
    res->InsertTail(llvmlist);
    res->InsertTail(LLVMfactory::createLableLLVM(label2));
    return res;
}

LLVMList* create_if_else_stmt(Expression* exp,LLVMList* llvmlist1,LLVMList* llvmlist2){
    LLVMList* res=new LLVMList();
    res->InsertTail(exp->llvmlist);
    BasicSymbol* condi=dynamic_cast<BasicSymbol*>(exp->sym);
    if(condi->getDataType()==dataType::i32){
        condi=SymbolFactory::createTmpVarSymbolWithScope(dataType::i1,scope);
        res->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::llvm_trunc,dynamic_cast<BasicSymbol*>(exp->sym),condi));
    }
    LabelSymbol* label1=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    LabelSymbol* label2=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    LabelSymbol* label3=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    res->InsertTail(LLVMfactory::createConditionalBranchLLVM(condi,label1,label2));
    res->InsertTail(LLVMfactory::createLableLLVM(label1));
    res->InsertTail(llvmlist1);
    res->InsertTail(LLVMfactory::createUnconditionalBranchLLVM(label3));
    res->InsertTail(LLVMfactory::createLableLLVM(label2));
    res->InsertTail(llvmlist2);
    res->InsertTail(LLVMfactory::createLableLLVM(label3));
    return res;
}

LLVMList* create_while(Expression* exp){
    LabelSymbol* label3=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    LLVMList* res=new LLVMList();
    res->InsertHead(LLVMfactory::createLableLLVM(label3));
    res->InsertTail(exp->llvmlist);
    LabelSymbol* label1=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    LabelSymbol* label2=SymbolFactory::createTmpLabelSymbolWithScope(scope);
    BasicSymbol* condi=dynamic_cast<BasicSymbol*>(exp->sym);
    if(condi->getDataType()==dataType::i32){
        condi=SymbolFactory::createTmpVarSymbolWithScope(dataType::i1,scope);
        res->InsertTail(LLVMfactory::createTypeConversionOperation(LLVMtype::llvm_trunc,dynamic_cast<BasicSymbol*>(exp->sym),condi));
    }
    res->InsertTail(LLVMfactory::createConditionalBranchLLVM(condi,label1,label2));
    res->InsertTail(LLVMfactory::createLableLLVM(label1));
    break_st.push(label2);
    continue_st.push(label3);
    return res;
}

LLVMList* create_while_stmt(LLVMList* llvmlist,LLVMList* stmt){
    LabelSymbol* label2=break_st.top();
    LabelSymbol* label3=continue_st.top();
    break_st.pop();
    continue_st.pop();
    LLVMList* res=new LLVMList();
    res->InsertTail(llvmlist);
    res->InsertTail(stmt);
    res->InsertTail(LLVMfactory::createUnconditionalBranchLLVM(label3));
    res->InsertTail(LLVMfactory::createLableLLVM(label2));
    return res;
}

LLVMList* create_continue_stmt(){
    LabelSymbol* label=continue_st.top();
    LLVMList* res=new LLVMList();
    res->InsertHead(LLVMfactory::createUnconditionalBranchLLVM(label));
    return res;
}

LLVMList* create_break_stmt(){
    LabelSymbol* label=break_st.top();
    LLVMList* res=new LLVMList();
    res->InsertHead(LLVMfactory::createUnconditionalBranchLLVM(label));
    return res;
}

LLVMList* create_return_stmt(Expression* exp){
    LLVMList* llvmlist=new LLVMList();
    if(exp==nullptr){
        llvmlist->InsertTail(LLVMfactory::createReturnLLVM(nullptr));
    }
    else{
        llvmlist->InsertHead(exp->llvmlist);
        llvmlist->InsertTail(LLVMfactory::createReturnLLVM(dynamic_cast<BasicSymbol*>(exp->sym)));
    }
    return llvmlist;
}

LLVMList* create_const_decl(int btype,std::vector<Symbol*>* syms){
    LLVMList* llvmlist=new LLVMList();
    dataType dtype=btype==INT_TYPE?dataType::i32:dataType::f32;
    dataType ty=assign_queue.front()->sym->data->getType();
    if((btype==INT_TYPE && ty==dataType::i32)||(btype==FLOAT_TYPE && ty==dataType::f32)){
        for(auto &a : (*syms)){
            if(a->getType()==symType::array){
                ArraySymbol* array=dynamic_cast<ArraySymbol*>(a);
                array->arrayType=dtype;
                llvmlist->InsertTail(LLVMfactory::createConstantArrayVarDefination(array));
            }
            else if(a->getType()==symType::constant_var){
                ConstVarSymbol* constVarSymbol=dynamic_cast<ConstVarSymbol*>(a);
                if(constVarSymbol->getDataType()==dataType::data_undefined){
                    throw std::runtime_error("the constVarSymbol is defined by a undefined dataType");
                }
                llvmlist->InsertTail(LLVMfactory::createConstantNonArrayVarDefination(constVarSymbol,SymbolFactory::createConstSymbol(constVarSymbol->data)));
            }
        }
    }
    else{
        for(auto &a : (*syms)){
            if(a->getType()==symType::array){
                ArraySymbol* array=dynamic_cast<ArraySymbol*>(a);
                array->arrayType=dtype;
                for(auto &b : array->initialedData->initializedData){
                    b={b.first,typeConversion(dtype,b.second)};
                }
                llvmlist->InsertTail(LLVMfactory::createConstantArrayVarDefination(array));
            }
            else{
                ConstVarSymbol* constSymbol=dynamic_cast<ConstVarSymbol*>(a);
                constSymbol->data=typeConversion(dtype,constSymbol->data);
                llvmlist->InsertTail(LLVMfactory::createConstantNonArrayVarDefination(constSymbol,SymbolFactory::createConstSymbol(constSymbol->data)));
            }
        }
    }
    assign_queue.pop();
    return llvmlist;
}

Symbol* create_array_const_def(std::string name,std::vector<int>& idxs,ArrayInitial* arrayInitial){
    ArraySymbol* array=SymbolFactory::createArraySymbolWithScope(name,idxs,scope);//注意之后要把数据类型给加上！
    array->setInitialedData(arrayInitial);
    std::stack<int> empty_stack;
    //std::swap(empty_stack,array_initial);
    //assign_queue.push(exp);
    cnt_array_init=0;
    variable_table[scope][name]=array;
    return array;
}

Symbol* create_const_def(std::string name,Expression* exp){
    //std::stack<int> empty_stack;
    //std::swap(empty_stack,array_initial);
    cnt_array_init=0;
    assign_queue.push(exp);
    ConstVarSymbol* constVarSymbol=SymbolFactory::createConstVarSymbolWithScope(name,scope,exp->sym->data);
    variable_table[scope][name]=constVarSymbol;
    return constVarSymbol;
}

Symbol* create_var_def(std::string name,std::vector<int>* idxs){
    //std::stack<int> empty_stack;
    //std::swap(empty_stack,array_initial);
    cnt_array_init=0;
    assign_queue.push(nullptr);
    //array_init_idx=0;
    if(variable_table[scope].find(name)!=variable_table[scope].end())
        throw std::runtime_error("the identifier was defined before!");
    if(idxs->size()==0){
        PointerSymbol* ps=SymbolFactory::createPointerSymbolWithScope(name,scope);
        variable_table[scope][name]=ps;
        return ps;
    }
    else{
        ArraySymbol* array=SymbolFactory::createArraySymbolWithScope(name,*idxs,scope);
        array->setInitialedData(new ArrayInitial());
        variable_table[scope][name]=array;
        return array;
    }
}

Symbol* create_var_def(std::string name,std::vector<int>& idxs,Expression* exp){
    //std::stack<int> empty_stack;
    //std::swap(empty_stack,array_initial);
    cnt_array_init=0;
    assign_queue.push(exp);
    if(variable_table[scope].find(name)!=variable_table[scope].end())
        throw std::runtime_error("the identifier was defined before!");
    if(idxs.size()==0){
        PointerSymbol* pointerSymbol= SymbolFactory::createPointerSymbolWithScope(name,scope);
        if(isConst(exp->sym)){
            if(pointerSymbol->data->getType()==dataType::array_data)
                pointerSymbol->data=arrayInitialToData(dynamic_cast<ArrayInitial*>(exp->sym->data));
            else
                pointerSymbol->data=exp->sym->data;
        }  
        variable_table[scope][name]=pointerSymbol;
        return pointerSymbol;
    }
    else{
        ArraySymbol* array=SymbolFactory::createArraySymbolWithScope(name,idxs,scope);
        if(exp->sym!=nullptr){
            array->setInitialedData(dynamic_cast<ArrayInitial*>(exp->sym->data));
        }
        else{
            ArrayInitial* arrayInitial=new ArrayInitial();
            arrayInitial->setInitMode(zeroinitializer);
            array->setInitialedData(arrayInitial);
        }
        variable_table[scope][name]=array;
        return array;
    }
}

std::vector<std::pair<dataType,BasicSymbol*>>& intVectorToBasicSymbolVector(const std::vector<int>& idxs){
    static std::vector<std::pair<dataType,BasicSymbol*>> res;
    res.clear();
    res.push_back({dataType::i32,SymbolFactory::createConstSymbol(createData(dataType::i32,0))});
    for(auto &idx:idxs){
        res.push_back({dataType::i32,SymbolFactory::createConstSymbol(createData(dataType::i32,idx))});
    }
    return res;
}

LLVMList* create_var_decl(int btype,std::vector<Symbol*>* syms){
    LLVMList* llvmlist=new LLVMList();
    dataType dtype=btype==INT_TYPE?dataType::i32:dataType::f32;
    const size_t size = syms->size();
    for (size_t i = 0; i < size; ++i) {
        const auto& a = (*syms)[i];
        dataType ty=assign_queue.empty()||assign_queue.front()==nullptr||assign_queue.front()->sym==nullptr?dtype:assign_queue.front()->sym->data->getType();
        if((btype==INT_TYPE && ty==dataType::i32)||(btype==FLOAT_TYPE && ty==dataType::f32)){
            if(a->getType()==symType::array){
                ArraySymbol* array=dynamic_cast<ArraySymbol*>(a);
                array->arrayType=dtype;
                if(a->scope==GLOBAL_SCOPE||array->isConst==true){
                    llvmlist->InsertHead(LLVMfactory::createGlobalArrayVarDefination(array));
                }
                else{
                    llvmlist->InsertTail(LLVMfactory::createAllocaArrayLLVM(array));
                    PointerSymbol* ps;
                    for(auto & element :array->getInitializedData()){
                        ps=SymbolFactory::createTmpPointerSymbolWithScope(array->getArrayType(),scope);
                        llvmlist->InsertTail(LLVMfactory::createGetElementPtrLLVM(ps,array,intVectorToBasicSymbolVector(element.first)));
                        if(element.second!=nullptr&&element.second->getType()!=dataType::data_undefined)
                            llvmlist->InsertTail(LLVMfactory::createStoreLLVM(SymbolFactory::createConstSymbol(element.second),ps));
                        else
                            throw std::runtime_error("the constant do not have a value");
                    }
                }
            }
            else if(a->getType()==symType::pointer){
                PointerSymbol* pointerSymbol=dynamic_cast<PointerSymbol*>(a);
                pointerSymbol->PointedType=dtype;
                if(assign_queue.front()!=nullptr&&pointerSymbol->data!=nullptr){
                    if(pointerSymbol->scope==GLOBAL_SCOPE){
                        llvmlist->InsertTail(LLVMfactory::createGlobalNonArrayVarDefination(pointerSymbol,SymbolFactory::createConstSymbol(pointerSymbol->data)));
                    }
                    else{
                        llvmlist->InsertTail(LLVMfactory::createAllocaNonArrayLLVM(pointerSymbol));
                        if(assign_queue.front()->llvmlist->head==nullptr){
                            if(pointerSymbol->data!=nullptr&&pointerSymbol->getType()!=dataType::data_undefined)
                                llvmlist->InsertTail(LLVMfactory::createStoreLLVM(dynamic_cast<BasicSymbol*>(assign_queue.front()->sym),pointerSymbol));
                            }
                        else{
                            llvmlist->InsertTail(assign_queue.front()->llvmlist);
                            llvmlist->InsertTail(LLVMfactory::createStoreLLVM(dynamic_cast<BasicSymbol*>(assign_queue.front()->sym),pointerSymbol));
                        }
                    }
                }
                else{
                    if(pointerSymbol->scope==GLOBAL_SCOPE)
                        llvmlist->InsertTail(LLVMfactory::createGlobalNonArrayVarDefination(pointerSymbol,initializer::zeroinitializer));
                    else
                        llvmlist->InsertTail(LLVMfactory::createAllocaNonArrayLLVM(pointerSymbol));
                }
            }
            else{
                throw std::runtime_error("error occurs at the create_var_decl"
                    "the variable is neither array type nor pointer type");
            }
        }
        else{
            if(a->getType()==symType::array){
                ArraySymbol* array=dynamic_cast<ArraySymbol*>(a);
                array->arrayType=dtype;
                for(auto &b : array->initialedData->initializedData){
                    b={b.first,typeConversion(dtype,b.second)};
                }
                if(a->scope==GLOBAL_SCOPE||array->isConst==true){
                    llvmlist->InsertHead(LLVMfactory::createGlobalArrayVarDefination(array));
                }
                else{
                    llvmlist->InsertTail(LLVMfactory::createAllocaArrayLLVM(array));
                    PointerSymbol* ps;
                    for(auto & element :array->getInitializedData()){
                        ps=SymbolFactory::createTmpPointerSymbolWithScope(array->getArrayType(),scope);
                        llvmlist->InsertTail(LLVMfactory::createGetElementPtrLLVM(ps,array,intVectorToBasicSymbolVector(element.first)));
                        if(element.second!=nullptr&&element.second->getType()!=dataType::data_undefined)
                            llvmlist->InsertTail(LLVMfactory::createStoreLLVM(SymbolFactory::createConstSymbol(element.second),ps));
                        else
                            throw std::runtime_error("the constant do not have a value");
                    }
                }
            }
            else if(a->getType()==symType::pointer){
                PointerSymbol* pointerSymbol=dynamic_cast<PointerSymbol*>(a);
                pointerSymbol->PointedType=dtype;
                if(pointerSymbol->data!=nullptr){
                    if(pointerSymbol->scope==GLOBAL_SCOPE){
                        llvmlist->InsertTail(LLVMfactory::createGlobalNonArrayVarDefination(pointerSymbol,SymbolFactory::createConstSymbol(typeConversion(dtype,pointerSymbol->data))));
                    }
                    else{
                        llvmlist->InsertTail(LLVMfactory::createAllocaNonArrayLLVM(pointerSymbol));
                        if(pointerSymbol->data!=nullptr&&pointerSymbol->getType()!=dataType::data_undefined)
                            llvmlist->InsertTail(LLVMfactory::createStoreLLVM(SymbolFactory::createConstSymbol(pointerSymbol->data),pointerSymbol));
                        else
                            throw std::runtime_error("the constant do not have a value");
                    }
                }
                else{
                    if(pointerSymbol->scope==GLOBAL_SCOPE)
                        llvmlist->InsertTail(LLVMfactory::createGlobalNonArrayVarDefination(pointerSymbol,initializer::zeroinitializer));
                    else
                        llvmlist->InsertTail(LLVMfactory::createAllocaNonArrayLLVM(pointerSymbol));
                }
            }
            else
                throw std::runtime_error("error occurs in the create_var_decl.the symbol is neither a pointer nor array");
        }
        assign_queue.pop();
    }
    return llvmlist;
}

dataType intToDataType(int btype){
    dataType dtype;
    switch(btype){
        case INT_TYPE:
            dtype=dataType::i32;
            break;
        case FLOAT_TYPE:
            dtype=dataType::f32;
            break;
        case VOID_TYPE:
            dtype=dataType::void_;
            break;
        default:
            dtype=dataType::data_undefined;
            break;
    }
    return dtype;
}

LLVMList* create_func_def(int btype,std::string name,std::vector<Symbol*>* syms){
    dataType dtype=intToDataType(btype);
    std::vector<dataType> param_types;
    for(auto &a : (*syms)){
        if(a->getType()==symType::variable)
            param_types.push_back(dynamic_cast<VarSymbol*>(a)->getDataType());
        else if(a->getType()==symType::array)
            param_types.push_back(dynamic_cast<ArraySymbol*>(a)->getArrayType());
    }
    FuncSymbol* func=SymbolFactory::createFuncSymbolWithScope(name,param_types,GLOBAL_SCOPE,dtype);
    func_table[name]=func;
    FuncDefination* funcdefination=LLVMfactory::createFuncDefination(func,*syms);
    LLVMList* res=new LLVMList();
    res->InsertHead(funcdefination);
    return res;
}

LLVMList* create_func_blk(LLVMList* decl,LLVMList* llvmlist){
    FuncDefination* funcdefination=dynamic_cast<FuncDefination*>(decl->head);
    funcdefination->block_tail=llvmlist->tail;
    LLVMList* res=new LLVMList();
    res->InsertHead(decl);
    res->InsertTail(llvmlist);
    return res;
}

void create_null_param(){
    scope=1;
    if(variable_table.size()<2){
        variable_table.push_back(std::unordered_map<std::string,Symbol*>());
    }
    if(variable_rename_table.size()<2){
        variable_rename_table.push_back(std::unordered_map<std::string,int>());
    }
}

Symbol* create_param_nonarray(int btype,std::string name){
    scope=1;
    if(variable_table.size()<2){
        variable_table.push_back(std::unordered_map<std::string,Symbol*>());
    }
    if(variable_rename_table.size()<2){
        variable_rename_table.push_back(std::unordered_map<std::string,int>());
    }
    VarSymbol* param=SymbolFactory::createVarSymbolWithScope(name,intToDataType(btype),scope);
    variable_table[1][name]=param;
    return param;
}

Symbol* create_param_array(int btype,std::string name,std::vector<int>* dims){
    std::vector<int>dimension;
    scope=1;
    if(variable_table.size()<2){
        variable_table.push_back(std::unordered_map<std::string,Symbol*>());
    }
    if(variable_rename_table.size()<2){
        variable_rename_table.push_back(std::unordered_map<std::string,int>());
    }
    for(auto & dim : (*dims)){
        dimension.push_back(dim);
    }
    ArraySymbol* array=SymbolFactory::createArraySymbolWithScope(name,dimension,scope,intToDataType(btype));
    variable_table[1][name]=array;
    return array;
}

void end_parser(){
    LLVMList* llvmlist=module_list->head;
    LLVM* llvm;
    std::ofstream outfile("output.ll");
    if(outfile.is_open()){
        for(;llvmlist!=nullptr;llvmlist=llvmlist->next){
            llvm=llvmlist->head;
            //if(llvm->getLLVMType()==LLVMtype::func_def){
                //SSA(llvmlist);
            //}
            outfile<<llvm->out_str();
        }
        outfile.close();
    }
}

void func_table_init(){
    FuncSymbol* func;
    std::vector<dataType>params;
    std::string name;
    name="getint";
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::i32);
    func_table[name]=func;

    name="getchar";
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::i32);
    func_table[name]=func;

    name="getfloat";
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::f32);
    func_table[name]=func;

    name="getarray";
    params.clear();
    params.push_back(dataType::i32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::i32);
    func_table[name]=func;

    name="getfarray";
    params.clear();
    params.push_back(dataType::f32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::i32);
    func_table[name]=func;

    name="putint";
    params.clear();
    params.push_back(dataType::i32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;

    name="putch";
    params.clear();
    params.push_back(dataType::i32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;

    name="putfloat";
    params.clear();
    params.push_back(dataType::f32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;

    name="putarray";
    params.clear();
    params.push_back(dataType::i32);
    params.push_back(dataType::i32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;

    name="putfarray";
    params.clear();
    params.push_back(dataType::i32);
    params.push_back(dataType::f32);
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;

    name="starttime";
    params.clear();
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;

    name="stoptime";
    params.clear();
    func=SymbolFactory::createFuncSymbolWithScope(name,params,GLOBAL_SCOPE,dataType::void_);
    func_table[name]=func;
}

void begin_parser(){
    scope=GLOBAL_SCOPE;
    module_list=new ModuleList();
    variable_table.push_back(std::unordered_map<std::string,Symbol*>());
    func_table_init();
    //array_init_idx=0;
    cnt_array_init=0;
    array_init_idx=std::vector<int>(0);
}

LLVMList* assign_array_item(Expression* LVal,Expression* exp){
    LLVM* tail_llvm=LVal->llvmlist->tail;
    LoadLLVM* llvm=dynamic_cast<LoadLLVM*>(tail_llvm);
    LLVMList* llvmlist=new LLVMList();
    llvmlist->InsertHead(LVal->llvmlist);
    llvmlist->InsertTail(exp->llvmlist);
    if(llvm!=nullptr){
        PointerSymbol* ps=llvm->src_sym;
        if(ps->isConst==false)
            llvmlist->InsertTail(LLVMfactory::createStoreLLVM(dynamic_cast<BasicSymbol*>(exp->sym),ps));
        else
            throw std::runtime_error("trying to assign to a constant varible");
    }
    return llvmlist;
}

void add_init_item(){
    int n=dim_array.size();
    int i=n-1;
    array_init_idx[i]++;
    while(array_init_idx[i]>=dim_array[i]){
        array_init_idx[i]-=dim_array[i];
        if(i==0)
            if(array_init_idx[i]!=0)
                throw std::runtime_error("the number of the initial data is out of the rage of the array item number");
            else
                break;
        i--;
        array_init_idx[i]++;
    }
}

void create_var_init_list(Expression* exp){
    if(exp->sym!=nullptr){
        if(exp->sym->data->getType()!=dataType::array_data){
            exp->sym->data=dataToArrayInitial(exp->sym->data);
            ArrayInitial* arrayInitial = dynamic_cast<ArrayInitial*>(exp->sym->data);
            arrayInitial->initializedData[0].first=array_init_idx;
            add_init_item();
        }
    }
}

void create_var_init_list(Expression* exp1,Expression* exp2){
    ArrayInitial* arrayInitial2=nullptr;
    if(exp2->sym!=nullptr){
        if(exp2->sym->data->getType()!=dataType::array_data){
            exp2->sym->data=dataToArrayInitial(exp2->sym->data);
            arrayInitial2 = dynamic_cast<ArrayInitial*>(exp2->sym->data);
            arrayInitial2->initializedData[0].first=array_init_idx;
            add_init_item();
        }
        else
            arrayInitial2 = dynamic_cast<ArrayInitial*>(exp2->sym->data);
    }
    ArrayInitial* arrayInitial1 = dynamic_cast<ArrayInitial*>(exp1->sym->data);
    if(arrayInitial2!=nullptr)
        arrayInitial1->merge(arrayInitial2);
}

void reduce_var_init_list(Expression* exp){
    bool flag=false;
    for(int i=cnt_array_init-1;i<dim_array.size();i++){
        if(array_init_idx[i]!=0){
            flag=true;
            array_init_idx[i]=0;
        }
    }
    cnt_array_init--;
    if(flag&&cnt_array_init>0)
        array_init_idx[cnt_array_init-1]++;
}

void reduce_var_def_left(const std::vector<int>*dims){
    dim_array.clear();
    dim_array=*dims;
    array_init_idx.clear();
    for(int i=0;i<dim_array.size();i++)
        array_init_idx.push_back(0);
    cnt_array_init=0;
}

void reduce_var_def_left(const std::vector<int>*dims,Expression* dim){
    dim_array.clear();
    dim_array=*dims;
    dim_array.push_back(std::get<int>(dim->sym->data->getValue()));
    cnt_array_init=0;
    array_init_idx.clear();
    array_init_idx.resize(dims->size());
    std::fill(array_init_idx.begin(), array_init_idx.end(), 0);
}

void var_init_list_reduce_left(){
    cnt_array_init++;
    if(cnt_array_init>dim_array.size()){
        throw std::runtime_error("the number of the { is more than the dimension of the array");
    }
}