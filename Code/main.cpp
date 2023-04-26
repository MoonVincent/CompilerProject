#include "syntax.tab.hpp"
#include "syntaxNode.hpp"
extern int yyparse();
extern void yyrestart(FILE*);
extern tree syntaxTree;
extern int yydebug;

int main(int argc, char** argv) {
    FILE* f = fopen(argv[1],"r");
    yyrestart(f);
    //yydebug=1;
    yyparse();
    printTree(syntaxTree);
    return 0;
}
