#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "syntaxNode.hpp"
#include "type.hpp"
void semantic(tree syntaxTree);
void ExtDefList(tree root, std::list<std::string>& record_struct);
void ExtDef(tree root, std::list<std::string>& record_struct);
void ExtDef(tree root, std::list<std::string>& record_struct);
void ExtDecList(Type type, tree root, std::list<std::string>& record);
Type Specifier(tree root, std::list<std::string>& record_struct);
Type StructSpecifier(tree root, std::list<std::string>& record_struct);
std::string OptTag(tree root);
std::string Tag(tree root);
int VarDec(Type type, tree root, std::list<std::string>& record);
void FunDec(Type rv_type, tree root, std::list<std::string>& record,
            std::list<std::string>& record_struct);
void VarList(std::vector<Type>& paramList, tree root,
             std::list<std::string>& record,
             std::list<std::string>& record_struct);
void ParamDec(std::vector<Type>& paramList, tree root,
              std::list<std::string>& record,
              std::list<std::string>& record_struct);
void CompSt(tree root, std::list<std::string>& record, Type& ret,
            std::list<std::string>& record_struct);
void StmtList(tree root, Type& ret);
void Stmt(tree root, Type& ret);
void DefList(tree root, std::list<std::string>& record,
             std::list<std::string>& record_struct);
void Def(tree root, std::list<std::string>& record,
         std::list<std::string>& record_struct);
void DecList(Type type, tree root, std::list<std::string>& record);
void Dec(Type type, tree root, std::list<std::string>& record);
std::pair<Type, bool> Exp(tree root);
bool Args(tree root, Type func_type, int paramNo);
