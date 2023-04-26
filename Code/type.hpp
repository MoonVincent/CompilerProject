#pragma once
#include <string>
#include <vector>
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
typedef enum Kind_ {INT, FLOAT, ARRAY, STRUCTURE, FUNC} Kind;
struct Type_{
    Kind kind;
    union {
        struct {Type elemType; int elemSize;} array;
        FieldList structure;
        struct {Type rv; int paraNum; Type* paramList;} func;
    } u;
};

/**
 * name 域的名字
 * type 域的类型
 * tail 连接到下一个FieldList_
 * 
*/

struct FieldList_{
    std::string name;
    Type type;
    FieldList tail;
};

Type newBasic(Kind kind);
Type newArray(Type elemType, int elemSize);
Type newStructure(std::unordered_map<std::string, Type> members);
Type newFunc(Type rv, std::vector<Type>& paramTypes);
Type copyType(Type src);
FieldList newFieldList(std::string name, Type type);
void deleteFieldList(FieldList fieldList);
FieldList copyFieldList(FieldList fieldList);
Type getType(std::string key);
bool isEquivalent(Type type1, Type type2);
bool insertType(std::string key, Type type);
void deleteType(std::string key);
