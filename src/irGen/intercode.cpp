#include "../include/intercode.hpp"

#include <stdio.h>

#include <iostream>

#include "../include/global.hpp"
InterCodeList head = newICList();
std::unordered_map<std::string, std::string> structMap;

/**
 * @brief 产生中间代码主入口
 *
 * @param root 当前要输出的树根节点
 */
void translate_Program(tree root) {
  if (root == NULL) {
    return;
  }
  // Program → ExtDefList
  if (root->children[0]->key == "ExtDefList") {
    translate_ExtDefList(root->children[0]);
  }
}

/**
 * @brief 当前节点为ExtDefList的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为ExtDefList)
 */
void translate_ExtDefList(tree node) {
  if (node == NULL) {
    return;
  }
  // ExtDefList -> ExtDef ExtDefList
  //             | e
  while (node) {
    translate_ExtDef(node->children[0]);
    node = node->children[1];
  }
}
/**
 * @brief 当前节点为ExtDef的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为ExtDef)
 */
void translate_ExtDef(tree node) {
  if (node == NULL) {
    return;
  }
  // ExtDef → Specifier ExtDecList SEMI
  //          | Specifier SEMI
  //          | Specifier FunDec CompSt
  if (node->children[1]->key == "FunDec") {
    std::vector<std::string> valueRecord;
    translate_FunDec(node->children[1], valueRecord);
    translate_CompSt(node->children[2], valueRecord);
  } else if (node->children[1]->key == "ExtDecList") {
    std::vector<std::string> valueRecord;
    translate_ExtDecList(node->children[1], valueRecord);
  }
}
/**
 * @brief 当前节点为ExtDecList的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为ExtDecList)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_ExtDecList(tree node, std::vector<std::string>& valueRecord) {
  if (node == nullptr) {
    return;
  }
  // ExtDecList -> VarDec
  //            -> VarDec COMMA ExtDecList
  Operand place = newvalue();
  translate_VarDec(node->children[0], place, valueRecord);
  if (node->childCnt == 3) {
    translate_ExtDecList(node->children[2], valueRecord);
  }
}
/**
 * @brief 当前节点为FunDec的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为FunDec)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_FunDec(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // to do
  // FunDec -> ID LP VarList RP
  //         | ID LP RP
  InterCode x =
      newOneop(IC_FUNCTION, newOperand(OP_FUNCTION, node->children[0]->value));
  add_ICList(head, x);
  if (node->childCnt == 4) {
    translate_VarList(node->children[2], valueRecord);
  }
}
/**
 * @brief 当前节点为VarList的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为VarList)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_VarList(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // VarList → ParamDec COMMA VarList
  //          | ParamDec
  translate_ParamDec(node->children[0], valueRecord);
  if (node->childCnt == 3) {
    translate_VarList(node->children[2], valueRecord);
  }
}
/**
 * @brief 当前节点为ParamDec的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为ParamDec)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_ParamDec(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // ParamDec → Specifier VarDec
  // VarDec → ID
  //          | VarDec LB INT RB
  tree temp = node->children[1];
  //直到找到ID
  while (temp->childCnt != 1) {
    temp = temp->children[0];
  }
  Operand param = newvalue();
  if (node->children[0]->children[0]->value == "string") {
    param->kind = OP_V_STRING;
  }
  insertValueItem(temp->children[0]->value, param);
  valueRecord.push_back(temp->children[0]->value);
  InterCode x = newOneop(IC_PARAM, param);
  add_ICList(head, x);
}
/**
 * @brief 当前节点为CompSt的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为CompSt)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_CompSt(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // CompSt → LC DefList StmtList RC
  translate_DefList(node->children[1], valueRecord);
  translate_StmtList(node->children[2]);
  while (!valueRecord.empty()) {
    deleteValueItem(valueRecord.back());
    valueRecord.pop_back();
  }
}
/**
 * @brief 当前节点为DefList的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为DefList)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_DefList(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // DefList → Def DefList
  //           |e
  while (node) {
    translate_Def(node->children[0], valueRecord);
    node = node->children[1];
  }
}
/**
 * @brief 当前节点为Def的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为Def)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_Def(tree node, std::vector<std::string>& valueRecord)
{
    if (node == NULL)
        return;
    // Def → Specifier DecList SEMI
    if (node->children[0]->children[0]->key == "StructSpecifier" && node->children[0]->children[0]->childCnt == 2)
    {
        std::string Tag = node->children[0]->children[0]->children[1]->children[0]->value;
        Type type = getStructItem(Tag);
        int size = compute_size(type);
        tree temp = node->children[1];
        while (temp)
        {
            Operand v = newvalue();
            std::cout << temp->children[0]->value << std::endl;
            std::string valueName = temp->children[0]->children[0]->children[0]->value;
            insertValueItem(valueName, v);
            structMap.insert({valueName, Tag});
            valueRecord.push_back(valueName);
            add_ICList(head, newDec(IC_DEC, v, size));
            if (temp->childCnt == 3){
                temp = temp->children[2];
            } else {
                break;
            }
        }
    }
    else{
        translate_DecList(node->children[1], valueRecord);
    }

}
/**
 * @brief 计算item的大小便于DEC
 *
 * @param item 需要被计算的type
 */
int compute_size(Type item)
{
    if (item == NULL)
        return 0;
    switch (item->kind)
    {
        case INT_SEMA:
        case FLOAT_SEMA:
            return 8;
        case ARRAY_SEMA:
            return item->u.array.elemSize * compute_size(item->u.array.elemType);
        case STRUCTURE_SEMA:
        {
            int size = 0;
            FieldList temp = item->u.structure;
            while (temp)
            {
                size += compute_size(temp->type);
                temp = temp->tail;
            }
            return size;
        }
    }
}
/**
 * @brief 当前节点为DecList的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为DecList)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_DecList(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // DecList → Dec
  //          | Dec COMMA DecList
  while (node) {
    translate_Dec(node->children[0], valueRecord);
    if (node->childCnt == 3) {
      node = node->children[2];
    } else {
      break;
    }
  }
}
/**
 * @brief 当前节点为Dec的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为Dec)
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_Dec(tree node, std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // Dec → VarDec
  //      | VarDec ASSIGNOP Exp

  if (node->childCnt == 1) {
    Operand v1 = newvalue();
    translate_VarDec(node->children[0], v1, valueRecord);
  }
  // Dec -> VarDec ASSIGNOP Exp
  else {
    tree temp = node;
    while (temp->childCnt != 1) {
      temp = temp->children[0];
    }
    Operand v1 = newvalue();
    translate_VarDec(node->children[0], v1, valueRecord);
    Operand t2;
    if (node->children[2]->children[0]->key == "STRING") {
      v1->kind = OP_V_STRING;
      t2 = newOperand(OP_STRING, node->children[2]->children[0]->value);
    } else {
      t2 = newtemp();
      translate_Exp(node->children[2], t2);
    }
    InterCode x = newAssign(IC_ASSIGN, t2, v1);
    add_ICList(head, x);
  }
}
/**
 * @brief 当前节点为VarDec的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为VarDec)
 * @param place 储存以当前节点为根的子树返回值
 * @param valueRecord 储存当前作用域的变量，便于离开作用域时销毁
 */
void translate_VarDec(tree node, Operand place,
                      std::vector<std::string>& valueRecord) {
  if (node == NULL) {
    return;
  }
  // VarDec → ID
  //          | VarDec LB INT RB
  if (node->childCnt == 4) {
    std::string info = node->children[2]->value;
    int size = 1;
    while (node->childCnt == 4) {
      size = size * std::stoi(node->children[2]->value);
      node = node->children[0];
    }
    size = size * 8;
    InterCode x = newDec(IC_DEC, place, size);
    add_ICList(head, x);
    insertDimensionItem(node->children[0]->value, info);
  }

  insertValueItem(node->children[0]->value, place);
  valueRecord.push_back(node->children[0]->value);
}
/**
 * @brief 当前节点为Exp的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为Exp)
 * @param place 储存以当前节点为根的子树返回值
 */
void translate_Exp(tree node, Operand place) {
  if (node == NULL) {
    return;
  }
  if (node->childCnt == 4) {
    // Exp → ID LP Args RP
    if (node->children[0]->key == "ID") {
      Arglist list = newArglist();
      translate_Args(node->children[2], list);
      Arg p = list->head;
      while (p != nullptr) {
        InterCode x = newOneop(IC_ARG, p->op);
        add_ICList(head, x);
        p = p->next;
      }
      Operand id = newOperand(OP_CALL, node->children[0]->value);
      InterCode x;
      if (place) {
        x = newAssign(IC_ASSIGN, id, place);
      } else {
        x = newOneop(IC_CALL, id);
      }
      add_ICList(head, x);
      return;
    }
    // | Exp LB Exp RB
    else {
      Operand t1 = newtemp();
      Operand t2 = newtemp();
      translate_Exp(node->children[2], t1);
      Operand tmp = newtemp();
      tree tmp_node = node;
      while (tmp_node->childCnt != 1) tmp_node = tmp_node->children[0];
      Operand v = getValueItem(tmp_node->children[0]->value);
      if (v->kind == OP_V_STRING) {
        add_ICList(head,
                   newAssign(IC_ASSIGN, newOperand(OP_CONSTANT, "1"), tmp));
      } else {
        add_ICList(head,
                   newAssign(IC_ASSIGN, newOperand(OP_CONSTANT, "8"), tmp));
      }
      add_ICList(head, newBinop(IC_MUL, t2, t1, tmp));

      Operand t3 = newtemp();
      if (node->children[0]->childCnt == 1) {
        translate_Exp(node->children[0], t3);
      } else {
        Operand t4 = newtemp();
        translate_Exp(node->children[0]->children[2], t4);
        add_ICList(head, newBinop(IC_MUL, t4, t4, tmp));
        std::string arry_size = getDimensionItem(
            node->children[0]->children[0]->children[0]->value);
        Operand tmp2 = newtemp();
        add_ICList(head, newAssign(IC_ASSIGN,
                                   newOperand(OP_CONSTANT, arry_size), tmp2));
        add_ICList(head, newBinop(IC_MUL, t4, t4, tmp2));
        add_ICList(head, newBinop(IC_ADD, t2, t4, t2));
        translate_Exp(node->children[0]->children[0], t3);
      }
      if (place->loc == 0) {
        Operand new_place = newOperand(OP_VARIABLE, place->name);
        add_ICList(head, newBinop(IC_ADD, new_place, t3, t2));
        if (v->kind == OP_V_STRING) {
          place->kind = OP_WRITE_ADDRESS_BYTE;
        } else {
          place->kind = OP_WRITE_ADDRESS;
        }
      } else {
        Operand new_place = newOperand(OP_WRITE_ADDRESS, place->name);
        if (v->kind == OP_V_STRING) {
          new_place->kind = OP_WRITE_ADDRESS_BYTE;
        }
        add_ICList(head, newBinop(IC_ADD, place, t3, t2));
        add_ICList(head, newAssign(IC_ASSIGN, new_place, place));
      }
    }
  } else if (node->childCnt == 3) {
    // | Exp DOT ID
    if (node->children[1]->key == "DOT") {
      tree tmp_node = node;
      while (tmp_node->childCnt != 1) tmp_node = tmp_node->children[0];
      std::string valueName = tmp_node->children[0]->value;
      Operand val = getValueItem(valueName);
      auto target = structMap.find(valueName);
      Type v = getStructItem(target->second);
      std::string name = node->children[2]->value;
      int offset = 0;
      FieldList structure = v->u.structure;
      while (structure->name != name) {
        structure = structure->tail;
        offset++;
      }
      Operand size = newtemp();
      add_ICList(head, newAssign(IC_ASSIGN, newOperand(OP_CONSTANT, "8"), size));
      Operand off = newtemp();
      add_ICList(head, newAssign(IC_ASSIGN, newOperand(OP_CONSTANT, std::to_string(offset)), off));
      add_ICList(head, newBinop(IC_MUL, off, off, size));
      Operand baseAddress = newtemp();
      add_ICList(head, newAssign(IC_ASSIGN, val, baseAddress));
      if (place->loc == 0) {
        Operand new_place = newOperand(OP_VARIABLE, place->name);
        add_ICList(head, newBinop(IC_ADD, new_place, baseAddress, off));
        place->kind = OP_WRITE_ADDRESS;
      } else {
        Operand new_place = newOperand(OP_WRITE_ADDRESS, place->name);
        add_ICList(head, newBinop(IC_ADD, place, baseAddress, off));
        add_ICList(head, newAssign(IC_ASSIGN, new_place, place));
      }
    }
    // | ID LP RP
    if (node->children[0]->key == "ID") {
      Operand id = newOperand(OP_CALL, node->children[0]->value);
      InterCode x;
      if (place) {
        x = newAssign(IC_ASSIGN, id, place);
        add_ICList(head, x);
      } else {
        x = newOneop(IC_CALL, id);
        add_ICList(head, x);
      }
    }
    // | LP Exp RP
    if (node->children[0]->key == "LP") {
      translate_Exp(node->children[1], place);
    }
    // | Exp ASSIGNOP Exp
    if (node->children[1]->key == "ASSIGNOP") {
      Operand t1;
      if (node->children[2]->children[0]->key == "STRING") {
        t1 = newOperand(OP_STRING, node->children[2]->children[0]->value);
      } else {
        t1 = newtemp();
        translate_Exp(node->children[2], t1);
      }
      if (node->children[0]->children[0]->key == "ID") {
        Operand v = getValueItem(node->children[0]->children[0]->value);
        if (t1->kind == OP_STRING) {
          v->kind = OP_V_STRING;
        }
        add_ICList(head, newAssign(IC_ASSIGN, t1, v));

        if (place) {
          add_ICList(head, newAssign(IC_ASSIGN, v, place));
        }
      } else {
        Operand t2 = newtemp();
        t2->loc = 0;
        translate_Exp(node->children[0], t2);
        add_ICList(head, newAssign(IC_ASSIGN, t1, t2));
        if (place) {
          add_ICList(head, newAssign(IC_ASSIGN, t2, place));
        }
      }
    }
    // | Exp AND Exp
    // | Exp OR Exp
    // | Exp RELOP Exp
    if (node->children[1]->key == "AND" || node->children[1]->key == "OR" ||
        node->children[1]->key == "RELOP") {
      Operand label1 = newlabel();
      Operand label2 = newlabel();
      Operand constant = newOperand(OP_CONSTANT, "0");
      InterCode insert = newAssign(IC_ASSIGN, constant, place);
      add_ICList(head, insert);

      translate_Cond(node, label1, label2);

      InterCode p = newOneop(IC_LABEL, label1);
      add_ICList(head, p);

      Operand one = newOperand(OP_CONSTANT, "1");
      InterCode q = newAssign(IC_ASSIGN, one, place);
      add_ICList(head, q);

      InterCode two = newOneop(IC_LABEL, label2);
      add_ICList(head, two);
    }
    // | Exp PLUS Exp
    if (node->children[1]->key == "PLUS") {
      Operand t1 = newtemp();
      Operand t2 = newtemp();
      translate_Exp(node->children[0], t1);
      translate_Exp(node->children[2], t2);
      InterCode insert = newBinop(IC_ADD, place, t1, t2);
      add_ICList(head, insert);
    }
    // | Exp MINUS Exp
    if (node->children[1]->key == "MINUS") {
      Operand t1 = newtemp();
      Operand t2 = newtemp();
      translate_Exp(node->children[0], t1);
      translate_Exp(node->children[2], t2);
      InterCode insert = newBinop(IC_SUB, place, t1, t2);
      add_ICList(head, insert);
    }
    // | Exp STAR Exp
    if (node->children[1]->key == "STAR") {
      Operand t1 = newtemp();
      Operand t2 = newtemp();
      translate_Exp(node->children[0], t1);
      translate_Exp(node->children[2], t2);
      InterCode insert = newBinop(IC_MUL, place, t1, t2);
      add_ICList(head, insert);
    }
    // | Exp DIV Exp
    if (node->children[1]->key == "DIV") {
      Operand t1 = newtemp();
      Operand t2 = newtemp();
      translate_Exp(node->children[0], t1);
      translate_Exp(node->children[2], t2);
      InterCode insert = newBinop(IC_DIV, place, t1, t2);
      add_ICList(head, insert);
    }
  } else if (node->childCnt == 2) {
    // | MINUS Exp
    if (node->children[0]->key == "MINUS") {
      Operand t1 = newtemp();
      translate_Exp(node->children[1], t1);
      Operand t2 = newtemp();
      Operand zero = newOperand(OP_CONSTANT, "0");
      InterCode x = newAssign(IC_ASSIGN, zero, t2);
      add_ICList(head, x);
      // Operand zero = newOperand(OP_CONSTANT, "0");
      x = newBinop(IC_SUB, place, t2, t1);
      add_ICList(head, x);
    }
    // | NOT Exp
    if (node->children[0]->key == "NOT") {
      Operand label1 = newlabel();
      Operand label2 = newlabel();
      Operand constant = newOperand(OP_CONSTANT, "0");
      InterCode insert = newAssign(IC_ASSIGN, constant, place);
      add_ICList(head, insert);

      translate_Cond(node, label1, label2);

      InterCode p = newOneop(IC_LABEL, label1);
      add_ICList(head, p);

      Operand one = newOperand(OP_CONSTANT, "1");
      InterCode q = newAssign(IC_ASSIGN, one, place);
      add_ICList(head, q);

      InterCode two = newOneop(IC_LABEL, label2);
      add_ICList(head, two);
    }
  } else {
    // | ID
    if (node->children[0]->key == "ID") {
      std::string value = node->children[0]->value;
      Operand val = getValueItem(value);
      InterCode x = newAssign(IC_ASSIGN, val, place);
      add_ICList(head, x);
    } else if (node->children[0]->key == "STRING") {
      std::string value = node->children[0]->value;
      Operand val = newOperand(OP_STRING, value);
      InterCode x = newAssign(IC_ASSIGN, val, place);
      add_ICList(head, x);
    }
    // | INT
    else if (node->children[0]->key == "INT") {
      std::string value = node->children[0]->value;
      Operand val = newOperand(OP_CONSTANT, value);
      InterCode x = newAssign(IC_ASSIGN, val, place);
      add_ICList(head, x);
    }
    // | FLOAT
    else {
      std::string value = node->children[0]->value;
      Operand val = newOperand(OP_CONSTANT, value);
      InterCode x = newAssign(IC_ASSIGN, val, place);
      add_ICList(head, x);
    }
  }
}
/**
 * @brief 当前节点为StmtList的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为StmtList)
 */
void translate_StmtList(tree node) {
  if (node == NULL) {
    return;
  }
  // StmtList -> Stmt StmtList
  //           | e
  while (node) {
    translate_Stmt(node->children[0]);
    node = node->children[1];
  }
}
/**
 * @brief 当前节点为Stmt的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为Stmt)
 */
void translate_Stmt(tree node) {
  if (node == NULL) {
    return;
  }
  // Stmt -> Exp SEMI
  if (node->children[0]->key == "Exp") {
    translate_Exp(node->children[0], nullptr);
  }
  //       | CompSt
  if (node->children[0]->key == "CompSt") {
    std::vector<std::string> valueRecord;
    translate_CompSt(node->children[0], valueRecord);
  }
  //       | RETURN Exp SEMI
  if (node->children[0]->key == "RETURN") {
    Operand t1 = newtemp();
    translate_Exp(node->children[1], t1);
    InterCode x = newOneop(IC_RETURN, t1);
    add_ICList(head, x);
  }
  if (node->children[0]->key == "IF") {
    //   | IF LP Exp RP Stmt ELSE Stmt
    if (node->childCnt > 5) {
      Operand label1 = newlabel();
      Operand label2 = newlabel();
      Operand label3 = newlabel();
      translate_Cond(node->children[2], label1, label2);
      InterCode x = newOneop(IC_LABEL, label1);
      add_ICList(head, x);
      translate_Stmt(node->children[4]);
      x = newOneop(IC_GOTO, label3);
      add_ICList(head, x);
      x = newOneop(IC_LABEL, label2);
      add_ICList(head, x);
      translate_Stmt(node->children[6]);
      x = newOneop(IC_LABEL, label3);
      add_ICList(head, x);
    }
    //   | IF LP Exp RP Stmt
    else {
      Operand label1 = newlabel();
      Operand label2 = newlabel();
      translate_Cond(node->children[2], label1, label2);
      InterCode x = newOneop(IC_LABEL, label1);
      add_ICList(head, x);
      translate_Stmt(node->children[4]);
      x = newOneop(IC_LABEL, label2);
      add_ICList(head, x);
    }
  }
  //       | WHILE LP Exp RP Stmt
  if (node->children[0]->key == "WHILE") {
    Operand label1 = newlabel();
    Operand label2 = newlabel();
    Operand label3 = newlabel();
    InterCode x = newOneop(IC_LABEL, label1);
    add_ICList(head, x);
    translate_Cond(node->children[2], label2, label3);
    x = newOneop(IC_LABEL, label2);
    add_ICList(head, x);
    translate_Stmt(node->children[4]);
    x = newOneop(IC_GOTO, label1);
    add_ICList(head, x);
    x = newOneop(IC_LABEL, label3);
    add_ICList(head, x);
  }
}
/**
 * @brief 当前节点为Cond的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为Cond)
 * @param label_true 条件为true时的跳转label
 * @param label_false 条件为false时的跳转label
 */
void translate_Cond(tree node, Operand label_true, Operand label_false) {
  if (node == NULL) {
    return;
  }
  // Exp -> Exp AND Exp
  //      | Exp OR Exp
  //      | Exp RELOP Exp
  //      | NOT Exp
  // to do

  // Exp -> Exp RELOP Exp
  if (node->children[1]->key == "RELOP") {
    Operand t1, t2;
    t1 = newtemp();
    translate_Exp(node->children[0], t1);
    t2 = newtemp();
    translate_Exp(node->children[2], t2);
    Operand relop = newOperand(OP_RELOP, node->children[1]->value);

    add_ICList(head, newIf_goto(IC_IF_GOTO, t1, relop, t2, label_true));
    add_ICList(head, newOneop(IC_GOTO, label_false));
  }
  // Exp -> NOT Exp
  else if (node->children[0]->key == "NOT") {
    translate_Cond(node->children[1], label_false, label_true);
  }
  // Exp -> Exp AND Exp
  else if (node->children[1]->key == "AND") {
    Operand label1 = newlabel();
    translate_Cond(node->children[0], label1, label_false);
    add_ICList(head, newOneop(IC_LABEL, label1));
    translate_Cond(node->children[2], label_true, label_false);
  }

  // Exp ->Exp OR Exp
  else if (node->children[1]->key == "OR") {
    Operand label1 = newlabel();
    translate_Cond(node->children[0], label_true, label1);
    add_ICList(head, newOneop(IC_LABEL, label1));
    translate_Cond(node->children[2], label_true, label_false);
  }

  //(other cases)
  else {
    Operand t1 = newtemp();
    translate_Exp(node, t1);
    add_ICList(head, newIf_goto(IC_IF_GOTO, t1, newOperand(OP_RELOP, "!="),
                                newOperand(OP_CONSTANT, "0"), label_true));
    add_ICList(head, newOneop(IC_GOTO, label_false));
  }
}

/**
 * @brief 当前节点为Args的中间代码翻译
 *
 * @param node 当前要输出的子树根节点(key为Args)
 * @param argList 需要返回的参数链表
 */
void translate_Args(tree node, Arglist argList) {
  if (node == NULL) {
    return;
  }
  // Args -> Exp COMMA Args
  //       | Exp

  // Args -> Exp
  Operand t1 = newtemp();
  translate_Exp(node->children[0], t1);
  Arg temp = newArg(t1);
  addArg(argList, temp);

  // Args -> Exp COMMA Args
  if (node->childCnt == 3) {
    translate_Args(node->children[2], argList);
  }
}

/**
 * @brief 初始化参数链表
 *
 * @return 参数链表
 */
Arglist newArglist() {
  Arglist head = new Arglist_();
  head->head = NULL;
  head->cur = NULL;
  return head;
}
/**
 * @brief 产生一个新参数
 *
 * @param op 参数对应的操作数
 */
Arg newArg(Operand op) {
  Arg temp = new Arg_();
  temp->op = op;
  temp->next = NULL;
  return temp;
}
/**
 * @brief 向参数链表新增参数
 *
 * @param argList 参数链表
 * @param arg 添加的参数
 */
void addArg(Arglist argList, Arg arg) {
  if (argList->head == NULL) {
    argList->head = arg;
    argList->cur = arg;
  } else {
    argList->head = arg;
    argList->head->next = argList->cur;
    argList->cur = arg;
  }
}
/**
 * @brief 初始化中间代码链表
 */
InterCodeList newICList() {
  InterCodeList p = new InterCodes();
  p->code = nullptr;  // head pointer's content is null
  p->prev = p->next = nullptr;
  return p;
}
/**
 * @brief 向中间代码链表新增中间代码
 *
 * @param p 中间代码链表
 * @param q 添加的中间代码
 */
void add_ICList(InterCodeList p, InterCode q) {
  InterCodeList temp = p->next;
  InterCodeList tail = p;
  while (temp != nullptr) {
    tail = temp;
    temp = temp->next;
  }
  temp = new InterCodes();
  tail->next = temp;
  temp->code = q;
  temp->prev = tail;
  temp->next = nullptr;
}

/**
 * @brief 产生一条Assign中间代码
 *
 * @param kind 中间代码类型
 * @param right assign右值
 * @param left assign左值
 *
 * @return 一条kind为IC_ASSIGN的中间代码
 */
InterCode newAssign(Kind_IC kind, Operand right, Operand left) {
  InterCode temp = new InterCode_();
  switch (kind) {
    case IC_ASSIGN: {
      temp->kind = IC_ASSIGN;
      temp->u.assign.right = right;
      temp->u.assign.left = left;
      break;
    }
    default: {
      break;
    }
  }
  return temp;
}
/**
 * @brief 产生一条二元运算中间代码
 *
 * @param kind 中间代码类型
 * @param result 结果
 * @param op1 第一个操作数
 * @param op2 第二个操作数
 *
 * @return 一条二元运算中间代码
 */
InterCode newBinop(Kind_IC kind, Operand res, Operand op1, Operand op2) {
  InterCode temp = new InterCode_();
  switch (kind) {
    case IC_ADD: {
      temp->kind = IC_ADD;
      temp->u.binop.result = res;
      temp->u.binop.op1 = op1;
      temp->u.binop.op2 = op2;
      break;
    }
    case IC_SUB: {
      temp->kind = IC_SUB;
      temp->u.binop.result = res;
      temp->u.binop.op1 = op1;
      temp->u.binop.op2 = op2;
      break;
    }
    case IC_MUL: {
      temp->kind = IC_MUL;
      temp->u.binop.result = res;
      temp->u.binop.op1 = op1;
      temp->u.binop.op2 = op2;
      break;
    }
    case IC_DIV: {
      temp->kind = IC_DIV;
      temp->u.binop.result = res;
      temp->u.binop.op1 = op1;
      temp->u.binop.op2 = op2;
      break;
    }
    default: {
      break;
    }
  }
  return temp;
}
/**
 * @brief 产生一条单操作数中间代码
 *
 * @param kind 中间代码类型
 * @param op 操作数
 *
 * @return 一条单操作数中间代码
 */
InterCode newOneop(Kind_IC kind, Operand op) {
  InterCode temp = new InterCode_();
  switch (kind) {
    case IC_LABEL: {
      temp->kind = IC_LABEL;
      temp->u.oneop.op = op;
      break;
    }
    case IC_FUNCTION: {
      temp->kind = IC_FUNCTION;
      temp->u.oneop.op = op;
      break;
    }
    case IC_PARAM: {
      temp->kind = IC_PARAM;
      temp->u.oneop.op = op;
      break;
    }
    case IC_RETURN: {
      temp->kind = IC_RETURN;
      temp->u.oneop.op = op;
      break;
    }
    case IC_GOTO: {
      temp->kind = IC_GOTO;
      temp->u.oneop.op = op;
      break;
    }
    case IC_ARG: {
      temp->kind = IC_ARG;
      temp->u.oneop.op = op;
      break;
    }
    case IC_CALL: {
      temp->kind = IC_CALL;
      temp->u.oneop.op = op;
      break;
    }
    default: {
      break;
    }
  }
  return temp;
}
/**
 * @brief 产生一条if_goto中间代码
 *
 * @param kind 中间代码类型
 * @param x 比较符左值
 * @param relop 比较符
 * @param y 比较符右值
 * @param t 条件为真跳转label
 *
 * @return 一条if_goto中间代码
 */
InterCode newIf_goto(Kind_IC kind, Operand x, Operand relop, Operand y,
                     Operand t) {
  InterCode temp = new InterCode_();
  switch (kind) {
    case IC_IF_GOTO: {
      temp->kind = IC_IF_GOTO;
      temp->u.if_goto.x = x;
      temp->u.if_goto.relop = relop;
      temp->u.if_goto.y = y;
      temp->u.if_goto.t = t;
      break;
    }
    default: {
      break;
    }
  }
  return temp;
}
/**
 * @brief 产生一条DEC中间代码
 *
 * @param kind 中间代码类型
 * @param x DEC的操作数
 * @param size DEC大小
 *
 * @return 一条DEC中间代码
 */
InterCode newDec(Kind_IC kind, Operand x, int size) {
  InterCode temp = new InterCode_();
  switch (kind) {
    case IC_DEC: {
      temp->kind = IC_DEC;
      temp->u.dec.x = x;
      temp->u.dec.size = size;
      break;
    }
    default: {
      break;
    }
  }
  return temp;
}
/**
 * @brief 打印中间代码
 *
 * @param out 输出流
 * @param head 中间代码链表头指针
 */
void printInterCodes(std::ofstream& out, InterCodeList head) {
  InterCodeList cur = head->next;
  while (cur) {
    switch (cur->code->kind) {
      case IC_LABEL: {
        out << "LABEL ";
        printOperand(out, cur->code->u.oneop.op);
        out << " :";
        break;
      }
      case IC_FUNCTION: {
        out << "FUNCTION ";
        printOperand(out, cur->code->u.oneop.op);
        out << " :";
        break;
      }
      case IC_ASSIGN: {
        printOperand(out, cur->code->u.assign.left);
        out << " := ";
        printOperand(out, cur->code->u.assign.right);
        break;
      }
      case IC_ADD: {
        printOperand(out, cur->code->u.binop.result);
        out << " := ";
        printOperand(out, cur->code->u.binop.op1);
        out << " + ";
        printOperand(out, cur->code->u.binop.op2);
        break;
      }
      case IC_SUB: {
        printOperand(out, cur->code->u.binop.result);
        out << " := ";
        printOperand(out, cur->code->u.binop.op1);
        out << " - ";
        printOperand(out, cur->code->u.binop.op2);
        break;
      }
      case IC_MUL: {
        printOperand(out, cur->code->u.binop.result);
        out << " := ";
        printOperand(out, cur->code->u.binop.op1);
        out << " * ";
        printOperand(out, cur->code->u.binop.op2);
        break;
      }
      case IC_DIV: {
        printOperand(out, cur->code->u.binop.result);
        out << " := ";
        printOperand(out, cur->code->u.binop.op1);
        out << " / ";
        printOperand(out, cur->code->u.binop.op2);
        break;
      }
      case IC_GOTO: {
        out << "GOTO ";
        printOperand(out, cur->code->u.oneop.op);
        break;
      }
      case IC_IF_GOTO: {
        out << "IF ";
        printOperand(out, cur->code->u.if_goto.x);
        out << " ";
        printOperand(out, cur->code->u.if_goto.relop);
        out << " ";
        printOperand(out, cur->code->u.if_goto.y);
        out << " GOTO ";
        printOperand(out, cur->code->u.if_goto.t);
        break;
      }
      case IC_RETURN: {
        out << "RETURN ";
        printOperand(out, cur->code->u.oneop.op);
        break;
      }
      case IC_DEC: {
        out << "DEC ";
        printOperand(out, cur->code->u.dec.x);
        out << " ";
        out << cur->code->u.dec.size;
        break;
      }
      case IC_ARG: {
        out << "ARG ";
        printOperand(out, cur->code->u.oneop.op);
        break;
      }
      case IC_CALL: {
        printOperand(out, cur->code->u.assign.right);
        break;
      }
      case IC_PARAM: {
        out << "PARAM ";
        printOperand(out, cur->code->u.oneop.op);
        break;
      }
    }
    out << "\n";
    cur = cur->next;
  }
}

/**
 * @brief 产生一个操作数
 *
 * @param kind 操作数类型
 * @param val 操作数ID
 *
 * @return 操作数
 */
Operand newOperand(Kind_op kind, std::string val) {
  Operand op = new Operand_();
  op->kind = kind;
  op->loc = 1;
  op->name = val;
  return op;
}

int num_temp = 0;
int num_label = 0;
int num_value = 0;

/**
 * @brief 产生一个临时寄存器操作数
 *
 * @return 临时寄存器操作数,如t0,t1等
 */
Operand newtemp() {
  std::string name = "t" + std::to_string(num_temp);
  ++num_temp;
  Operand op = newOperand(OP_VARIABLE, name);
  return op;
}
/**
 * @brief 产生一个标识符操作数
 *
 * @return 标识符操作数,如label0,label1等
 */
Operand newlabel() {
  std::string name = "label" + std::to_string(num_label);
  ++num_label;
  Operand op = newOperand(OP_LABEL, name);
  return op;
}
/**
 * @brief 产生一个值操作数
 *
 * @return 值操作数,如v0,v1等
 */
Operand newvalue() {
  std::string name = "v" + std::to_string(num_value);
  ++num_value;
  Operand op = newOperand(OP_VARIABLE, name);
  return op;
}

/**
 * @brief 打印操作数
 *
 * @param out 输出流
 * @param op 操作数
 */
void printOperand(std::ofstream& out, Operand op) {
  if (!op) {
    return;
  }
  switch (op->kind) {
    case OP_CONSTANT: {
      out << "#" << op->name;
      break;
    }
    case OP_CALL: {
      out << "CALL " << op->name;
      break;
    }
    case OP_VARIABLE:
    case OP_LABEL:
    case OP_FUNCTION:
    case OP_RELOP:
    case OP_STRING:
    case OP_V_STRING: {
      out << op->name;
      break;
    }
    case OP_READ_ADDRESS: {
      out << "&" << op->name;
      break;
    }
    case OP_WRITE_ADDRESS:
    case OP_WRITE_ADDRESS_BYTE: {
      out << "*" << op->name;
      break;
    }
  }
}
/**
 * @brief 从符号表获取ID对应的操作数
 *
 * @param key 需要查询的ID
 *
 * @return 查询到的操作数
 */
Operand getValueItem(std::string key) {
  auto target = valueTable.find(key);
  if (target == valueTable.end()) {
    return nullptr;
  } else {
    if (target->second.size() == 0) {
      return nullptr;
    } else {
      return target->second.top();
    }
  }
}
/**
 * @brief 添加符号表元素
 *
 * @param key key
 * @param place value
 *
 * @return 插入是否成功
 */
bool insertValueItem(std::string key, Operand place) {
  auto target = valueTable.find(key);
  if (target == valueTable.end()) {
    std::stack<Operand> tmp;
    tmp.push(place);
    valueTable.insert({key, tmp});
  } else {
    target->second.push(place);
  }

  return true;
}
/**
 * @brief 删除符号表元素
 *
 * @param key 元素ID
 */
void deleteValueItem(std::string key) {
  auto target = valueTable.find(key);
  if (target == valueTable.end()) {
    std::cout << "Error in deleteValueItem" << std::endl;
  } else {
    if (target->second.size() == 0) {
      std::cout << "Error in deleteValueItem" << std::endl;
    } else {
      target->second.pop();
    }
  }
}
/**
 * @brief 获取二维数组第二个维度
 *
 * @param key 二维数组ID
 *
 * @return 二维数组对应的第二个维度信息
 */
std::string getDimensionItem(std::string key) {
  auto target = dimensionTable.find(key);
  if (target == dimensionTable.end()) {
    return "";
  } else {
    return target->second;
  }
}
/**
 * @brief 插入二维数组ID与其第二个维度信息
 *
 * @param key 二维数组ID
 * @param size 二维数组第二个维度信息
 * @return 插入是否成功
 */
bool insertDimensionItem(std::string key, std::string size) {
  auto target = dimensionTable.find(key);
  if (target == dimensionTable.end()) {
    dimensionTable.insert({key, size});
  } else {
    std::cout << "Error in insertDimensionItem" << std::endl;
    return false;
  }
}