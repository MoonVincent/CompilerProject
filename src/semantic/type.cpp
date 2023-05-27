#include "../include/type.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>

#include "../include/global.hpp"
/**
 * @brief 新建INT/FLOAT类型
 *
 * @param kind:标明是INT还是FLOAT
 * @return Type 指向该INT/FLOAT类型的指针
 */
Type newBasic(Kind_SEMA kind) {
  Type type = new Type_();
  type->kind = kind;
  return type;
}
/**
 * @brief 新建一个数组类型
 *
 * @param elemType 数组中元素的类型
 * @param elemSize 数组元素个数
 * @return Type 指向该数组类型的指针
 */
Type newArray(Type elemType, int elemSize) {
  Type type = new Type_();
  type->kind = ARRAY_SEMA;
  type->u.array.elemType = elemType;
  type->u.array.elemSize = elemSize;
  return type;
}
/**
 * @brief 新建一个结构体类型
 *
 * @param members 一个域名和域类型的对应表
 * @return Type 指向该结构体类型的指针
 */
Type newStructure(std::vector<std::pair<std::string, Type>> members) {
  Type type = new Type_();
  type->kind = STRUCTURE_SEMA;

  FieldList dummyNode = new FieldList_();
  dummyNode->tail = nullptr;
  FieldList cur = dummyNode;
  for (auto member : members) {
    cur->tail = newFieldList(member.first, member.second);
    cur = cur->tail;
  }
  type->u.structure = dummyNode->tail;
  return type;
}

Type newFunc(Type rv, std::vector<Type>& paramTypes) {
  Type type = new Type_();
  type->kind = FUNC_SEMA;
  type->u.func.rv = rv;
  type->u.func.paraNum = paramTypes.size();
  type->u.func.paramList = new Type[paramTypes.size()];
  for (int i = 0; i < paramTypes.size(); ++i) {
    type->u.func.paramList[i] = paramTypes[i];
  }
  return type;
}

Type copyType(Type src) {
  Type type = new Type_();
  type->kind = src->kind;
  switch (src->kind) {
    case INT_SEMA:
    case FLOAT_SEMA:
      break;
    case ARRAY_SEMA: {
      type->u.array.elemType = copyType(src->u.array.elemType);
      type->u.array.elemSize = src->u.array.elemSize;
      break;
    }
    case FUNC_SEMA: {
      type->u.func.rv = copyType(src->u.func.rv);
      type->u.func.paraNum = src->u.func.paraNum;
      type->u.func.paramList = new Type[type->u.func.paraNum];
      for (int i = 0; i < type->u.func.paraNum; ++i) {
        type->u.func.paramList[i] = copyType(src->u.func.paramList[i]);
      }
      break;
    }
    case STRUCTURE_SEMA: {
      type->u.structure = copyFieldList(src->u.structure);
      break;
    }
  }
  return type;
}

void deleteType(Type type) {
  switch (type->kind) {
    case INT_SEMA:
    case FLOAT_SEMA:
      break;
    case FUNC_SEMA: {
      deleteType(type->u.func.rv);
      for (int i = 0; i < type->u.func.paraNum; ++i) {
        deleteType(type->u.func.paramList[i]);
      }
      break;
    }
    case ARRAY_SEMA: {
      deleteType(type->u.array.elemType);
      break;
    }
    case STRUCTURE_SEMA: {
      deleteFieldList(type->u.structure);
      break;
    }
  }
  delete type;
}

FieldList newFieldList(std::string name, Type type) {
  FieldList fieldList = new FieldList_();
  fieldList->name = name;
  fieldList->type = type;
  fieldList->tail = nullptr;
  return fieldList;
}

void deleteFieldList(FieldList fieldList) {
  FieldList cur = fieldList;
  while (cur) {
    FieldList next = cur->tail;
    delete cur;
    cur = next;
  }
}

FieldList copyFieldList(FieldList fieldList) {
  if (fieldList == nullptr) {
    return nullptr;
  }
  FieldList newList = new FieldList_();
  newList->name = fieldList->name;
  newList->type = fieldList->type;
  newList->tail = copyFieldList(fieldList->tail);
}

Type getItem(std::string key) {
  auto target = symTable.find(key);
  if (target == symTable.end()) {
    return nullptr;
  } else {
    if (target->second.size() == 0) {
      return nullptr;
    } else {
      return target->second.top();
    }
  }
}

bool insertItem(std::string key, Type type) {
  auto target = symTable.find(key);
  if (target == symTable.end()) {
    std::stack<Type> tmp;
    tmp.push(type);
    symTable.insert({key, tmp});
  } else {
    target->second.push(type);
  }

  return true;
}

void deleteItem(std::string key) {
  auto target = symTable.find(key);
  if (target == symTable.end()) {
    std::cout << "Error in deleteType" << std::endl;
  } else {
    if (target->second.size() == 0) {
      std::cout << "Error in deleteType" << std::endl;
    } else {
      target->second.pop();
    }
  }
}

Type getFuncItem(std::string key) {
  auto target = funcTable.find(key);
  if (target == funcTable.end()) {
    return nullptr;
  } else {
    if (target->second.size() == 0) {
      return nullptr;
    } else {
      return target->second.top();
    }
  }
}

bool insertFuncItem(std::string key, Type type) {
  auto target = funcTable.find(key);
  if (target == funcTable.end()) {
    std::stack<Type> tmp;
    tmp.push(type);
    funcTable.insert({key, tmp});
    return true;
  } else {
    return false;
  }
}

void deleteFuncItem(std::string key) {
  auto target = funcTable.find(key);
  if (target == funcTable.end()) {
    std::cout << "Error in deleteFuncItem" << std::endl;
  } else {
    if (target->second.size() == 0) {
      std::cout << "Error in deleteFuncItem" << std::endl;
    } else {
      target->second.pop();
    }
  }
}

Type getFieldType(FieldList target, std::string name) {
  while (target != nullptr) {
    if (name == target->name) {
      return target->type;
    }
    target = target->tail;
  }
  return nullptr;
}

bool isLeftValue(Type type) {
  if (type == nullptr) {
    return false;
  }
  if (type->kind == FUNC_SEMA || type->kind == INT_SEMA ||
      type->kind == FLOAT_SEMA) {
    return false;
  }
  return true;
}

Type getArrayElemType(Type type, int level) {  // EXP-> EXP LB EXP RB level = 1
  int count = 0;
  while (type->kind == ARRAY_SEMA) {
    type = type->u.array.elemType;
    ++count;
    if (count == level) {
      break;
    }
  }
  if (count < level) {
    return nullptr;
  } else {
    return type;
  }
}

Type getArrayType(tree root, int& array_depth) {
  Type type = nullptr;
  while (root && root->childCnt > 1) {
    ++array_depth;
    root = root->children[0];
  }
  if (root && root->childCnt == 1 && root->children[0]->key == "ID") {
    type = getItem(root->children[0]->value);
    if (type == nullptr) {
      std::cout << "[line " << root->children[0]->lineNo << " semantic error] "
                << "Undefined reference to variable "
                << root->children[0]->value << std::endl;
    }
  }
  return type;
}

bool isEquivalent(Type type1, Type type2) {
  if (type1 == nullptr || type2 == nullptr) {
    return false;
  }
  if (type1->kind == type2->kind) {
    switch (type1->kind) {
      case INT_SEMA:
      case FLOAT_SEMA:
        return true;
      case ARRAY_SEMA: {
        if (type1->u.array.elemSize != type2->u.array.elemSize) {
          return false;
        }
        return isEquivalent(type1->u.array.elemType, type2->u.array.elemType);
      }
      case FUNC_SEMA: {
        if (type1->u.func.rv != type2->u.func.rv ||
            type1->u.func.paraNum != type2->u.func.paraNum) {
          return false;
        }
        for (int i = 0; i < type1->u.func.paraNum; ++i) {
          if (!isEquivalent(type1->u.func.paramList[i],
                            type2->u.func.paramList[i])) {
            return false;
          }
        }
        return true;
      }
      case STRUCTURE_SEMA: {
        FieldList f1 = type1->u.structure;
        FieldList f2 = type2->u.structure;
        while (f1 && f2) {
          if (!isEquivalent(f1->type, f2->type)) {
            return false;
          }
          f1 = f1->tail;
          f2 = f2->tail;
        }
        if (f1 || f2) {
          return false;
        }
        return true;
      }
    }
  } else {
    return false;
  }
  return false;
}

bool insertStructItem(std::string key, Type type) {
  auto target = structTable.find(key);
  if (target == structTable.end()) {
    std::stack<Type> tmp;
    tmp.push(type);
    structTable.insert({key, tmp});
    return true;
  } else {
    return false;
  }
}

void deleteStructItem(std::string key) {
  auto target = structTable.find(key);
  if (target == structTable.end()) {
    std::cout << "Error in deleteType" << std::endl;
  } else {
    if (target->second.size() == 0) {
      std::cout << "Error in deleteType" << std::endl;
    } else {
      target->second.pop();
    }
  }
}

Type getStructItem(std::string key) {
  auto target = structTable.find(key);
  if (target == structTable.end()) {
    return nullptr;
  } else {
    if (target->second.size() == 0) {
      return nullptr;
    } else {
      return target->second.top();
    }
  }
}