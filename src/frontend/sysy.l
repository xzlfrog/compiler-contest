%{
#include "sysy.tab.h"
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
%}

%option yylineno

%%

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
    yylval.string = strdup(yytext);
    return IDENTIFIER;
}

[0-9]+ {
    yylval.string = strdup(yytext);
    return INT_CONST;
}

[0-9]+"."[0-9]* {
    yylval.string = strdup(yytext);
    return FLOAT_CONST;
}

"//".*      /* skip single-line comments */
"/*"(.|\n)*"*/"  /* skip multi-line comments */

[ \t\n]     ; /* skip whitespace */

. {
    yyerror("Invalid character");
}

%%

int yywrap() {
    return 1;
}