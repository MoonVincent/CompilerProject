%{
#include<stdio.h>
%}

digit [0-9]
letter [_a-zA-Z]
%%
struct {printf("STRUCT\n");}//{return STRUCT;}
return {printf("RETURN\n");}//{return RETURN;}
if {printf("IF\n");}//{return IF;}
else {printf("ELSE\n");}//{return ELSE;}
while {printf("WHILE\n");}//{return WHILE;}
"int"|"float" {printf("TYPE\n");}//{return TYPE;}
{digit}+ {printf("INT\n");}//{return INT;}
[+−]?([0-9]*\.?[0-9]+|[0-9]+\.) {printf("FLOAT");}//{return FLOAT;}
{letter}+[_0-9a-zA-Z]* {printf("ID\n");}//{return ID;}
; {printf("SEMI\n");}//{return SEMI;}
, {printf("COMMA\n");}//{return COMMA;}
= {printf("ASSIGNOP\n");}//{return ASSIGNOP;}
>|<|>=|<=|==|!= {printf("RELOP\n");}//{return RELOP;}
"+" {printf("PLUS\n");}//{return PLUS;}
"-" {printf("MINUS\n");}//{return MINUS;}
"*" {printf("STAR\n");}//{return STAR;}
"/" {printf("DIV\n");}//{return DIV;}
"&&" {printf("AND\n");}//{return AND;}
"||" {printf("OR\n");}//{return OR;}
"." {printf("DOT\n");}//{return DOT;}
"!" {printf("NOT\n");}//{return NOT;}
"(" {printf("LP\n");}//{return LP;}
")" {printf("RP\n");}//{return RP;}
"[" {printf("LB\n");}//{return LB;}
"]" {printf("RB\n");}//{return RB;}
"{" {printf("LC\n");}//{return LC;}
"}" {printf("RC\n");}//{return RC;}
. {}
%%
int main(int argc, char **argv)
{
    FILE *fin=fopen(argv[1],"r");
    yyin=fin;
    yylex();
    return 0;
}