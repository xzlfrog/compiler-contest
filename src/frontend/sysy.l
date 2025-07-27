%{
#include "sysy.y.hpp"
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
extern FILE* yyin;
extern int yyparse();
#include<stdio.h>
int yylex();
%}
%option yylineno
%option nounput 
%option noinput 
%%
"//".*      /* skip single-line comments */
"/*"([^*]|(\*+[^*/]))*\*+"/"  /* skip multi-line comments */
"int"       { return INT; }
"float"     { return FLOAT; }
"const"     { return CONST; }
"void"      { return VOID; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"return"    { return RETURN; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"%"         { return '%'; }
"=="        { return EQ; }
"!="        { return NE; }
"<"         { return LT; }
">"         { return GT; }
"<="        { return LE; }
">="        { return GE; }
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }
"="         { return '='; }
";"         { return ';'; }
","         { return ','; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
"["         { return '['; }
"]"         { return ']'; }
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = new std::string(yytext);
    return IDENTIFIER;
}

0[xX]([0-9a-fA-F]+\.[0-9a-fA-F]*|\.[0-9a-fA-F]+|[0-9a-fA-F]+\.)[pP][-+]?[0-9]+ {
    yylval.str = new std::string(yytext);
    return FLOAT_CONST;
}

([0-9]*\.[0-9]+|[0-9]+\.)[eE][-+]?[0-9]+ {
    yylval.str = new std::string(yytext);
    return FLOAT_CONST;
}

[0-9]+[eE][-+]?[0-9]+ {
    yylval.str = new std::string(yytext);
    return FLOAT_CONST;
}

([0-9]*\.[0-9]+|[0-9]+\.) {
    yylval.str = new std::string(yytext);
    return FLOAT_CONST;
}

0[xX][0-9a-fA-F]+ {
    yylval.str = new std::string(yytext);
    return INT_CONST;
}

0[1-7][0-7]* {
    yylval.str = new std::string(yytext);
    return INT_CONST;
}

"0" {
    yylval.str = new std::string(yytext);
    return INT_CONST;
}

[1-9][0-9]* {
    yylval.str = new std::string(yytext);
    return INT_CONST;
}

[ \t\n\r\v\f]     ; /* skip whitespace */
. {
    yyerror("Invalid character");
}
%%
int yywrap() {
    return 1;
}