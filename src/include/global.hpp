#pragma once
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>

#include "intercode.hpp"
#include "syntaxNode.hpp"
#include "type.hpp"
extern std::unordered_map<std::string, std::stack<Type>> symTable;
extern std::unordered_map<std::string, std::stack<Type>> funcTable;
extern std::unordered_map<std::string, std::stack<Type>> structTable;
//struct T {
//    int a;
//    int b;
//};
//struct T t; FieldList fields = getStructItem(T);
//DEC 16 v0
//t.a fields.name = a 2
extern std::unordered_map<std::string, std::stack<Operand>> valueTable;
extern std::unordered_map<std::string, std::string> dimensionTable;
