#include "./src/include/assemble.hpp"
#include "./src/include/intercode.hpp"
#include "./src/include/semantic.hpp"
#include "./src/include/syntax.tab.hpp"
#include "./src/include/syntaxNode.hpp"

extern int yyparse();
extern void yyrestart(FILE*);
extern tree syntaxTree; //语法树根节点
extern bool semanticError;  //是否发生语义错误
extern std::vector<int> syntaxErrorLines; //语法错误发生的行号
const std::string buildPath = "./build/"; //编译输入的源代码时，产生的中间文件存放地址
extern std::string fileName;  //输入的文件名
/**
 * @brief 从输入的路径中获取文件名
 * 
 */
void getFileName();

int main(int argc, char** argv) {
  //打开文件
  FILE* f = fopen(argv[1], "r");
  if (f == nullptr) {
    std::cout << "No such file" << std::endl;
    exit(-1);
  }
  //获取文件名
  fileName = argv[1];
  getFileName();
  //进行词法和语法分析
  yyrestart(f);
  yyparse();
  fclose(f);
  //如果发生了语法错误，打印提示信息并退出
  if (syntaxErrorLines.size() > 0) {
    for (int syntaxErrorLine : syntaxErrorLines) {
      std::cout << "[line " << syntaxErrorLine << " syntax error]" << std::endl;
    }
    exit(-1);
  }
  //输出语法树到./build/tree.txt
  printTree(syntaxTree);
  //语义分析
  semantic(syntaxTree);
  //发生语义错误就推出
  if (semanticError) {
    exit(-1);
  }
  //生成中间代码
  translate_Program(syntaxTree);
  //输出生成的IR
  std::ofstream ir(buildPath + fileName + ".ir");
  printInterCodes(ir, head);
  //指令选择
  selectInstr(head);
  //输出指令选择生成的指令序列
  std::ofstream sr(buildPath + fileName + ".sr");
  printSelectedInstr(sr, instrListHead);
  //输出活跃分析记录，活跃分析与指令选择同时进行
  std::ofstream livenessRecord(buildPath + fileName + ".i");
  printActiveRecord(livenessRecord);
  //初始化RISC-V 32个寄存器的信息
  initializeRegs();
  //寄存器分配
  allocateRegister();
  //输出目标代码
  std::ofstream code(buildPath + fileName + ".s");
  printAllocatedInstr(code, instrListHead);

  return 0;
}

/**
 * @brief 获取输入的文件名
 * 
 */
void getFileName() {
  int begin = 0, end;
  end = fileName.length() - 4;  //去掉.cmm
  for (int i = fileName.length() - 1; i >= 0; --i) {
    if (fileName[i] == '/') {
      begin = i;
      break;
    }
  }
  fileName = fileName.substr(begin, end - begin); //去掉路径信息
}
