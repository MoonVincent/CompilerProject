#pragma once
#include "type.hpp"
#include <unordered_map>
#include <stack>
#include <string>
#include <fstream>
extern std::unordered_map<std::string, std::stack<Type>> symTable;
