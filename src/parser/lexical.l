%{
#include "stdio.h"
#include "syntax.tab.hpp"
#include "syntaxNode.hpp"
std::string preProcess(std::string str);
%}

digit [0-9]
letter [_a-zA-Z]
%option yylineno
%option noyywrap

%%
"struct" {yylval.node = buildTree(0, yylineno, true, "STRUCT", yytext); return STRUCT; }
"return" {yylval.node = buildTree(0, yylineno, true, "RETURN", yytext); return RETURN; }
"if" {yylval.node = buildTree(0, yylineno, true, "IF", yytext); return IF; }
"else" {yylval.node = buildTree(0, yylineno, true, "ELSE", yytext); return ELSE; }
"while" {yylval.node = buildTree(0, yylineno, true, "WHILE", yytext); return WHILE; }
"int"|"float"|"string" {yylval.node = buildTree(0, yylineno, true, "TYPE", yytext); return TYPE; }
\".*\" {std::string x(yytext);yylval.node = buildTree(0, yylineno, true, "STRING", x.c_str()); return STRING;}
[0-9]+ {yylval.node = buildTree(0, yylineno, true, "INT", yytext); return INT; }
[+-]?([0-9]*\.[0-9]+|[0-9]+\.) {yylval.node = buildTree(0, yylineno, true, "FLOAT", yytext); return FLOAT; }
[_a-zA-Z][a-z0-9A-Z]* {yylval.node = buildTree(0, yylineno, true, "ID", yytext); return ID;}
";" {yylval.node = buildTree(0, yylineno, true, "SEMI", yytext); return SEMI; }
"," {yylval.node = buildTree(0, yylineno, true, "COMMA", yytext); return COMMA; }
"=" {yylval.node = buildTree(0, yylineno, true, "ASSIGNOP", yytext); return ASSIGNOP; }
">"|"<"|">="|"<="|"=="|"!=" {yylval.node = buildTree(0, yylineno, true, "RELOP", yytext); return RELOP; }
"+" {yylval.node = buildTree(0, yylineno, true, "PLUS", yytext); return PLUS; }
"-" {yylval.node = buildTree(0, yylineno, true, "MINUS", yytext); return MINUS; }
"*" {yylval.node = buildTree(0, yylineno, true, "STAR", yytext); return STAR; }
"/" {yylval.node = buildTree(0, yylineno, true, "DIV", yytext); return DIV; }
"&&" {yylval.node = buildTree(0, yylineno, true, "AND", yytext); return AND; }
"||" {yylval.node = buildTree(0, yylineno, true, "OR", yytext); return OR; }
"." {yylval.node = buildTree(0, yylineno, true, "DOT", yytext); return DOT; }
"!" {yylval.node = buildTree(0, yylineno, true, "NOT", yytext); return NOT; }
"(" {yylval.node = buildTree(0, yylineno, true, "LP", yytext); return LP; }
")" {yylval.node = buildTree(0, yylineno, true, "RP", yytext); return RP; }
"[" {yylval.node = buildTree(0, yylineno, true, "LB", yytext); return LB; }
"]" {yylval.node = buildTree(0, yylineno, true, "RB", yytext); return RB; }
"{" {yylval.node = buildTree(0, yylineno, true, "LC", yytext); return LC; }
"}" {yylval.node = buildTree(0, yylineno, true, "RC", yytext); return RC; }
"\n" {}
"\t" {}
" " {}
. { printf("Error type A at Line %d: Mysterious characters \'%s\'\n",  yylineno,  yytext);  } 
%%

std::string preProcess(std::string str) {

    str = str.substr(1, str.length() - 2); //去掉双引号
    int i = 0;
    while(1) {
        if (i >= str.length() - 1) {
            break;
        }
        if (str[i] == '\\') {
            switch(str[i + 1]){
                case 'n':{
                    str[i] = '\n';
                    str = str.erase(i + 1, 1);
                    break;
                }
                case '\"':{
                    str[i] = '\"';
                    str = str.erase(i + 1, 1);
                    break;
                }
            }
        }
        ++i;
    }
    return str;
}