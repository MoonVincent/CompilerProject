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
extern std::unordered_map<std::string, std::stack<Operand>> valueTable;
extern std::unordered_map<std::string, std::string> dimensionTable;
extern std::string fileName;
