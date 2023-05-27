#include "./include/global.hpp"
std::unordered_map<std::string, std::stack<Type>> symTable;
std::unordered_map<std::string, std::stack<Type>> funcTable;
std::unordered_map<std::string, std::stack<Type>> structTable;
std::unordered_map<std::string, std::stack<Operand>> valueTable;
std::unordered_map<std::string, std::string> dimensionTable;
std::string fileName;
