%{
    #include "syntaxNode.hpp"
    #define NO_VALUE ""
    #define NO_LINE -1
%}

%union{
    tree node;
}

tree syntaxTree = nullptr;

%token <node> INT,FLOAT,ID,SEMI,COMMA,ASSIGNOP,RELOP,PLUS,MINUS,STAR
%token <node> DIV,AND,OR,DOT,NOT,TYPE,LP,RP,RB,LC,RC,STRUCT,RETURN,IF,ELSE,WHILE
%type <node> Program,ExtDefList,ExtDef,Specifier,ExtDecList,FunDec,CompSt,VarDec
%type <node> StructSpecifier,OptTag,DefList,Tag,VarList,ParamDec,StmtList,Stmt,Exp
%type <node> Dec,DecList,Args,Def
%%

    Program: ExtDefList {syntaxTree = buildTree(1, NO_LINE, false, "Program", NO_VALUE, $1);}
            ;
    
    ExtDefList: ExtDef ExtDefList {$$ = buildTree(2, NO_LINE, false, "ExtDefList", NO_VALUE, $1, $2);}
              | {$$ = nullptr;}
              ;
    
    ExtDef: Specifier ExtDecList SEMI {$$ = buildTree(3, NO_LINE, false, "ExtDef", NO_VALUE, $1, $2, $3);}
          | Specifier SEMI {$$ = buildTree(2, NO_LINE, false, "ExtDef", NO_VALUE, $1, $2);}
          | Specifier FunDec Compt {$$ = buildTree(3, NO_LINE, false, "ExtDef", NO_VALUE, $1, $2, $3);}
          ;
    
    ExtDecList: VarDec {$$ = buildTree(1, NO_LINE, false, "ExtDecList", NO_VALUE, $1);}
              | VarDec COMMA ExtDecList {$$ = buildTree(3, NO_LINE, false, "ExtDecList", NO_VALUE, $1, $2, $3);}
              ;
    
    Specifier: TYPE {$$ = buildTree(1, NO_LINE, false, "Specifier", NO_VALUE, $1);}
             | StructSpecifier {$$ = buildTree(1, NO_LINE, false, "Specifier", NO_VALUE, $1);}
             ;
    
    StructSpecifier: STRUCT OptTag LC DefList RC {$$ = buildTree(5, NO_LINE, false, "StructSpecifier", NO_VALUE, $1, $2, $3, $4, $5);}
                   | STRUCT Tag {$$ = buildTree(2, NO_LINE, false, "StructSpecifier", NO_VALUE, $1, $2);}
                   ;
    
    OptTag: ID {$$ = buildTree(1, NO_LINE, false, "OptTag", NO_VALUE, $1);}
          ;
    
    Tag: ID {$$ = buildTree(1, NO_LINE, false, "Tag", NO_VALUE, $1);}
       ;

    VarDec: ID {$$ = buildTree(1, NO_LINE, false, "VarDec", NO_VALUE, $1);}
          | VarDec LB INT RB {$$ = buildTree(4, NO_LINE, false, "VarDec", NO_VALUE, $1, $2, $3, $4);}
          ;
    
    FunDec: ID LP VarList RP {$$ = buildTree(4, NO_LINE, false, "FunDec", NO_VALUE, $1, $2, $3, $4);}
          | ID LP RP {$$ = buildTree(3, NO_LINE, false, "FunDec", NO_VALUE, $1, $2, $3);}
          ;
    
    VarList: ParamDec COMMA VarList {$$ = buildTree(3, NO_LINE, false, "VarList", NO_VALUE, $1, $2, $3);}
           | ParamDec {$$ = buildTree(1, NO_LINE, false, "VarList", NO_VALUE, $1);}
           ;
    
    ParamDec: Specifier VarDec {$$ = buildTree(2, NO_LINE, false, "ParamDec", NO_VALUE, $1, $2);}
            ;

        

