bison -d ./src/parser/syntax.ypp
flex ./src/parser/lexical.l
mv ./syntax.tab.cpp ./src/parser/
cp ./syntax.tab.hpp ./src/parser/
mv ./syntax.tab.hpp ./src/include/
mv ./lex.yy.c ./src/parser/