#include "../include/assemble.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#define VERSION 8 //64位架构
instrSelectedList instrList;  //指令序列
instrSelectedList instrListHead;  //指令序列的头节点
int line = 0; //遍历指令时，当前指令所处行数
int currentFrameSize = 0;  //当前栈帧的大小，因为一定会存储ra和fp，因此初始大小为16
bool isGlobal = true; //全局变量标识
std::unordered_map<std::string, std::pair<int, int>> activeRecord;  //活跃记录
std::unordered_map<std::string, int> vrTranslation; //IR变量与寄存器转换表
std::unordered_map<std::string, int> offset;  //变量在栈帧中的offset
std::unordered_map<std::string, int> globalArrays;  //全局变量定义信息
std::vector<std::string> localArrayOrStruct;
std::unordered_map<std::string, std::string> strTable;  //定义的字符串信息
struct regInfo regs[32];  //RISC-V中32个寄存器信息
/**
 * @brief 向指令链表里加入新指令
 * 
 * @param new_node 指向新指令的指针
 */
void addInstList(instrSelectedList new_node) {
  instrList->next = new_node;
  instrList->next->prev = instrList;
  instrList = instrList->next;
}
/**
 * @brief 新建一个M型命令
 * 
 * @param kind INST_MOVE/INST_LI
 * @param dstName 目的寄存器
 * @param srcName 源寄存器
 * @return instrSelectedList 
 */
instrSelectedList newM(Kind_instr kind, std::string dstName,
                       std::string srcName) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.M.dst = new instrItem_(REG, dstName);
  if (kind == INST_MOVE) {
    ret->instr->u.M.src = new instrItem_(REG, srcName);
  } else {
    ret->instr->u.M.src = new instrItem_(IMM, srcName);
  }
  ++line;
  updateActiveRecord(dstName, line);
  updateActiveRecord(srcName, line);

  return ret;
}
/**
 * @brief 新建R型指令
 * 
 * @param kind INST_ADD/INST_SUB/INST_DIV ...
 * @param dst 目的寄存器
 * @param src1 源寄存器
 * @param src2 源寄存器
 * @return instrSelectedList 
 */
instrSelectedList newR(Kind_instr kind, std::string dst, std::string src1,
                       std::string src2) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.R.dst = new instrItem_(REG, dst);
  ret->instr->u.R.src1 = new instrItem_(REG, src1);
  ret->instr->u.R.src2 = new instrItem_(REG, src2);
  ++line;
  updateActiveRecord(dst, line);
  updateActiveRecord(src1, line);
  updateActiveRecord(src2, line);
  return ret;
}
/**
 * @brief 新建I型指令
 * 
 * @param kind INST_SUBI/ADDI ...
 * @param dst 目的寄存器
 * @param src 源寄存器
 * @param imm 立即数
 * @return instrSelectedList 
 */

instrSelectedList newI(Kind_instr kind, std::string dst, std::string src,
                       std::string imm) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.I.dst = new instrItem_(REG, dst);
  ret->instr->u.I.src = new instrItem_(REG, src);
  ret->instr->u.I.imm = new instrItem_(IMM, imm);
  ++line;
  updateActiveRecord(dst, line);
  updateActiveRecord(src, line);
  return ret;
}

/**
 * @brief 新建L型指令
 * 
 * @param kind INST_LW/INST_LB
 * @param dst 目的寄存器
 * @param imm 立即数偏移量
 * @param src 源寄存器，存储地址
 * @return instrSelectedList 
 */

instrSelectedList newL(Kind_instr kind, std::string dst, std::string imm,
                       std::string src) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.L.dst = new instrItem_(REG, dst);
  ret->instr->u.L.src = new instrItem_(REG, src);
  ret->instr->u.L.imm = new instrItem_(IMM, imm);
  ++line;
  updateActiveRecord(dst, line);
  updateActiveRecord(src, line);
  return ret;
}

/**
 * @brief 新建La指令
 * 
 * @param kind INST_LA
 * @param dst 目的寄存器
 * @param tag 地址标签
 * @return instrSelectedList 
 */

instrSelectedList newLa(Kind_instr kind, std::string dst, std::string tag) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.La.dst = new instrItem_(REG, dst);
  ret->instr->u.La.tag = new instrItem_(LABEL, tag);
  ++line;
  updateActiveRecord(dst, line);
  return ret;
}

/**
 * @brief 新建S型指令
 * 
 * @param kind INST_SW/INST_SB
 * @param src 源寄存器
 * @param imm 立即数
 * @param dst 目的寄存器
 * @return instrSelectedList 
 */

instrSelectedList newS(Kind_instr kind, std::string src, std::string imm,
                       std::string dst) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.S.dst = new instrItem_(REG, dst);
  ret->instr->u.S.src = new instrItem_(REG, src);
  ret->instr->u.S.imm = new instrItem_(IMM, imm);
  ++line;
  updateActiveRecord(src, line);
  updateActiveRecord(dst, line);
  return ret;
}

/**
 * @brief 新建J型指令
 * 
 * @param kind INST_JAL/INST_J
 * @param LABEL_REG 寄存器/目的标签
 * @return instrSelectedList 
 */

instrSelectedList newJ(Kind_instr kind, std::string LABEL_REG) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  if (kind == INST_J || kind == INST_JAL) {
    ret->instr->u.J.LABEL_REG = new instrItem_(LABEL, LABEL_REG);
    ++line;
  } else {
    ret->instr->u.J.LABEL_REG = new instrItem_(REG, LABEL_REG);
    ++line;
    updateActiveRecord(LABEL_REG, line);
  }
  return ret;
}

/**
 * @brief 新建B型指令
 * 
 * @param kind INST_BEQ/INST_BNE ...
 * @param reg1 用于对比的第一个寄存器
 * @param reg2 用于对比的第二个寄存器
 * @param LABEL_ 跳转目标标签
 * @return instrSelectedList 
 */

instrSelectedList newB(Kind_instr kind, std::string reg1, std::string reg2,
                       std::string LABEL_) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.B.reg1 = new instrItem_(REG, reg1);
  ret->instr->u.B.reg2 = new instrItem_(REG, reg2);
  ret->instr->u.B.LABEL = new instrItem_(LABEL, LABEL_);
  ++line;
  updateActiveRecord(reg1, line);
  updateActiveRecord(reg2, line);
  return ret;
}

/**
 * @brief 新建标签
 * 
 * @param kind INST_LABEL
 * @param label label名称
 * @return instrSelectedList 
 */

instrSelectedList newLabel(Kind_instr kind, std::string label) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = kind;
  ret->instr->u.Label.LABEL = new instrItem_(LABEL, label);
  ++line;
  return ret;
}

/**
 * @brief 新建ret指令
 * 
 * @param kind INST_RET
 * @return instrSelectedList 
 */

instrSelectedList newRet(Kind_instr kind) {
  instrSelectedList ret = new instrSelectedList_();
  ret->instr = new instrSelected_();
  ret->instr->kind = INST_RET;
  ++line;
  return ret;
}

/**
 * @brief 为IR中的赋值语句选择指令
 * 
 * @param interCode 一条IR指令
 */

void selectAssign(InterCodeList interCode) {
  instrSelectedList newInstr;
  if (interCode->code->u.assign.right->kind == OP_WRITE_ADDRESS) {  // x = *y
    std::string dst = interCode->code->u.assign.left->name;
    std::string src = interCode->code->u.assign.right->name;
    newInstr = newL(INST_LD, dst, "0", src);
    addInstList(newInstr);
  } else if (interCode->code->u.assign.left->kind ==
             OP_WRITE_ADDRESS) {  //*x = y
    std::string dst = interCode->code->u.assign.left->name;
    std::string src = interCode->code->u.assign.right->name;
    auto target = strTable.find(dst);
    newInstr = newS(INST_SD, src, "0", dst);
    addInstList(newInstr);
  } else if (interCode->code->u.assign.right->kind ==
             OP_WRITE_ADDRESS_BYTE) {  // x = *y
    std::string dst = interCode->code->u.assign.left->name;
    std::string src = interCode->code->u.assign.right->name;
    newInstr = newL(INST_LB, dst, "0", src);
    addInstList(newInstr);
  } else if (interCode->code->u.assign.left->kind ==
             OP_WRITE_ADDRESS_BYTE) {  //*x = y
    std::string dst = interCode->code->u.assign.left->name;
    std::string src = interCode->code->u.assign.right->name;
    newInstr = newS(INST_SB, src, "0", dst);
    addInstList(newInstr);
  } else if (interCode->code->u.assign.right->kind == OP_CONSTANT) {  // li
    std::string dst = interCode->code->u.assign.left->name;
    std::string imm = interCode->code->u.assign.right->name;
    newInstr = newM(INST_LI, dst, imm);
    addInstList(newInstr);
  } else if (interCode->code->u.assign.right->kind == OP_STRING) {  // v = "str"
    std::string dst = interCode->code->u.assign.left->name;
    std::string str = interCode->code->u.assign.right->name;
    strTable.insert({dst, str});
  } else if (interCode->code->u.assign.right->kind == OP_VARIABLE) {  // mv
    std::string dst = interCode->code->u.assign.left->name;
    std::string src = interCode->code->u.assign.right->name;
    if (dst[0] == 'v') {
      int off = getValueOffset(dst, VERSION);
      newInstr = newS(INST_SD, src, "-" + std::to_string(off), "fp");
    } else if (src[0] == 'v') {
      if (globalArrays.find(src) == globalArrays.end()) {
        int off = getValueOffset(src, VERSION);
        if (std::find(localArrayOrStruct.begin(), localArrayOrStruct.end(), src) == localArrayOrStruct.end()) {
          newInstr = newL(INST_LD, dst, "-" + std::to_string(off), "fp");
        } else {
          newInstr = newI(INST_ADDI, dst, "fp", "-" + std::to_string(off));
        }

      } else {
        newInstr = newLa(INST_LA, dst, src);
      }
    } else {
      newInstr = newM(INST_MOVE, dst, src);
    }
    addInstList(newInstr);
  } else if (interCode->code->u.assign.right->kind == OP_CALL) {  // x := CALL f
    std::string dst = interCode->code->u.assign.left->name;
    std::string funcName = interCode->code->u.assign.right->name;
    newInstr = newJ(INST_JAL, funcName);  // jal f
    addInstList(newInstr);
    newInstr = newM(INST_MOVE, dst, "a0");  // move x, $a0
    addInstList(newInstr);
  } else if (interCode->code->u.assign.right->kind == OP_V_STRING) {
    std::string dst = interCode->code->u.assign.left->name;
    std::string src = interCode->code->u.assign.right->name;
    if (strTable.find(src) != strTable.end()) {
      newInstr = newLa(INST_LA, dst, src);
    } else {
      int off = getValueOffset(src, VERSION);
      newInstr = newL(INST_LD, dst, "-" + std::to_string(off), "fp");  // TODO:
    }

    addInstList(newInstr);
  }
}
/**
 * @brief 为IR中的加法选择指令
 * 
 * @param interCode 一条IR代码
 */
void selectAdd(InterCodeList interCode) {
  instrSelectedList newInstr;
  std::string dst = interCode->code->u.binop.result->name;
  std::string src1 = interCode->code->u.binop.op1->name;
  std::string src2 = interCode->code->u.binop.op2->name;
  if (interCode->code->u.binop.op2->kind == OP_CONSTANT) {  // addi
    newInstr = newI(INST_ADDI, dst, src1, src2);
  } else {  // add
    newInstr = newR(INST_ADD, dst, src1, src2);
  }
  addInstList(newInstr);
}
/**
 * @brief 为IR中的减法选择指令
 * 
 * @param interCode 一条IR代码
 */
void selectSub(InterCodeList interCode) {
  instrSelectedList newInstr;
  std::string dst = interCode->code->u.binop.result->name;
  std::string src1 = interCode->code->u.binop.op1->name;
  std::string src2 = interCode->code->u.binop.op2->name;
  if (interCode->code->u.binop.op2->kind == OP_CONSTANT) {  // subi用addi实现
    newInstr = newI(INST_ADDI, dst, src1, "-" + src2);
  } else {  // add
    newInstr = newR(INST_SUB, dst, src1, src2);
  }
  addInstList(newInstr);
}
/**
 * @brief 为IR中函数传参选择指令
 * 
 * @param interCode 一条代码
 * @param argNum 参数个数
 */
void selectArg(InterCodeList interCode, int argNum) {
  // TODO:栈帧的分配估计后续会在这里涉及到
  std::string argName = interCode->code->u.oneop.op->name;
  instrSelectedList newInstr;
  if (strTable.find(argName) == strTable.end()) {
    newInstr = newM(INST_MOVE, "a" + std::to_string(argNum), argName);
  } else {
    newInstr = newLa(INST_LA, "a" + std::to_string(argNum), argName);
  }

  addInstList(newInstr);
}
/**
 * @brief 为IR中的call选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectCall(InterCodeList interCode) {  //无返回值的函数CALL CALL f
  instrSelectedList newInstr;
  std::string funcName = interCode->code->u.oneop.op->name;
  newInstr = newJ(INST_JAL, funcName);  // jal f
  addInstList(newInstr);
}
/**
 * @brief 为IR中的DEC代码选择指令
 * 
 * @param interCode 一条IR代码
 */
void selectDec(InterCodeList interCode) {
  std::string name = interCode->code->u.dec.x->name;
  int size = interCode->code->u.dec.size;
  if (isGlobal) {
    globalArrays.insert({name, size});
  } else {
    getValueOffset(name, size);
    localArrayOrStruct.push_back(name);
  }
}

/**
 * @brief 为IR中的除法选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectDiv(InterCodeList interCode) {  // x:= y / z
  instrSelectedList newInstr;
  std::string dst = interCode->code->u.binop.result->name;
  std::string src1 = interCode->code->u.binop.op1->name;
  std::string src2 = interCode->code->u.binop.op2->name;
  newInstr = newR(INST_DIV, dst, src1, src2);
  addInstList(newInstr);
}

/**
 * @brief 为IR中的函数定义选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectFunction(InterCodeList interCode) {
  instrSelectedList newInstr;
  std::string funcName = interCode->code->u.oneop.op->name;
  newInstr = newLabel(INST_LABEL, funcName);
  addInstList(newInstr);
  newInstr = newI(INST_ADDI, "sp", "sp", "-" + std::to_string(2 * VERSION));
  addInstList(newInstr);
  newInstr = newS(INST_SD, "ra", std::to_string(VERSION), "sp");
  addInstList(newInstr);
  newInstr = newS(INST_SD, "fp", "0", "sp");
  addInstList(newInstr);
  newInstr = newI(INST_ADDI, "fp", "sp", std::to_string(2 * VERSION));
  currentFrameSize += 3 * VERSION;
  addInstList(newInstr);
  offset.clear();
  isGlobal = false;
}

/**
 * @brief 为IR中的GOTO选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectGoto(InterCodeList interCode) {
  instrSelectedList newInstr;
  std::string labelName = interCode->code->u.oneop.op->name;
  newInstr = newJ(INST_J, labelName);
  addInstList(newInstr);
}

/**
 * @brief 为IR中的if选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectIf(InterCodeList interCode) {
  Kind_instr kind;
  std::string relopName = interCode->code->u.if_goto.relop->name;
  if (relopName == "==") {
    kind = INST_BEQ;
  } else if (relopName == "!=") {
    kind = INST_BNE;
  } else if (relopName == ">") {
    kind = INST_BGT;
  } else if (relopName == "<") {
    kind = INST_BLT;
  } else if (relopName == ">=") {
    kind = INST_BGE;
  } else {
    kind = INST_BLE;
  }
  std::string reg1 = interCode->code->u.if_goto.x->name;
  std::string reg2 = interCode->code->u.if_goto.y->name;
  std::string label = interCode->code->u.if_goto.t->name;
  instrSelectedList newInstr = newB(kind, reg1, reg2, label);
  addInstList(newInstr);
}

/**
 * @brief 为IR中的label选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectLabel(InterCodeList interCode) {
  std::string labelName = interCode->code->u.oneop.op->name;
  instrSelectedList newInstr = newLabel(INST_LABEL, labelName);
  addInstList(newInstr);
}

/**
 * @brief 为IR中的乘法选择指令
 * 
 * @param interCode 一条IR代码
 */

void selectMul(InterCodeList interCode) {
  std::string dst = interCode->code->u.binop.result->name;
  std::string src1 = interCode->code->u.binop.op1->name;
  std::string src2 = interCode->code->u.binop.op2->name;
  instrSelectedList newInstr = newR(INST_MUL, dst, src1, src2);
  addInstList(newInstr);
}

/**
 * @brief 为IR中函数参数定义选择指令
 * 
 * @param interCode 一条IR代码
 * @param paramNum 参数个数
 */

void selectParam(InterCodeList interCode, int paramNum) {
  std::string param = interCode->code->u.oneop.op->name;
  offset.insert({param, paramNum * VERSION + 3 * VERSION});
}

/**
 * @brief 为IR中的return选择指令
 * 
 * @param interCode 一条IR代码
 */
void selectReturn(InterCodeList interCode) {
  std::string ret = interCode->code->u.oneop.op->name;
  instrSelectedList newInstr = newM(INST_MOVE, "sp", "fp");
  addInstList(newInstr);
  newInstr = newL(INST_LD, "ra", "-" + std::to_string(VERSION), "fp");
  addInstList(newInstr);
  newInstr = newL(INST_LD, "fp", "-" + std::to_string(2 * VERSION), "fp");
  addInstList(newInstr);
  newInstr = newM(INST_MOVE, "a0", ret);
  addInstList(newInstr);

  newInstr = newRet(INST_RET);
  addInstList(newInstr);
  bool isEnd = false;
  interCode = interCode->next;
  while (interCode != nullptr) {
    if (interCode->code->kind == IC_RETURN) {
      break;
    }
    if (interCode->code->kind == IC_FUNCTION) {
      isEnd = true;
    }
    interCode = interCode->next;
  }
  if (isEnd || interCode == nullptr) {
    currentFrameSize = 0;
    isGlobal = true;
  }
}
/**
 * @brief 指令选择入口
 * 
 * @param interCode 当前被执行指令选择的IR代码
 */
void selectInstr(InterCodeList interCode) {
  instrList = new instrSelectedList_();
  instrListHead = instrList;
  interCode = interCode->next;
  while (interCode != nullptr) {
    switch (interCode->code->kind) {
      case IC_ASSIGN: {
        selectAssign(interCode);
        break;
      }
      case IC_ADD: {
        selectAdd(interCode);
        break;
      }
      case IC_SUB: {
        selectSub(interCode);
        break;
      }
      case IC_ARG: {
        int argNum = 0;
        while (interCode->code->kind == IC_ARG) {
          selectArg(interCode, argNum);
          interCode = interCode->next;
          ++argNum;
        }
        interCode = interCode->prev;
        break;
      }
      case IC_CALL: {
        selectCall(interCode);
        break;
      }
      case IC_DEC: {
        selectDec(interCode);
        break;
      }
      case IC_DIV: {
        selectDiv(interCode);
        break;
      }
      case IC_FUNCTION: {
        selectFunction(interCode);
        break;
      }
      case IC_GOTO: {
        selectGoto(interCode);
        break;
      }
      case IC_IF_GOTO: {
        selectIf(interCode);
        break;
      }
      case IC_LABEL: {
        selectLabel(interCode);
        break;
      }
      case IC_MUL: {
        selectMul(interCode);
        break;
      }
      case IC_PARAM: {
        int paramNum = -1;
        while (interCode->code->kind == IC_PARAM) {
          ++paramNum;
          selectParam(interCode, paramNum);
          interCode = interCode->next;
        }
        interCode = interCode->prev;
        int size = VERSION * (paramNum + 1);
        instrSelectedList newInstr =
            newI(INST_ADDI, "sp", "sp", "-" + std::to_string(size));
        currentFrameSize += size;
        addInstList(newInstr);
        if (paramNum == 0) {
          newInstr = newS(INST_SD, "a0", std::to_string(size - VERSION), "sp");
          addInstList(newInstr);
        }
        if (paramNum == 1) {
          newInstr = newS(INST_SD, "a1", std::to_string(size - VERSION), "sp");
          addInstList(newInstr);
          newInstr =
              newS(INST_SD, "a0", std::to_string(size - 2 * VERSION), "sp");
          addInstList(newInstr);
        }
        if (paramNum == 2) {
          newInstr = newS(INST_SD, "a2", std::to_string(size - VERSION), "sp");
          addInstList(newInstr);
          newInstr =
              newS(INST_SD, "a1", std::to_string(size - 2 * VERSION), "sp");
          addInstList(newInstr);
          newInstr =
              newS(INST_SD, "a0", std::to_string(size - 3 * VERSION), "sp");
          addInstList(newInstr);
        }
        if (paramNum == 3) {
          newInstr = newS(INST_SD, "a3", std::to_string(size - VERSION), "sp");
          addInstList(newInstr);
          newInstr =
              newS(INST_SD, "a2", std::to_string(size - 2 * VERSION), "sp");
          addInstList(newInstr);
          newInstr =
              newS(INST_SD, "a1", std::to_string(size - 3 * VERSION), "sp");
          addInstList(newInstr);
          newInstr =
              newS(INST_SD, "a0", std::to_string(size - 4 * VERSION), "sp");
          addInstList(newInstr);
        }

        break;
      }
      case IC_RETURN: {
        selectReturn(interCode);
        break;
      }
    }
    interCode = interCode->next;
  }

}

/**
 * @brief 寄存器分配入口
 * 
 */

void allocateRegister() {
  instrSelectedList instrs = instrListHead;
  line = 0;
  instrs = instrs->next;
  while (instrs != nullptr) {
    ++line;
    switch (instrs->instr->kind) {
      case INST_ADD:
      case INST_SUB:
      case INST_MUL:
      case INST_DIV: {
        std::string dst = instrs->instr->u.R.dst->value;
        std::string src1 = instrs->instr->u.R.src1->value;
        std::string src2 = instrs->instr->u.R.src2->value;
        instrs->instr->u.R.dst->value = regs[getRegister(dst)].name;
        instrs->instr->u.R.src1->value = regs[getRegister(src1)].name;
        instrs->instr->u.R.src2->value = regs[getRegister(src2)].name;
        break;
      }
      case INST_MOVE: {
        std::string dst = instrs->instr->u.M.dst->value;
        std::string src = instrs->instr->u.M.src->value;
        instrs->instr->u.M.dst->value = regs[getRegister(dst)].name;
        instrs->instr->u.M.src->value = regs[getRegister(src)].name;
        break;
      }
      case INST_LI: {
        std::string dst = instrs->instr->u.M.dst->value;
        /*                 instrs->instr->u.M.dst->regNum = getRegister(dst); */
        instrs->instr->u.M.dst->value = regs[getRegister(dst)].name;
        break;
      }
      case INST_ADDI:
      case INST_SUBI: {
        std::string dst = instrs->instr->u.I.dst->value;
        std::string src = instrs->instr->u.I.src->value;
        instrs->instr->u.I.dst->value = regs[getRegister(dst)].name;
        instrs->instr->u.I.src->value = regs[getRegister(src)].name;
        break;
      }
      case INST_LD: {
        std::string dst = instrs->instr->u.L.dst->value;
        std::string src = instrs->instr->u.L.src->value;
        instrs->instr->u.L.dst->value = regs[getRegister(dst)].name;
        instrs->instr->u.L.src->value = regs[getRegister(src)].name;
        break;
      }
      case INST_SD: {
        std::string src = instrs->instr->u.S.src->value;
        std::string dst = instrs->instr->u.S.dst->value;
        instrs->instr->u.S.src->value = regs[getRegister(src)].name;
        instrs->instr->u.S.dst->value = regs[getRegister(dst)].name;
        break;
      }
      case INST_SB: {
        std::string dst = instrs->instr->u.L.dst->value;
        std::string src = instrs->instr->u.L.src->value;
        instrs->instr->u.L.dst->value = regs[getRegister(dst)].name;
        instrs->instr->u.L.src->value = regs[getRegister(src)].name;
        break;
      }
      case INST_LB: {
        std::string src = instrs->instr->u.S.src->value;
        std::string dst = instrs->instr->u.S.dst->value;
        instrs->instr->u.S.src->value = regs[getRegister(src)].name;
        instrs->instr->u.S.dst->value = regs[getRegister(dst)].name;
        break;
      }
      case INST_BEQ:
      case INST_BGE:
      case INST_BGT:
      case INST_BLE:
      case INST_BLT:
      case INST_BNE: {
        std::string reg1 = instrs->instr->u.B.reg1->value;
        std::string reg2 = instrs->instr->u.B.reg2->value;
        instrs->instr->u.B.reg1->value = regs[getRegister(reg1)].name;
        instrs->instr->u.B.reg2->value = regs[getRegister(reg2)].name;
        break;
      }
      case INST_LABEL:
      case INST_JAL:
      case INST_J: {
        break;
      }
      case INST_LA: {
        std::string dst = instrs->instr->u.La.dst->value;
        instrs->instr->u.La.dst->value = regs[getRegister(dst)].name;
        break;
      }
      case INST_RET: {
        break;
      }
    }
    instrs = instrs->next;
  }
}
/**
 * @brief 为相应的中间代码中的t变量返回真实寄存器编号
 * 
 * @param regName 中间代码中t变量名称，如t156
 * @return int 
 */
int getRegister(std::string regName) {
  if (regName == "sp") {
    return 2;
  }
  if (regName == "ra") {
    return 1;
  }
  if (regName == "a0") {
    return 10;
  }
  if (regName == "a1") {
    return 11;
  }
  if (regName == "a2") {
    return 12;
  }
  if (regName == "a3") {
    return 13;
  }
  if (regName == "fp") {
    return 8;
  }
  auto target = vrTranslation.find(regName);
  if (target == vrTranslation.end()) {
    return getAvaiableReg(regName);
  } else {
    return target->second;
  }
}
/**
 * @brief 更新活跃记录
 * 
 * @param regName 被记录活跃记录的变量
 * @param lineNum 当前所在行数
 */
void updateActiveRecord(std::string regName, int lineNum) {
  if (regName[0] != 't') {
    return;
  }
  auto target = activeRecord.find(regName);
  if (target == activeRecord.end()) {
    activeRecord.insert({regName, {lineNum, lineNum}});
  } else {
    target->second.second = lineNum;
  }
}
/**
 * @brief 为vrName对应的IR中的t变量分配寄存器
 * 
 * @param vrName IR中的t变量，如t156
 * @return int 
 */
int getAvaiableReg(std::string vrName) {
  for (int i = 5; i <= 7; ++i) {
    if (line > regs[i].avaliableLine) {
      vrTranslation.insert({vrName, i});
      regs[i].avaliableLine = activeRecord.find(vrName)->second.second;
      return i;
    }
  }

  for (int i = 28; i <= 31; ++i) {
    if (line > regs[i].avaliableLine) {
      vrTranslation.insert({vrName, i});
      regs[i].avaliableLine = activeRecord.find(vrName)->second.second;
      return i;
    }
  }
  exit(-1);
  return -1;
}

/**
 * @brief 获得变量在栈帧中的offset
 * 
 * @param valueName 变量名称
 * @param size 待分配的变量的大小
 * @return int 
 */

int getValueOffset(std::string valueName, int size) {
  auto target = offset.find(valueName);
  if (target == offset.end()) {
    int off = currentFrameSize;
    offset.insert({valueName, currentFrameSize});
    currentFrameSize += size;
    instrSelectedList newInstr =
        newI(INST_ADDI, "sp", "sp", "-" + std::to_string(size));
    addInstList(newInstr);
    return off;
  } else {
    return target->second;
  }
}

/**
 * @brief 输出活跃记录到文件
 * 
 */
void printActiveRecord(std::ofstream &record) {

  for (auto iter = activeRecord.begin(); iter != activeRecord.end(); ++iter) {
    record << iter->first << " <" << iter->second.first << ", "
           << iter->second.second << ">" << std::endl;
  }
}
/**
 * @brief 打印寄存器分配后的指令序列
 * 
 * @param out 待输出的文件
 * @param instrs 指令选择后的指令序列
 */
void printAllocatedInstr(std::ofstream &out, instrSelectedList instrs) {
  instrs = instrs->next;
  if (globalArrays.size() > 0) {
    out << ".data" << std::endl;
    for (auto array : globalArrays) {
      out << "    " << array.first << ":" << std::endl;
      out << "        .space " << array.second << std::endl;
    }
  }

  if (strTable.size() > 0) {
    if (globalArrays.size() == 0) {
      out << ".data" << std::endl;
    }
    for (auto str : strTable) {
      out << "    " << str.first << ": .string " << str.second << std::endl;
    }
  }

  out << ".globl main" << std::endl;
  out << ".text" << std::endl;

  while (instrs != nullptr) {
    switch (instrs->instr->kind) {
      case INST_ADD: {
        out << "    add " << instrs->instr->u.R.dst->value << ", "
            << instrs->instr->u.R.src1->value << ", "
            << instrs->instr->u.R.src2->value << std::endl;
        break;
      }
      case INST_ADDI: {
        out << "    addi " << instrs->instr->u.I.dst->value << ", "
            << instrs->instr->u.I.src->value << ", "
            << instrs->instr->u.I.imm->value << std::endl;
        break;
      }
      case INST_SUBI: {
        out << "    subi " << instrs->instr->u.I.dst->value << ", "
            << instrs->instr->u.I.src->value << ", "
            << instrs->instr->u.I.imm->value << std::endl;
        break;
      }
      case INST_BEQ: {
        out << "    beq " << instrs->instr->u.B.reg1->value << ", "
            << instrs->instr->u.B.reg2->value << ", "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BGE: {
        out << "    bge " << instrs->instr->u.B.reg1->value << ", "
            << instrs->instr->u.B.reg2->value << ", "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BGT: {
        out << "    bgt " << instrs->instr->u.B.reg1->value << ", "
            << instrs->instr->u.B.reg2->value << ", "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BLE: {
        out << "    ble " << instrs->instr->u.B.reg1->value << ", "
            << instrs->instr->u.B.reg2->value << ", "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BLT: {
        out << "    blt " << instrs->instr->u.B.reg1->value << ", "
            << instrs->instr->u.B.reg2->value << ", "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BNE: {
        out << "    bne " << instrs->instr->u.B.reg1->value << ", "
            << instrs->instr->u.B.reg2->value << ", "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_DIV: {
        out << "    div " << instrs->instr->u.R.dst->value << ", "
            << instrs->instr->u.R.src1->value << ", "
            << instrs->instr->u.R.src2->value << std::endl;
        break;
      }
      case INST_J: {
        out << "    j " << instrs->instr->u.J.LABEL_REG->value << std::endl;
        break;
      }
      case INST_JAL: {
        out << "    jal " << instrs->instr->u.J.LABEL_REG->value << std::endl;
        break;
      }
      case INST_RET: {
        out << "    ret " << std::endl;
        break;
      }
      case INST_LABEL: {
        out << instrs->instr->u.Label.LABEL->value << ":" << std::endl;
        break;
      }
      case INST_LI: {
        out << "    li " << instrs->instr->u.M.dst->value << ", "
            << instrs->instr->u.M.src->value << std::endl;
        break;
      }
      case INST_LD: {
        out << "    ld " << instrs->instr->u.L.dst->value << ", "
            << instrs->instr->u.L.imm->value << "("
            << instrs->instr->u.L.src->value << ")" << std::endl;
        break;
      }
      case INST_LB: {
        out << "    lb " << instrs->instr->u.L.dst->value << ", "
            << instrs->instr->u.L.imm->value << "("
            << instrs->instr->u.L.src->value << ")" << std::endl;
        break;
      }
      case INST_MOVE: {
        out << "    mv " << instrs->instr->u.M.dst->value << ", "
            << instrs->instr->u.M.src->value << std::endl;
        break;
      }
      case INST_MUL: {
        out << "    mul " << instrs->instr->u.R.dst->value << ", "
            << instrs->instr->u.R.src1->value << ", "
            << instrs->instr->u.R.src2->value << std::endl;
        break;
      }
      case INST_SUB: {
        out << "    sub " << instrs->instr->u.R.dst->value << ", "
            << instrs->instr->u.R.src1->value << ", "
            << instrs->instr->u.R.src2->value << std::endl;
        break;
      }
      case INST_SD: {
        out << "    sd " << instrs->instr->u.S.src->value << ", "
            << instrs->instr->u.S.imm->value << "("
            << instrs->instr->u.S.dst->value << ")" << std::endl;
        break;
      }
      case INST_SB: {
        out << "    sb " << instrs->instr->u.S.src->value << ", "
            << instrs->instr->u.S.imm->value << "("
            << instrs->instr->u.S.dst->value << ")" << std::endl;
        break;
      }
      case INST_LA: {
        out << "    la " << instrs->instr->u.La.dst->value << ", "
            << instrs->instr->u.La.tag->value << std::endl;
        break;
      }
      default: {
        std::cout << "Error in print allocate" << std::endl;
      }
    }
    instrs = instrs->next;
  }
}
/**
 * @brief 输出指令选择后的指令序列到文件
 * 
 * @param out 对应的输出文件
 * @param instrs 指令选择后的指令序列
 */
void printSelectedInstr(std::ofstream &out, instrSelectedList instrs) {
  instrs = instrs->next;
  while (instrs != nullptr) {
    switch (instrs->instr->kind) {
      case INST_ADD: {
        out << "    add reg(" << instrs->instr->u.R.dst->value << "), reg("
            << instrs->instr->u.R.src1->value << "), reg("
            << instrs->instr->u.R.src2->value << ")" << std::endl;
        break;
      }
      case INST_ADDI: {
        out << "    addi reg(" << instrs->instr->u.I.dst->value << "), reg("
            << instrs->instr->u.I.src->value << "), "
            << instrs->instr->u.I.imm->value << std::endl;
        break;
      }
      case INST_SUBI: {
        out << "    subi reg(" << instrs->instr->u.I.dst->value << "), reg("
            << instrs->instr->u.I.src->value << "), "
            << instrs->instr->u.I.imm->value << std::endl;
        break;
      }
      case INST_BEQ: {
        out << "    beq reg(" << instrs->instr->u.B.reg1->value << "), reg("
            << instrs->instr->u.B.reg2->value << "), "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BGE: {
        out << "    bge reg(" << instrs->instr->u.B.reg1->value << "), reg("
            << instrs->instr->u.B.reg2->value << "), "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BGT: {
        out << "    bgt reg(" << instrs->instr->u.B.reg1->value << "), reg("
            << instrs->instr->u.B.reg2->value << "), "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BLE: {
        out << "    ble reg(" << instrs->instr->u.B.reg1->value << "), reg("
            << instrs->instr->u.B.reg2->value << "), "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BLT: {
        out << "    blt reg(" << instrs->instr->u.B.reg1->value << "), reg("
            << instrs->instr->u.B.reg2->value << "), "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_BNE: {
        out << "    bne reg(" << instrs->instr->u.B.reg1->value << "), reg("
            << instrs->instr->u.B.reg2->value << "), "
            << instrs->instr->u.B.LABEL->value << std::endl;
        break;
      }
      case INST_DIV: {
        out << "    div reg(" << instrs->instr->u.R.dst->value << "), reg("
            << instrs->instr->u.R.src1->value << "), reg("
            << instrs->instr->u.R.src2->value << ")" << std::endl;
        break;
      }
      case INST_J: {
        out << "    j " << instrs->instr->u.J.LABEL_REG->value << std::endl;
        break;
      }
      case INST_JAL: {
        out << "    jal " << instrs->instr->u.J.LABEL_REG->value << std::endl;
        break;
      }
      case INST_RET: {
        out << "    ret" << std::endl;
        break;
      }
      case INST_LABEL: {
        out << instrs->instr->u.Label.LABEL->value << ":" << std::endl;
        break;
      }
      case INST_LI: {
        out << "    li reg(" << instrs->instr->u.M.dst->value << "), "
            << instrs->instr->u.M.src->value << std::endl;
        break;
      }
      case INST_LD: {
        out << "    ld reg(" << instrs->instr->u.L.dst->value << "), "
            << instrs->instr->u.L.imm->value << "(reg("
            << instrs->instr->u.L.src->value << "))" << std::endl;
        break;
      }
      case INST_LB: {
        out << "    lb reg(" << instrs->instr->u.L.dst->value << "), "
            << instrs->instr->u.L.imm->value << "(reg("
            << instrs->instr->u.L.src->value << "))" << std::endl;
        break;
      }
      case INST_MOVE: {
        out << "    mv reg(" << instrs->instr->u.M.dst->value << "), reg("
            << instrs->instr->u.M.src->value << ")" << std::endl;
        break;
      }
      case INST_MUL: {
        out << "    mul reg(" << instrs->instr->u.R.dst->value << "), reg("
            << instrs->instr->u.R.src1->value << "), reg("
            << instrs->instr->u.R.src2->value << ")" << std::endl;
        break;
      }
      case INST_SUB: {
        out << "    sub reg(" << instrs->instr->u.R.dst->value << "), reg("
            << instrs->instr->u.R.src1->value << "), reg("
            << instrs->instr->u.R.src2->value << ")" << std::endl;
        break;
      }
      case INST_SD: {
        out << "    sd reg(" << instrs->instr->u.S.src->value << "), "
            << instrs->instr->u.S.imm->value << "(reg("
            << instrs->instr->u.S.dst->value << "))" << std::endl;
        break;
      }
      case INST_SB: {
        out << "    sb reg(" << instrs->instr->u.S.src->value << "), "
            << instrs->instr->u.S.imm->value << "(reg("
            << instrs->instr->u.S.dst->value << "))" << std::endl;
        break;
      }
      case INST_LA: {
        out << "    la reg(" << instrs->instr->u.La.dst->value <<"), "
            << instrs->instr->u.La.tag << std::endl;
            break;
      }
    }
    instrs = instrs->next;
  }
}
/**
 * @brief 初始化RISC-V的32个寄存器的信息
 * 
 */
void initializeRegs() {
  regs[0].name = "zero";
  regs[0].avaliableLine = -1;
  regs[1].name = "ra";
  regs[1].avaliableLine = -1;
  regs[2].name = "sp";
  regs[2].avaliableLine = -1;
  regs[3].name = "gp";
  regs[3].avaliableLine = -1;
  regs[4].name = "tp";
  regs[4].avaliableLine = -1;
  regs[5].name = "t0";
  regs[5].avaliableLine = -1;
  regs[6].name = "t1";
  regs[6].avaliableLine = -1;
  regs[7].name = "t2";
  regs[7].avaliableLine = -1;
  regs[8].name = "fp";
  regs[8].avaliableLine = -1;
  regs[9].name = "s1";
  regs[9].avaliableLine = -1;
  regs[10].name = "a0";
  regs[10].avaliableLine = -1;
  regs[11].name = "a1";
  regs[11].avaliableLine = -1;
  regs[12].name = "a2";
  regs[12].avaliableLine = -1;
  regs[13].name = "a3";
  regs[13].avaliableLine = -1;
  regs[14].name = "a4";
  regs[14].avaliableLine = -1;
  regs[15].name = "a5";
  regs[15].avaliableLine = -1;
  regs[16].name = "a6";
  regs[16].avaliableLine = -1;
  regs[17].name = "a7";
  regs[17].avaliableLine = -1;
  regs[18].name = "s2";
  regs[18].avaliableLine = -1;
  regs[19].name = "s3";
  regs[19].avaliableLine = -1;
  regs[20].name = "s4";
  regs[20].avaliableLine = -1;
  regs[21].name = "s5";
  regs[21].avaliableLine = -1;
  regs[22].name = "s6";
  regs[22].avaliableLine = -1;
  regs[23].name = "s7";
  regs[23].avaliableLine = -1;
  regs[24].name = "s8";
  regs[24].avaliableLine = -1;
  regs[25].name = "s9";
  regs[25].avaliableLine = -1;
  regs[26].name = "s10";
  regs[26].avaliableLine = -1;
  regs[27].name = "s11";
  regs[27].avaliableLine = -1;
  regs[28].name = "t3";
  regs[28].avaliableLine = -1;
  regs[29].name = "t4";
  regs[29].avaliableLine = -1;
  regs[30].name = "t5";
  regs[30].avaliableLine = -1;
  regs[31].name = "t6";
  regs[31].avaliableLine = -1;
}
