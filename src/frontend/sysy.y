%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/frontend/frontendtool.hpp"
#include "../../include/frontend/keyWordsTool.hpp"

void yyerror(const char *s);
int yylex(void);

/* 假设的语义动作函数声明 */
void* create_comp_unit(void* decl_or_func);
void* create_decl(void* const_or_var_decl);

LLVM* create_const_decl(std::string type, LLVM* const_def_list);
void* create_var_decl(char* type, void* var_def_list);

LLVM* create_const_def(std::string name,Data* const_exp; std::vector<int>& dimensions, std::vector<std::pair<std::vector<int>,Data*>> initializedData);
LLVM* create_const_def(std::string name, Data* data);

void* create_var_def(char* id, void* dim_list, void* init_val);
void* create_block(void* decl_list, void* stmt_list);

/* keyWordsTool.hpp */
LLVM* create_if_stmt(Expression* cond, LLVM* then_stmt, LLVM* else_stmt);
LLVM* create_if_stmt(Expression* cond, LLVM* then_stmt);

LLVM* create_while_stmt(Expression* cond, LLVM* stmt);
LLVM* create_while_stmt(Expression* cond, LLVM* stmt);
LLVM* create_break_stmt();
LLVM* create_return_stmt(Expression* expr);
LLVM* create_return_stmt();
LLVM* create_assign_stmt(std::string id, Expression* expr);

/* frontendTool.hpp */
Expression* create_primary_IDENTIFIER(std::string id);
Expression* create_primary_INTCONST(int value);
Expression* create_primary_FLOATCONST(float value);
Expression* create_binary_expr(int op, Expression* exp1, Expression* exp2);
Expression* create_unary_expr(int op, Expression* exp);

/*funcTool.hpp*/
FuncDefination* create_func_def(std::string returnDataTypeString, std::string name, std::vector<Symbol*> params, LLVM* blocks);
std::vector<BasicSymbol*> addToParams(BasicSymbol* param);
VarSymbol* create_param_nonarray(std::string paraType, std::sting name);
ArraySymbol* create_param_array(std::string paraType, std::string name, std::vector<int> dimensions);


void* create_func_call(char* id, void* args);
void* create_array_access(char* id, void* indices);

%}

%union {
    char* string;
    void* ast_node;
}

%token INT FLOAT CONST VOID
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token EQ NE LT GT LE GE AND OR NOT
%token <string> IDENTIFIER INT_CONST FLOAT_CONST

%type <ast_node> comp_unit decl const_decl var_decl var_def

%type <LLVM*> func_def
%type <std::vector<BasicSymbol*>> func_params func_params_list
%type <BasicSymbol*> func_param
%type <LLVM*> const_def const_def_list block stmt 
%type <Data*> const_exp
%type <Expression*> cond expr

%type <std::vector<int>> dim_list
%type <ast_node> init_val
%type <ast_node> func_call array_access
%type <ast_node> const_init_val var_init_val index_list

%start comp_unit

%%

comp_unit : decl_or_func_list
    { $$ = create_comp_unit($1); }
;

decl_or_func_list : decl_or_func
    | decl_or_func_list decl_or_func
    { $$ = LLVMList::InsertAfter($1,$2);}
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
    { $$ = create_const_decl($2, $3); }
;

var_decl : btype var_def_list ';'
    { $$ = create_var_decl($1, $2); }
;

btype : INT
    { $$ = "int"; }
    | FLOAT
    { $$ = "float"; }
;

const_def_list : const_def
    | const_def_list ',' const_def
    { $$ = LLVMList::InsertAfter($1,$2);}
;

var_def_list : var_def
    | var_def_list ',' var_def
    { $$ = LLVMList::InsertAfter($1,$2);}
;

const_def : IDENTIFIER '[' const_exp ']' dim_list '=' const_init_val
    { $$ = create_const_def($1, $3, $5, $7); 
      }
    | IDENTIFIER '=' const_init_val
    {
      $$ = create_const_def($1, $3); 
    }
;

var_def : IDENTIFIER dim_list
    { $$ = $1;
     create_var_def($1, $2); }
    | IDENTIFIER dim_list '=' var_init_val
    { $$ = $1;
    create_var_def($1, $2, $4); }
;

dim_list : /* empty */
    {   $$ = dimensions;}
    | '[' const_exp ']' dim_list
    {  
        $$ = do_dimensions($2,$4);
     }
;

func_def : func_type IDENTIFIER '(' func_params ')' block
    {   scope+=1;
        $$ = create_func_def($1, $2, $4, $6);
     }
;

func_type : VOID
    { $$ = "void"; }
    | btype
    { $$ = $1; }
;

func_params : /* empty */
    | func_param_list
;

func_param_list : func_param
    { $$ = addToParams($1);}
    | func_param_list ',' func_param
    { $$ = addToParams($3);}
;

func_param : btype IDENTIFIER
    { $$ = create_param_nonarray($1,$2); }
    | btype IDENTIFIER '[' ']' dim_list
    { $$ = create_param_array($1,$2,$5); }
;

block : '{' block_items '}'
    { $$ = create_block(NULL, $2); }
    | '{' decl_list block_items '}'
    { $$ = create_block($2, $3); }
;

decl_list : decl
    | decl_list decl
;

block_items : /* empty */
    {   scope-=1;
        $$ = NULL; }
    | block_items stmt
;

stmt : LVal '=' expr ';'
    {}
    | expr ';'
    | ';'
    | block
    | IF '(' cond ')' stmt
    { $$ = create_if_stmt($3, $5); }
    | IF '(' cond ')' stmt ELSE stmt
    { $$ = create_if_stmt($3, $5, $7); }
    | WHILE '(' cond ')' stmt
    { $$ = create_while_stmt($3, $5); }
    | BREAK ';'
    { $$ = create_break_stmt();}
    | CONTINUE ';'
    { $$ = create_continue_stmt();}
    | RETURN expr ';'
    { $$ = create_return_stmt($2); }
    | RETURN ';'
    { $$ = create_return_stmt(); }
;

expr : add_expr
    { $$ = $1; }
;

cond : or_expr
    { $$ = $1}
;

or_expr : and_expr
    | or_expr OR and_expr
    { $$ = create_binary_expr(OR, $1, $3); }
;

and_expr : eq_expr
    | and_expr AND eq_expr
    { $$ = create_binary_expr(AND, $1, $3); }
;

eq_expr : rel_expr
    | eq_expr EQ rel_expr
    { $$ = create_binary_expr(EQ, $1, $3); }
    | eq_expr NE rel_expr
    { $$ = create_binary_expr(NE, $1, $3); }
;

rel_expr : add_expr
    | rel_expr LT add_expr
    { $$ = create_binary_expr(LT, $1, $3); }
    | rel_expr GT add_expr
    { $$ = create_binary_expr(GT, $1, $3); }
    | rel_expr LE add_expr
    { $$ = create_binary_expr(LE, $1, $3); }
    | rel_expr GE add_expr
    { $$ = create_binary_expr(GE, $1, $3); }
;

add_expr : mul_expr
    | add_expr '+' mul_expr
    { $$ = create_binary_expr('+', $1, $3); }
    | add_expr '-' mul_expr
    { $$ = create_binary_expr('-', $1, $3); }
;

mul_expr : unary_expr
    | mul_expr '*' unary_expr
    { $$ = create_binary_expr('*', $1, $3); }
    | mul_expr '/' unary_expr
    { $$ = create_binary_expr('/', $1, $3); }
    | mul_expr '%' unary_expr
    { $$ = create_binary_expr('%', $1, $3); }
;

unary_expr : primary_expr
    | '+' unary_expr
    { $$ = create_unary_expr('+', $2); }
    | '-' unary_expr
    { $$ = create_unary_expr('-', $2); }
    | NOT unary_expr
    { $$ = create_unary_expr(NOT, $2); }
;

primary_expr : IDENTIFIER
    { $$ = create_primary_IDENTIFIER($1);}
    | IDENTIFIER '[' const_exp ']' dim_list
    { $$ = create_primary_ARRAY($1, $3, $5);}
    | INT_CONST
    { $$ = create_primary_INTCONST(stoi($1));  }
    | FLOAT_CONST
    { $$ = create_primary_FLOATCONST(stof($1));  }
    | '(' expr ')'
    { $$ = $2; }
    | func_call
    { $$ = $1; }
    | array_access
    { $$ = $1; }
;

func_call : IDENTIFIER '(' ')'
    { $$ = create_func_call($1, ); }
    | IDENTIFIER '(' expr_list ')'
    { $$ = create_func_call($1, $3); }
;

expr_list : expr
    | expr_list ',' expr
;

array_access : IDENTIFIER '[' expr ']'
    { $$ = create_array_access($1, $3); }
    | array_access '[' expr ']'
    {}
;

const_exp : add_expr
    { $$ = expShorten($1); }
;

const_init_val : const_exp
    {//转换为数据Data，并记录暂存————可插进数组？}
    | '{' const_init_list '}'
    {//将vector依次插入 i guess}
;

const_init_list : const_init_val
    | const_init_list ',' const_init_val
;

var_init_val : expr
    | '{' var_init_list '}'
;

var_init_list : var_init_val
    | var_init_list ',' var_init_val
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(1);
}

int main(int argc, char **argv) {
    yyparse();
    return 0;
}