bison -d -t -v syntax.ypp
flex lexical.l
g++ main.cpp syntax.tab.cpp syntaxNode.cpp -ly -o parser