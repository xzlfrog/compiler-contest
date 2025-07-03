%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
int yylex(void);

/* 假设的语义动作函数声明 */
void* create_comp_unit(void* decl_or_func);
void* create_decl(void* const_or_var_decl);
void* create_const_decl(char* type, void* const_def_list);
void* create_var_decl(char* type, void* var_def_list);
void* create_const_def(char* id, void* dim_list, void* init_val);
void* create_var_def(char* id, void* dim_list, void* init_val);
void* create_func_def(char* ret_type, char* id, void* params, void* block);
void* create_block(void* decl_list, void* stmt_list);
void* create_if_stmt(void* cond, void* then_stmt, void* else_stmt);
void* create_while_stmt(void* cond, void* stmt);
void* create_return_stmt(void* expr);
void* create_assign_stmt(char* id, void* expr);
void* create_binary_expr(int op, void* left, void* right);
void* create_unary_expr(int op, void* expr);
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

%type <ast_node> comp_unit decl const_decl var_decl const_def var_def
%type <ast_node> func_def block stmt expr const_exp init_val
%type <ast_node> func_param func_params func_call array_access
%type <ast_node> const_init_val var_init_val dim_list index_list

%start comp_unit

%%

comp_unit : decl_or_func_list
    { $$ = create_comp_unit($1); }
;

decl_or_func_list : decl_or_func
    | decl_or_func_list decl_or_func
;

decl_or_func : decl
    { $$ = create_decl($1); }
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
;

var_def_list : var_def
    | var_def_list ',' var_def
;

const_def : IDENTIFIER dim_list '=' const_init_val
    { $$ = create_const_def($1, $2, $4); }
;

var_def : IDENTIFIER dim_list
    { $$ = create_var_def($1, $2, NULL); }
    | IDENTIFIER dim_list '=' var_init_val
    { $$ = create_var_def($1, $2, $4); }
;

dim_list : /* empty */
    { $$ = NULL; }
    | '[' const_exp ']' dim_list
;

func_def : func_type IDENTIFIER '(' func_params ')' block
    { $$ = create_func_def($1, $2, $4, $6); }
;

func_type : VOID
    { $$ = "void"; }
    | btype
    { $$ = $1; }
;

func_params : /* empty */
    { $$ = NULL; }
    | func_param_list
;

func_param_list : func_param
    | func_param_list ',' func_param
;

func_param : btype IDENTIFIER
    | btype IDENTIFIER '[' ']' dim_list
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
    { $$ = NULL; }
    | block_items stmt
;

stmt : expr ';'
    | block
    | IF '(' expr ')' stmt
    { $$ = create_if_stmt($3, $5, NULL); }
    | IF '(' expr ')' stmt ELSE stmt
    { $$ = create_if_stmt($3, $5, $7); }
    | WHILE '(' expr ')' stmt
    { $$ = create_while_stmt($3, $5); }
    | BREAK ';'
    | CONTINUE ';'
    | RETURN expr ';'
    { $$ = create_return_stmt($2); }
    | RETURN ';'
    { $$ = create_return_stmt(NULL); }
;

expr : IDENTIFIER '=' expr
    { $$ = create_assign_stmt($1, $3); }
    | or_expr
    { $$ = $1; }
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
    | INT_CONST
    | FLOAT_CONST
    | '(' expr ')'
    { $$ = $2; }
    | func_call
    { $$ = $1; }
    | array_access
    { $$ = $1; }
;

func_call : IDENTIFIER '(' ')'
    { $$ = create_func_call($1, NULL); }
    | IDENTIFIER '(' expr_list ')'
    { $$ = create_func_call($1, $3); }
;

expr_list : expr
    | expr_list ',' expr
;

array_access : IDENTIFIER '[' expr ']'
    { $$ = create_array_access($1, $3); }
    | array_access '[' expr ']'
;

const_exp : add_expr
    { $$ = $1; }
;

const_init_val : const_exp
    | '{' const_init_list '}'
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