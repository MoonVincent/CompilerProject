#include "syntax.tab.hpp"
#include "syntaxNode.hpp"
#include "semantic.hpp"
#include "intercode.hpp"
extern int yyparse();
extern void yyrestart(FILE*);
extern tree syntaxTree;
extern int yydebug;

int main(int argc, char** argv) {
    FILE* f = fopen(argv[1],"r");
    yyrestart(f);
    yyparse();
    printTree(syntaxTree);
    semantic(syntaxTree);
    translate_Program(syntaxTree);
    return 0;
}
