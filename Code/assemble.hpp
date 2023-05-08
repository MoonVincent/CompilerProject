#pragma once
#include "intercode.hpp"
#include <string>
typedef struct instrSelected_* instrSelected;
typedef struct instrItem_* instrItem;
typedef struct instrSelectedList_* instrSelectedList;
typedef enum { INST_ADD, INST_ADDI, INST_SUB, INST_MUL, INST_DIV, INST_MFLO, INST_LI, INST_LW, INST_SW, INST_J, INST_JAL, INST_MOVE,
               INST_JR, INST_BEQ, INST_BNE, INST_BGT, INST_BLT, INST_BGE, INST_BLE, INST_LABEL} Kind_instr;
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
        struct {instrItem src1; instrItem src2;} DIV;
        struct {instrItem dst;} MFLO;
        struct {instrItem LABEL;} Label;
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
    instrSelectedList_(){
        prev = nullptr;
        next = nullptr;
    }
};

void selectInstr(InterCodeList interCode);
instrSelectedList newM(Kind_instr kind, std::string dstName, std::string srcName);
instrSelectedList newR(Kind_instr kind, std::string dst, std::string src1, std::string src2);
instrSelectedList newI(Kind_instr kind, std::string dst, std::string src, std::string imm);
instrSelectedList newL(Kind_instr kind, std::string dst, std::string imm, std::string src);
instrSelectedList newS(Kind_instr kind, std::string src, std::string imm, std::string dst);
instrSelectedList newJ(Kind_instr kind, std::string LABEL_REG);
instrSelectedList newB(Kind_instr kind, std::string reg1, std::string reg2, std::string LABEL_);
instrSelectedList newDIV(Kind_instr kind, std::string src1, std::string src2);
instrSelectedList newMflo(Kind_instr kind, std::string dst);
instrSelectedList newLabel(Kind_instr kind, std::string label);
void selectAssign(InterCodeList interCode);
void selectAdd(InterCodeList interCode);
void selectSub(InterCodeList interCode);
void selectArg(InterCodeList InterCode);
void selectCall(InterCodeList interCode);
void selectDec(InterCodeList interCode);
void selectDiv(InterCodeList interCode);
void selectFunction(InterCodeList interCode);
void selectGoto(InterCodeList interCode);
void selectIf(InterCodeList interCode);
void selectLabel(InterCodeList interCode);
void selectMul(InterCodeList interCode);
void selectParam(InterCodeList interCode);
void selectReturn(InterCodeList interCode);
void printSelectedInstr(std::ofstream& out, instrSelectedList instrs);
extern instrSelectedList instrListHead;