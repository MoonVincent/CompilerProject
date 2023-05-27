#include "./src/include/assemble.hpp"
#include "./src/include/intercode.hpp"
#include "./src/include/semantic.hpp"
#include "./src/include/syntax.tab.hpp"
#include "./src/include/syntaxNode.hpp"

extern int yyparse();
extern void yyrestart(FILE*);
extern tree syntaxTree;
extern bool semanticError;
extern std::vector<int> syntaxErrorLines;
extern int yydebug;

int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  if (f == nullptr) {
    std::cout << "No such file" << std::endl;
    exit(-1);
  }
  yyrestart(f);
  yyparse();
  fclose(f);
  if (syntaxErrorLines.size() > 0) {
    for (int syntaxErrorLine : syntaxErrorLines) {
      std::cout << "[line " << syntaxErrorLine << " syntax error]" << std::endl;
    }
    exit(-1);
  }
  printTree(syntaxTree);
  semantic(syntaxTree);
  if (semanticError) {
    exit(-1);
  }
  translate_Program(syntaxTree);
  std::ofstream ir("test.ir");
  printInterCodes(ir, head);
  selectInstr(head);

  return 0;
}
