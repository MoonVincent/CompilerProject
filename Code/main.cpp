#include "syntax.tab.hpp"
#include "syntaxNode.hpp"
#include "semantic.hpp"
#include "intercode.hpp"
#include "assemble.hpp"
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
    std::ofstream ir("test.ir");
    printInterCodes(ir, head);
    selectInstr(head);
    std::cout << "Hello" << std::endl;
    std::ofstream sr("test.sr");
    printSelectedInstr(sr, instrListHead);
    return 0;
}
