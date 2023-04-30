#include "global.hpp"
std::unordered_map<std::string, std::stack<Type>> symTable;
std::unordered_map<std::string, std::stack<Type>> funcTable;
std::unordered_map<std::string, std::stack<Type>> structTable;