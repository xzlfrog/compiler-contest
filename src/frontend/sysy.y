%code requires {
#include <string>
#include <vector>
class Expression;
class Symbol;
class ArrayInitial;
class LLVMList;
}

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/frontend/frontendTool.hpp"
#include<string>
#include<vector>
#include"../../include/llvm.hpp"
#include"../../include/sym.hpp"
#include"../../include/exp.hpp"
#include<stack>
#include<fstream>
extern FILE* yyin;
#include<iostream>


void yyerror(const char *s);
extern int yylex(void);
extern int yylineno;
extern ModuleList* module_list;
extern int scope;
extern std::vector<std::unordered_map<std::string,int>> variable_rename_table;
extern std::vector<std::unordered_map<std::string,Symbol*>> variable_table;
extern std::stack<int>array_initial;
extern int array_init_idx;
%}

%union {
    std::string* str;
    int dtype;
    Expression* exp;
    std::vector<int>* int_vector;
    Symbol* sym;
    std::vector<Symbol*>*  sym_vector;
    std::vector<Expression*>* exp_vector;
    LLVMList* llvm;
}

%token INT FLOAT CONST VOID
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token EQ NE LT GT LE GE AND OR NOT IDENTIFIER INT_CONST FLOAT_CONST

%type <str> IDENTIFIER INT_CONST FLOAT_CONST

%type <llvm> block_items block_item block stmt decl_or_func func_def decl var_decl const_decl
%type <sym_vector> func_params const_def_list func_param_list var_def_list
%type <sym> func_param const_def var_def
%type <exp> cond expr or_expr and_expr eq_expr rel_expr add_expr mul_expr unary_expr expr_list
%type <exp> primary_expr LVal func_call const_exp const_init_list const_init_val var_init_list var_init_val
%type <dtype> btype
%type <exp_vector> index_list
%type <int_vector> dim_list

%start comp_unit

%nonassoc IFX
%nonassoc ELSE

%%

comp_unit : decl_or_func_list{ 
    end_parser();
}
;

decl_or_func_list : decl_or_func
    {   module_list->InsertHead($1); }
| decl_or_func_list decl_or_func
    {   module_list->InsertTail($2); }
;

decl_or_func : decl
    { $$ = $1; }
    | func_def
    { $$ = $1; }
;

decl : const_decl
    { $$ = $1; }
    | var_decl
    { $$ = $1; }
;

const_decl : CONST btype const_def_list ';'
    { 
        if($2==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        $$ = create_const_decl($2, $3); 
    }
;

var_decl : btype var_def_list ';'
    { 
        if($1==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        $$ = create_var_decl($1, $2); 
    }
;

btype : INT
    { $$ = INT_TYPE; }
    | FLOAT
    { $$ = FLOAT_TYPE; }
    | VOID
    { $$ = VOID_TYPE;}
;

const_def_list : const_def{
        std::vector<Symbol*>* syms=new std::vector<Symbol*>(0);
        syms->push_back($1);
        $$=syms;
    }
    | const_def_list ',' const_def{ 
        $1->push_back($3);
        $$ = $1;
    }
;

var_def_list : var_def{
        std::vector<Symbol*>* syms=new std::vector<Symbol*>(0);
        syms->push_back($1);
        $$=syms;
    }
    | var_def_list ',' var_def{ 
        $1->push_back($3);
        $$ = $1;
    }
;

const_def : IDENTIFIER dim_list '[' const_exp ']' '=' const_init_val
    {   $$ = create_array_const_def(*($1), $2, $4, dynamic_cast<ArrayInitial*>($7->sym->data)); }
    | IDENTIFIER '=' const_init_val{
      $$ = create_const_def(*($1), $3); 
    }
;

var_def : IDENTIFIER dim_list{ 
        $$ = create_var_def(*($1), $2); 
    }
    | IDENTIFIER dim_list '=' var_init_val{ 
        $$ = create_var_def(*($1), $2, $4); 
    }
;

dim_list : /* empty */
    { $$ = new std::vector<int>(0); }
    | dim_list '[' const_exp ']'{  
        $$ = $1;
        BasicSymbol* constSym;
        if($3->sym->getType()==symType::constant_nonvar)
            constSym=dynamic_cast<ConstSymbol*>($3->sym);
        else if($3->sym->getType()==symType::constant_var)
            constSym=dynamic_cast<ConstVarSymbol*>($3->sym);
        $$->push_back(std::get<int>(constSym->data->getValue()));
    }
;

func_def : btype IDENTIFIER '(' func_params ')'
    {
        $<llvm>$ = create_func_def($1, *($2), $4);
    }
    block
    {
        scope=GLOBAL_SCOPE;
        while(variable_table.size()>1){
            variable_table.pop_back();
        }
        $$=create_func_blk($<llvm>6,$7);
    }
;

func_params : /* empty */
    {   $$=new std::vector<Symbol*>(0); create_null_param();}
    | func_param_list{   
        $$=$1;  
    }
;

func_param_list : func_param{ 
        $$=new std::vector<Symbol*>(0);
        $$->push_back($1);
    }
    | func_param_list ',' func_param{
        $$ = $1;
        $$->push_back($3);
    }
;

func_param : btype IDENTIFIER
    { 
        if($2==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        $$ = create_param_nonarray($1,*($2)); 
    }
    | btype IDENTIFIER '[' ']' dim_list
    { 
        if($2==VOID_TYPE)
            throw std::runtime_error("the variable is not allowed to be a void type");
        $$ = create_param_array($1,*($2),$5);
    }
;

block : '{' 
    {
        scope+=1;
        variable_table.push_back(std::unordered_map<std::string,Symbol*>());
        while(variable_rename_table.size()<=scope)
            variable_rename_table.push_back(std::unordered_map<std::string,int>());
        $<llvm>$=new LLVMList();
    }
    block_items '}'{ 
        $$=$<llvm>2;
        $$->InsertTail($3);
        while(variable_table.size()>scope)
            variable_table.pop_back();
        scope-=1;
    }
;

block_items: 
    {   $$=new LLVMList();}
    | block_item block_items{  
        $$=$2;
        $$->InsertHead($1);
    }
;

block_item : decl
    {   $$ = $1; }
    | stmt
    {   $$ = $1; }
;

stmt : LVal '=' expr ';'
    {   $$=assign_array_item($1,$3);}
    | expr ';'
    {   $$=$1->llvmlist;}
    | ';'
    {   $$=new LLVMList();}
    | block
    {   $$=$1; }
    | IF '(' cond ')' stmt %prec IFX
    { $$ = create_if_stmt($3, $5); }
    | IF '(' cond ')' stmt ELSE stmt
    { $$ = create_if_else_stmt($3, $5, $7); }
    | WHILE '(' cond ')'
    { $<llvm>$ = create_while($3); }
      stmt
    { $$ = create_while_stmt($<llvm>5,$6);}
    | BREAK ';'
    { $$ = create_break_stmt();}
    | CONTINUE ';'
    { $$ = create_continue_stmt();}
    | RETURN expr ';'
    { $$ = create_return_stmt($2); }
    | RETURN ';'
    { $$ = create_return_stmt(nullptr); }
;

LVal : IDENTIFIER index_list{
    $$=get_element(*($1),$2);
}
;

index_list : 
    {   $$=new std::vector<Expression*>(0); }
    |index_list '[' expr ']'{   
        $$=$1;
        $$->push_back($3);
    }
;


expr : add_expr
    { $$ = $1; }
;

cond : or_expr
    { $$ = $1;}
;

or_expr : and_expr
    {   $$ = $1;  }
    | or_expr OR and_expr
    { $$ = create_binary_expr(BINARY_OR, $1, $3); }
;

and_expr : eq_expr
    | and_expr AND eq_expr
    { $$ = create_binary_expr(BINARY_AND, $1, $3); }
;

eq_expr : rel_expr
    | eq_expr EQ rel_expr
    { $$ = create_binary_expr(BINARY_EQ, $1, $3); }
    | eq_expr NE rel_expr
    { $$ = create_binary_expr(BINARY_NE, $1, $3); }
;

rel_expr : add_expr
    | rel_expr LT add_expr
    { $$ = create_binary_expr(BINARY_LT, $1, $3); }
    | rel_expr GT add_expr
    { $$ = create_binary_expr(BINARY_GT, $1, $3); }
    | rel_expr LE add_expr
    { $$ = create_binary_expr(BINARY_LE, $1, $3); }
    | rel_expr GE add_expr
    { $$ = create_binary_expr(BINARY_GE, $1, $3); }
;

add_expr : mul_expr
    | add_expr '+' mul_expr
    { $$ = create_binary_expr(BINARY_ADD, $1, $3); }
    | add_expr '-' mul_expr
    { $$ = create_binary_expr(BINARY_SUB, $1, $3); }
;

mul_expr : unary_expr
    | mul_expr '*' unary_expr
    { $$ = create_binary_expr(BINARY_MUL, $1, $3); }
    | mul_expr '/' unary_expr
    { $$ = create_binary_expr(BINARY_DIV, $1, $3); }
    | mul_expr '%' unary_expr
    { $$ = create_binary_expr(BINARY_REM, $1, $3); }
;

unary_expr : primary_expr
    { $$ = $1; }
    | '+' unary_expr
    { $$ = create_unary_expr(SINGLE_POSITIVE, $2); }
    | '-' unary_expr
    { $$ = create_unary_expr(SINGLE_NEGTIVE, $2); }
    | NOT unary_expr
    { $$ = create_unary_expr(SINGLE_NOT, $2); }
;

primary_expr : LVal
    { $$ = $1;}
    | INT_CONST
    { $$ = create_primary_INTCONST(stoi(*($1)));  }
    | FLOAT_CONST
    { $$ = create_primary_FLOATCONST(stof(*($1)));  }
    | '(' expr ')'
    { $$ = $2; }
    | func_call
    { $$ = $1; }
;

func_call : IDENTIFIER '(' ')'
    { $$ = create_func_call(*($1),nullptr); }
    | IDENTIFIER '(' expr_list ')'
    { $$ = create_func_call(*($1), $3); }
;

expr_list : expr
    {   $$ = $1; }
    | expr_list ',' expr{   
        $$ = $1; 
        Expression* exp=$$;
        while(exp->next!=nullptr)
            exp=exp->next;
        exp->next=$3;
    }
;

const_exp : add_expr
    { $$ = $1; }
;

const_init_val : 
    {   $$=new Expression(new LLVMList(),nullptr); }
    |const_exp
    {   
        $$=$1;
    }
    | '{' 
    {
        array_initial.push(array_init_idx);
    }
    const_init_list '}'{
        reduce_var_init_list($3);
        $$=$3;
    }
;

const_init_list : const_init_val{   
        $$ = $1;
        create_var_init_list($$);
    }
    | const_init_list ',' const_init_val{
        $$ = $1;
        create_var_init_list($$,$3);
    }
;

var_init_val : 
    {   $$=new Expression(new LLVMList(),nullptr); }
    |expr
    {   
        $$=$1;
    }
    | '{' 
    {
        array_initial.push(array_init_idx);
    }
    var_init_list '}'{
        reduce_var_init_list($3);
        $$=$3;
    }
;

var_init_list : var_init_val{   
        $$ = $1;
        create_var_init_list($$);
    }
    | var_init_list ',' var_init_val{
        $$ = $1;
        create_var_init_list($$,$3);
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(1);
}