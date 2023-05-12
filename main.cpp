#include "./src/include/syntax.tab.hpp"
#include "./src/include/syntaxNode.hpp"
#include "./src/include/semantic.hpp"
#include "./src/include/intercode.hpp"
#include "./src/include/assemble.hpp"
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
    
    return 0;
}