#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "syntaxNode.hpp"
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
#define ARRAY_PARAM_NUM 2
#define STRUCTURE_PARAM_NUM 3
#define FUNC_PARAM_NUM 3
/**
 * kind:当前元素的类型
 *  INT 类型为整型
 *  FLOAT 类型为浮点型
 *  ARRAY 类型为数组
 *  STRUCTURE 类型为结构体
 *  FUNC 类型为函数
 * u:对应类型对应的具体信息
 *  array 存储元素类型和个数
 *  structure 存储可嵌套的FieldList
 *  func 存储返回值类型、参数个数和各参数类型
 *
 */
typedef enum Kind_ {
  INT_SEMA,
  FLOAT_SEMA,
  ARRAY_SEMA,
  STRUCTURE_SEMA,
  FUNC_SEMA
} Kind_SEMA;
struct Type_ {
  Kind_SEMA kind;
  union {
    struct {
      Type elemType;
      int elemSize;
    } array;
    FieldList structure;
    struct {
      Type rv;
      int paraNum;
      Type* paramList;
    } func;
  } u;
};

/**
 * name 域的名字
 * type 域的类型
 * tail 连接到下一个FieldList_
 *
 */

struct FieldList_ {
  std::string name;
  Type type;
  FieldList tail;
};

Type newBasic(Kind_SEMA kind);
Type newArray(Type elemType, int elemSize);
Type newStructure(std::unordered_map<std::string, Type> members);
Type newFunc(Type rv, std::vector<Type>& paramTypes);
Type copyType(Type src);
FieldList newFieldList(std::string name, Type type);
void deleteFieldList(FieldList fieldList);
FieldList copyFieldList(FieldList fieldList);
bool isEquivalent(Type type1, Type type2);
void deleteType(Type type);

Type getItem(std::string key);
void deleteItem(std::string key);
bool insertItem(std::string key, Type type);
Type getFieldType(FieldList target, std::string name);
bool isLeftValue(Type type);
Type getFuncItem(std::string key);
void deleteFuncItem(std::string key);
bool insertFuncItem(std::string key, Type type);
Type getArrayElemType(Type type, int level);
Type getArrayType(tree root, int& array_depth);
bool insertStructItem(std::string key, Type type);
void deleteStructItem(std::string key);
Type getStructItem(std::string key);
