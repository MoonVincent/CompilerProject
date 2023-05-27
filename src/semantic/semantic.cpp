#include "../include/semantic.hpp"

#include "../include/global.hpp"
bool semanticError = false;

/**
 * @brief 语义分析入口
 * 
 * @param syntaxTree 语法树根节点
 */
void semantic(tree syntaxTree) {
  std::list<std::string> record_struct;
  ExtDefList(syntaxTree->children[0], record_struct);
}
/**
 * @brief ExtDefList语义分析
 * 
 * @param root 子树根节点
 * @param record_struct 当前作用域内定义的struct的name集合
 */
void ExtDefList(tree root, std::list<std::string>& record_struct) {
  if (root == nullptr) {
    return;
  }
  ExtDef(root->children[0], record_struct);
  ExtDefList(root->children[1], record_struct);
}
/**
 * @brief ExtDef语义分析
 * 
 * @param root 子树根节点
 * @param record_struct 当前作用域内定义的struct的name集合
 */
void ExtDef(tree root, std::list<std::string>& record_struct) {
  Type type = Specifier(root->children[0], record_struct);
  if (root->children[1]->key == "ExtDecList") {
    std::list<std::string> record;
    ExtDecList(type, root->children[1], record);
  } else if (root->children[1]->key == "FunDec") {
    std::list<std::string> record;
    std::list<std::string> record_struct;
    FunDec(type, root->children[1], record, record_struct);
    Type ret;
    CompSt(root->children[2], record, ret, record_struct);
    if (!isEquivalent(type, ret)) {
      semanticError = true;
      std::cout << "[line " << root->children[1]->children[0]->lineNo
                << " semantic error] "
                << "The type of return value doesn't match with definition"
                << std::endl;
    }
  }
}
/**
 * @brief ExtDecList语义分析
 * 
 * @param type 属性文法传递的属性信息
 * @param root 子树根节点
 * @param record 作用域内定义的变量name
 */

void ExtDecList(Type type, tree root, std::list<std::string>& record) {
  VarDec(type, root->children[0], record);
  if (root->childCnt == 3) {
    ExtDecList(type, root->children[2], record);
  }
}

/**
 * @brief 获得Specifier表示的类型
 * 
 * @param root 子树根节点
 * @param record_struct 定义的struct的name集合
 * @return Type 
 */

Type Specifier(tree root, std::list<std::string>& record_struct) {
  Type type;
  if (root->children[0]->key == "TYPE") {
    if (root->children[0]->value == "int") {
      type = newBasic(INT_SEMA);
    } else {
      type = newBasic(FLOAT_SEMA);
    }
  } else {
    type = StructSpecifier(root->children[0], record_struct);
  }
  return type;
}
/**
 * @brief 获取struct定义的类型信息
 * 
 * @param root 子树根节点
 * @param record_struct 定义的struct的name集合
 * @return Type 
 */
Type StructSpecifier(tree root, std::list<std::string>& record_struct) {
  Type type;
  if (root->childCnt == 5) {
    std::string optag = OptTag(root->children[1]);
    std::list<std::string> names;
    std::unordered_map<std::string, Type> s_field;
    DefList(root->children[3], names, record_struct);
    for (auto name : names) {
      Type cur_type = getItem(name);
      s_field.insert({name, cur_type});
      deleteItem(name);
    }
    type = newStructure(s_field);
    if (optag != "") {
      if (!insertStructItem(optag, type)) {
        semanticError = true;
        std::cout << "[line " << root->children[2]->lineNo
                  << " semantic error] "
                  << "Multiple definition of struct " << optag << std::endl;
      } else {
        record_struct.push_back(optag);
      }
    }
    return type;
  } else if (root->children[1]->key == "Tag") {
    std::string tag = Tag(root->children[1]);
    type = getStructItem(tag);
    if (type == nullptr) {
      semanticError = true;
      std::cout << "[line " << root->children[1]->children[0]->lineNo
                << " semantic error] "
                << "Undefined reference to the struct " << tag << std::endl;
    }
  }
  return type;
}
/**
 * @brief 获得struct的OptTag struct T{int a;}; 其中T即为OptTag
 * 
 * @param root 
 * @return std::string 
 */
std::string OptTag(tree root) {
  if (root == nullptr) {
    return "";
  } else {
    return root->children[0]->value;
  }
}
/**
 * @brief 获取struct的tag名称 如 struct T t; 其中T则为tag
 * 
 * @param root 
 * @return std::string 
 */
std::string Tag(tree root) { return root->children[0]->value; }

/**
 * @brief 对VarDec文法进行语义分析
 * 
 * @param type 属性文法传递的属性信息
 * @param root 子树根节点
 * @param record 作用域内定义的变量name
 * @return int 
 */
int VarDec(Type type, tree root, std::list<std::string>& record) {
  if (root->children[0]->key == "ID") {
    //检查当前域内是否已经对该变量有过定义
    auto iter =
        std::find(record.begin(), record.end(), root->children[0]->value);
    if (iter != record.end()) {
      semanticError = true;
      std::cout << "[line " << root->children[0]->lineNo << " semantic error] "
                << "Multiple definition of variable "
                << root->children[0]->value << std::endl;
    } else {
      insertItem(root->children[0]->value, type);
      //记录当前域内已定义变量的名字
      record.push_back(root->children[0]->value);
      return root->children[0]->lineNo;
    }
  } else {  //数组定义
    int elemSize = atoi(root->children[2]->value.c_str());
    Type innerType = newArray(type, elemSize);
    //递归直至遇到变量名
    return VarDec(innerType, root->children[0], record);
  }
}
/**
 * @brief 对FunDec进行语义分析
 * 
 * @param rv_type 返回值类型
 * @param root 子树节点
 * @param record 作用域内定义的变量的name集合
 * @param record_struct 作用域内定义的struct的name集合
 */
void FunDec(Type rv_type, tree root, std::list<std::string>& record,
            std::list<std::string>& record_struct) {
  std::string func_name = root->children[0]->value;
  std::vector<Type> paramList;
  if (root->children[2]->key == "VarList") {
    VarList(paramList, root->children[2], record, record_struct);
  }
  Type type = newFunc(rv_type, paramList);
  if (!insertFuncItem(func_name, type)) {
    semanticError = true;
    std::cout << "[line " << root->children[0]->lineNo << " semantic error] "
              << "Multiple definition of function " << func_name << std::endl;
  }
}
/**
 * @brief VarList的语义分析
 * 
 * @param paramList 参数列表（函数定义时使用）
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 * @param record_struct 作用域内定义的struct的name集合
 */
void VarList(std::vector<Type>& paramList, tree root,
             std::list<std::string>& record,
             std::list<std::string>& record_struct) {
  ParamDec(paramList, root->children[0], record, record_struct);

  if (root->childCnt == 3) {
    VarList(paramList, root->children[2], record, record_struct);
  }
}
/**
 * @brief ParamDec的语义分析
 * 
 * @param paramList 参数列表（函数定义时使用）
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 * @param record_struct 作用域内定义的struct的name集合
 */
void ParamDec(std::vector<Type>& paramList, tree root,
              std::list<std::string>& record,
              std::list<std::string>& record_struct) {
  Type type = Specifier(root->children[0], record_struct);
  VarDec(type, root->children[1], record);  //参数列表中的参数会出现在符号表中
  paramList.push_back(type);
}

/**
 * @brief ComSt进行语义分析
 * 
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 * @param ret 返回值类型
 * @param record_struct 作用域内定义的struct的name集合
 */
void CompSt(tree root, std::list<std::string>& record, Type& ret,
            std::list<std::string>& record_struct) {
  DefList(root->children[1], record, record_struct);
  StmtList(root->children[2], ret);
  //出花括号时，将域内定义过的变量进行删除item操作
  while (!record.empty()) {
    deleteItem(record.back());
    record.pop_back();
  }

  while (!record.empty()) {
    deleteStructItem(record_struct.back());
    record_struct.pop_back();
  }
}

/**
 * @brief StmtList语义分析
 * 
 * @param root 子树根节点
 * @param ret 返回值类型
 */
void StmtList(tree root, Type& ret) {
  if (root == nullptr) {
    return;
  }
  Stmt(root->children[0], ret);
  StmtList(root->children[1], ret);
}
/**
 * @brief Stmt语义分析
 * 
 * @param root 子树根节点
 * @param ret 返回值类型
 */
void Stmt(tree root, Type& ret) {
  if (root->children[0]->key == "Exp") {
    Exp(root->children[0]);
  } else if (root->children[0]->key == "CompSt") {
    std::list<std::string> record;
    std::list<std::string> record_struct;
    Type unUsed;
    CompSt(root->children[0], record, unUsed, record_struct);
  } else if (root->children[0]->key == "RETURN") {
    ret = Exp(root->children[1]).first;
  } else if (root->children[0]->key == "WHILE") {  // WHILE LP EXP RP Stmt
    Exp(root->children[2]);
    Stmt(root->children[4], ret);
  } else {
    Exp(root->children[2]);
    Stmt(root->children[4], ret);
    if (root->childCnt == 7) {  // IF LP Exp RP Stmt ELSE Stmt
      Stmt(root->children[6], ret);
    }
  }
}
/**
 * @brief DefList语义分析
 * 
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 * @param record_struct 作用域内定义的struct的name集合
 */
void DefList(tree root, std::list<std::string>& record,
             std::list<std::string>& record_struct) {
  if (root == nullptr) {
    return;
  }
  Def(root->children[0], record, record_struct);
  DefList(root->children[1], record, record_struct);
}
/**
 * @brief Def语义分析
 * 
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 * @param record_struct 作用域内定义的struct的name集合
 */
void Def(tree root, std::list<std::string>& record,
         std::list<std::string>& record_struct) {
  Type type = Specifier(root->children[0], record_struct);
  DecList(type, root->children[1], record);
}
/**
 * @brief DecList语义分析
 * 
 * @param type 属性文法传递的类型信息
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 */
void DecList(Type type, tree root, std::list<std::string>& record) {
  Dec(type, root->children[0], record);
  if (root->childCnt == 3) {
    DecList(type, root->children[2], record);
  }
}
/**
 * @brief Dec语义分析
 * 
 * @param type 属性文法传递的类型信息
 * @param root 子树根节点
 * @param record 作用域内定义的变量的name集合
 */
void Dec(Type type, tree root, std::list<std::string>& record) {
  int line = VarDec(type, root->children[0], record);
  if (root->childCnt == 3) {
    //存在ASSIGNOP,
    // VarDec其后必为左值，因此此处的ASSIGNOP无需判断是否为左值
    Type right = Exp(root->children[2]).first;
    if (!isEquivalent(type, right)) {
      semanticError = true;
      std::cout << "[line " << line << " semantic error] "
                << "This kind of value can't be assigned to " << record.back()
                << std::endl;
    }
  }
}
/**
 * @brief Exp进行语义分析
 * 
 * @param root 子树根节点
 * @return std::pair<Type, bool> Type为Exp对应的类型，bool表示是否为左值
 */
std::pair<Type, bool> Exp(tree root) {
  if (root->childCnt == 1) {  // Exp->ID INT FLOAT
    if (root->children[0]->key == "ID") {
      Type type = getItem(root->children[0]->value);
      if (type == nullptr) {
        semanticError = true;
        std::cout << "[line " << root->children[0]->lineNo
                  << " semantic error] "
                  << "Undefined reference to variable "
                  << root->children[0]->value << std::endl;
        return {nullptr, false};
      }
      return {type, true};
    } else if (root->children[0]->key == "INT") {
      return {newBasic(INT_SEMA), false};
    } else {
      return {newBasic(FLOAT_SEMA), false};
    }
  } else if (root->childCnt == 3) {  //
    if (root->children[0]->key == "Exp") {
      if (root->children[1]->key == "ASSIGNOP") {  // Exp ASSIGNOP Exp
        std::pair<Type, bool> exp1 = Exp(root->children[0]);
        std::pair<Type, bool> exp2 = Exp(root->children[2]);

        if (exp1.first && exp2.first) {
          if (!exp1.second) {
            semanticError = true;
            std::cout << "[line " << root->children[1]->lineNo
                      << " semantic error] "
                      << "Can't assign value to a non-left value. "
                      << std::endl;
          }
          if (!isEquivalent(exp1.first, exp2.first)) {
            semanticError = true;
            std::cout << "[line " << root->children[1]->lineNo
                      << " semantic error] "
                      << "Type doesn't match" << std::endl;
          }
        }

        return {exp2.first ? exp2.first : exp1.first, false};

      } else if (root->children[1]->key == "DOT") {  // Exp DOT ID
        std::pair<Type, bool> typeExp = Exp(root->children[0]);
        if (typeExp.first == nullptr) {
          return {nullptr, false};
        }
        if (typeExp.first->kind != STRUCTURE_SEMA) {
          semanticError = true;
          std::cout << "[line " << root->children[1]->lineNo
                    << " semantic error] "
                    << "Can't access use ." << std::endl;
          return {nullptr, false};
        }
        std::string id = root->children[2]->value;
        Type typeID = getFieldType(typeExp.first->u.structure, id);
        if (typeID == nullptr) {
          semanticError = true;
          std::cout << "[line " << root->children[1]->lineNo
                    << " semantic error] "
                    << "The structure doesn't has the member "
                    << root->children[2]->value << std::endl;
          return {nullptr, false};
        }
        return {typeID, true};

      } else {  // Exp MUL Exp | Exp ADD Exp ......
        std::pair<Type, bool> exp1 = Exp(root->children[0]);
        std::pair<Type, bool> exp2 = Exp(root->children[2]);
        if (!isEquivalent(exp1.first, exp2.first)) {
          semanticError = true;
          std::cout << "[line " << root->children[1]->lineNo
                    << " semantic error] "
                    << "Type doesn't match" << std::endl;
          return {nullptr, false};
        }
        return {exp1.first, false};
      }

    } else if (root->children[0]->key == "LP") {  // LP Exp RP
      return Exp(root->children[1]);
    } else {  // ID LP RP
      std::string id = root->children[0]->value;
      Type type = getFuncItem(id);
      if (type == nullptr) {
        semanticError = true;
        std::cout << "[line " << root->children[0]->lineNo
                  << " semantic error] "
                  << "Undefined reference to function " << id << std::endl;
        return {nullptr, false};
      }
      if (type->u.func.paraNum != 0) {
        semanticError = true;
        std::cout << "[line " << root->children[0]->lineNo
                  << " semantic error] "
                  << "There are too many params" << std::endl;
      }
      return {type->u.func.rv, false};
    }
  } else if (root->childCnt == 2) {  // MINUS Exp /  NOT Exp
    std::pair<Type, bool> exp = Exp(root->children[1]);
    if (exp.first) {
      switch (exp.first->kind) {
        case INT_SEMA:
        FLOAT_SEMA : {
          if (root->children[0]->key == "MINUS") {
            return {exp.first, false};
          } else {
            return {newBasic(INT_SEMA), false};
          }
          break;
        }
        case ARRAY_SEMA: {
          if (root->children[0]->key == "NOT") {
            return {newBasic(INT_SEMA), false};
          }
          break;
        }
        case FUNC_SEMA: {
          Type rv_type = exp.first->u.func.rv;
          if (root->children[0]->key == "MINUS") {
            if (rv_type->kind != STRUCTURE_SEMA) {
              return {rv_type, false};
            }
          } else {
            if (rv_type->kind != STRUCTURE_SEMA) {
              return {newBasic(INT_SEMA), false};
            }
          }
          break;
        }
        case STRUCTURE_SEMA: {
          break;
        }
      }
    }
    semanticError = true;
    std::cout << "[line " << root->children[0]->lineNo << " semantic error] "
              << "Illegal usage of ! and -" << std::endl;
    return {nullptr, false};
  } else if (root->childCnt == 4) {
    if (root->children[0]->key == "ID") {  // ID LP Args RP
      std::string func_name = root->children[0]->value;
      Type func_type = getFuncItem(func_name);
      if (func_type == nullptr) {
        semanticError = true;
        std::cout << "[line " << root->children[0]->lineNo
                  << " semantic error] "
                  << "Undefined reference to function " << func_name
                  << std::endl;
        return {nullptr, false};
      }

      if (func_type->u.func.paraNum == 0) {
        semanticError = true;
        std::cout << "[line " << root->children[0]->lineNo
                  << " semantic error] "
                  << "The paramlist of function doesn't match" << std::endl;
        return {nullptr, false};
      }
      if (Args(root->children[2], func_type, 0)) {
        return {func_type->u.func.rv, false};
      }
      semanticError = true;
      std::cout << "[line " << root->children[0]->lineNo << " semantic error] "
                << "The paramlist of function doesn't match" << std::endl;
      return {nullptr, false};
    } else {  // Exp LB Exp RB
      int array_depth = 0;
      Type array_type = getArrayType(root, array_depth);
      std::pair<Type, bool> exp = Exp(root->children[2]);

      if (array_type == nullptr || array_type->kind != ARRAY_SEMA) {
        semanticError = true;
        std::cout << "[line " << root->children[1]->lineNo
                  << " semantic error] "
                  << "Can't access using index except array" << std::endl;
        return {nullptr, false};
      }

      if (exp.first->kind != INT_SEMA) {
        semanticError = true;
        std::cout << "[line " << root->children[1]->lineNo
                  << " semantic error] "
                  << "Can't access using non-integer index" << std::endl;
        return {nullptr, false};
      }
      Type res = getArrayElemType(array_type, array_depth);
      if (res == nullptr) {
        semanticError = true;
        std::cout << "[line " << root->children[1]->lineNo
                  << " semantic error] "
                  << "The access to array is out of range" << std::endl;
        return {nullptr, false};
      } else {
        return {res, true};
      }
    }
  }
}
/**
 * @brief 对Args进行语义分析
 * 
 * @param root 子树根节点
 * @param func_type 函数返回值类型
 * @param paramNo 参数个数
 * @return true 
 * @return false 
 */
bool Args(tree root, Type func_type, int paramNo) {
  if (root == nullptr && paramNo == func_type->u.func.paraNum) {
    return true;
  }
  if (root == nullptr) {
    return false;
  }
  std::pair<Type, bool> exp = Exp(root->children[0]);
  if (!isEquivalent(exp.first, func_type->u.func.paramList[paramNo])) {
    return false;
  } else {
    return Args(root->children[2], func_type, paramNo + 1);
  }
}
