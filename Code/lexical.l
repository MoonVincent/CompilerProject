%{
#include<stdio.h>
#include"syntaxNode.hpp"
%}
%option yylineno
digit [0-9]
letter [_a-zA-Z]
%%
struct {yylval.node = buildTree(0,yylineno,true,"STRUCT",yytext,nullptr);return STRUCT;}
return {yylval.node = buildTree(0,yylineno,true,"RETURN",yytext,nullptr);return RETURN;}
if {yylval.node = buildTree(0,yylineno,true,"IF",yytext,nullptr);return IF;}
else {yylval.node = buildTree(0,yylineno,true,"ELSE",yytext,nullptr);return ELSE;}
while {yylval.node = buildTree(0,yylineno,true,"WHILE",yytext,nullptr);return WHILE;}
"int"|"float" {yylval.node = buildTree(0,yylineno,true,"TYPE",yytext,nullptr);return TYPE;}
{digit}+{yylval.node = buildTree(0,yylineno,true,"INT",yytext,nullptr);return INT;}
[+−]?([0-9]*\.?[0-9]+|[0-9]+\.) {yylval.node = buildTree(0,yylineno,true,"FLOAT",yytext,nullptr);return FLOAT;}
{letter}+[_0-9a-zA-Z]* {yylval.node = buildTree(0,yylineno,true,"ID",yytext,nullptr);return ID;}
; {yylval.node = buildTree(0,yylineno,true,"SEMI",yytext,nullptr);return SEMI;}
, {yylval.node = buildTree(0,yylineno,true,"COMMA",yytext,nullptr);return COMMA;}
= {yylval.node = buildTree(0,yylineno,true,"ASSIGNOP",yytext,nullptr);return ASSIGNOP;}
>|<|>=|<=|==|!= {yylval.node = buildTree(0,yylineno,true,"RELOP",yytext,nullptr);return RELOP;}
"+" {yylval.node = buildTree(0,yylineno,true,"PLUS",yytext,nullptr);return PLUS;}
"-" {yylval.node = buildTree(0,yylineno,true,"MINUS",yytext,nullptr);return MINUS;}
"*" {yylval.node = buildTree(0,yylineno,true,"STAR",yytext,nullptr);return STAR;}
"/" {yylval.node = buildTree(0,yylineno,true,"DIV",yytext,nullptr);return DIV;}
"&&" {yylval.node = buildTree(0,yylineno,true,"AND",yytext,nullptr);return AND;}
"||" {yylval.node = buildTree(0,yylineno,true,"OR",yytext,nullptr);return OR;}
"." {yylval.node = buildTree(0,yylineno,true,"DOT",yytext,nullptr);return DOT;}
"!" {yylval.node = buildTree(0,yylineno,true,"NOT",yytext,nullptr);return NOT;}
"(" {yylval.node = buildTree(0,yylineno,true,"LP",yytext,nullptr);return LP;}
")" {yylval.node = buildTree(0,yylineno,true,"RP",yytext,nullptr);return RP;}
"[" {yylval.node = buildTree(0,yylineno,true,"LB",yytext,nullptr);return LB;}
"]" {yylval.node = buildTree(0,yylineno,true,"RB",yytext,nullptr);return RB;}
"{" {yylval.node = buildTree(0,yylineno,true,"LC",yytext,nullptr);return LC;}
"}" {yylval.node = buildTree(0,yylineno,true,"RC",yytext,nullptr);return RC;}
\n|\t|" "  {}
. { printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); } 
%%