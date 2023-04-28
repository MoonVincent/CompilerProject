#pragma once
#include "syntaxNode.hpp"
#include "type.hpp"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
void semantic(tree syntaxTree);
void ExtDefList(tree root);
void ExtDef(tree root);
void ExtDef(tree root);
void ExtDecList(Type type, tree root, std::list<std::string>& record);
Type Specifier(tree root);
Type StructSpecifier(tree root);
std::string OptTag(tree root);
std::string Tag(tree root);
int VarDec(Type type, tree root, std::list<std::string>& record);
void FunDec(Type rv_type, tree root, std::list<std::string>& record);
void VarList(std::vector<Type>& paramList, tree root, std::list<std::string>& record);
void ParamDec(std::vector<Type>& paramList, tree root, std::list<std::string>& record);
void CompSt(tree root, std::list<std::string>& record);
void StmtList(tree root);
void Stmt(tree root);
void DefList(tree root, std::list<std::string>& record);
void Def(tree root, std::list<std::string>& record);
void DecList(Type type, tree root, std::list<std::string>& record);
void Dec(Type type, tree root, std::list<std::string>& record);
std::pair<Type, bool> Exp(tree root);
bool Args(tree root, Type func_type, int paramNo);
