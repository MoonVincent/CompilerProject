bison -d -t -v syntax.ypp
flex lexical.l
g++ main.cpp syntax.tab.cpp syntaxNode.cpp semantic.cpp type.cpp global.cpp -ly -o parser -std=c++11