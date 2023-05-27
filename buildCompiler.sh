bash ./src/parser/build.sh
g++ ./main.cpp ./src/parser/syntax.tab.cpp ./src/semantic/semantic.cpp ./src/semantic/type.cpp ./src/global.cpp ./src/parser/syntaxNode.cpp ./src/irGen/intercode.cpp ./src/codeGen/assemble.cpp -ly -o ./Compiler