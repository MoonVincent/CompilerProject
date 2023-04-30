#pragma once
#include "type.hpp"
#include "syntaxNode.hpp"
#include <unordered_map>
#include <stack>
#include <string>
#include <fstream>
extern std::unordered_map<std::string, std::stack<Type>> symTable;
extern std::unordered_map<std::string, std::stack<Type>> funcTable;
extern std::unordered_map<std::string, std::stack<Type>> structTable;
extern std::unordered_map<std::string, std::stack<std::string>> regTable;
