#pragma once
#include "type.hpp"
#include <unordered_map>
#include <stack>
#include <string>
extern std::unordered_map<std::string, std::stack<Type>> symTable;
