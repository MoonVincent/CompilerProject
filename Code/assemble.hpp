#pragma once
#include "intercode.hpp"
#include <string>
typedef struct instrSelected_* instrSelected;
typedef struct instrItem_* instrItem;
typedef struct instrSelectedList_* instrSelectedList;
typedef enum { INST_ADD, INST_ADDI, INST_SUB, INST_MUL, INST_DIV, INST_MFLO, INST_LI, INST_LW, INST_SW, INST_J, INST_JAL, INST_MOVE,
               INST_JR, INST_BEQ, INST_BNE, INST_BGT, INST_BLT, INST_BGE, INST_BLE} Kind_instr;
typedef enum { REG, LABEL, IMM} Kind_item;
struct instrSelected_{
    Kind_instr kind;
    union { 
        struct {instrItem dst; instrItem src1; instrItem src2;} R;
        struct {instrItem dst; instrItem src;} M;
        struct {instrItem dst; instrItem src; instrItem imm;} I;
        struct {instrItem dst; instrItem imm; instrItem src;} L;
        struct {instrItem src; instrItem imm; instrItem dst;} S;
        struct {instrItem LABEL_REG;} J;
        struct {instrItem reg1; instrItem reg2; instrItem LABEL;} B;
    } u; 

};

struct instrItem_{
    Kind_item kind;
    std::string value;
    int reg_num;
    instrItem_(Kind_item k, std::string v){
        kind = k;
        value = v;
        reg_num = -1;
    }
};

struct instrSelectedList_{
    instrSelected instr;
    instrSelectedList prev;
    instrSelectedList next;

};

void selectInstr(InterCodeList interCode);