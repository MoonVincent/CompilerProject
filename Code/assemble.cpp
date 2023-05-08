#include "assemble.hpp"
#include <iostream>
instrSelectedList instrList;

void addInstList(instrSelectedList new_node){
    instrList->next = new_node;
    instrList->next->prev = instrList;
    instrList = instrList->next;
}

instrSelectedList newM(Kind_instr kind, std::string dstName, std::string srcName){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.M.dst = new instrItem_(REG, dstName);
    if (kind == INST_MOVE) {
        ret->instr->u.M.src = new instrItem_(REG, srcName);
    } else {
        ret->instr->u.M.src = new instrItem_(IMM, srcName); 
    }

    return ret;
}

instrSelectedList newR(Kind_instr kind, std::string dst, std::string src1, std::string src2){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.R.dst = new instrItem_(REG, dst);
    ret->instr->u.R.src1 = new instrItem_(REG, src1);
    ret->instr->u.R.src2 = new instrItem_(REG, src2);
    return ret;
}

instrSelectedList newI(Kind_instr kind, std::string dst, std::string src, std::string imm){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.I.dst = new instrItem_(REG, dst);
    ret->instr->u.I.src = new instrItem_(REG, src);
    ret->instr->u.I.imm = new instrItem_(IMM, imm);
    return ret;
}

instrSelectedList newL(Kind_instr kind, std::string dst, std::string imm, std::string src){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.L.dst = new instrItem_(REG, dst);
    ret->instr->u.L.src = new instrItem_(REG, src);
    ret->instr->u.L.imm = new instrItem_(IMM, imm);
    return ret;
}

instrSelectedList newS(Kind_instr kind, std::string src, std::string imm, std::string dst){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.S.dst = new instrItem_(REG, dst);
    ret->instr->u.S.src = new instrItem_(REG, src);
    ret->instr->u.S.imm = new instrItem_(IMM, imm);
    return ret;
}

instrSelectedList newJ(Kind_instr kind, std::string LABEL_REG){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    if (kind == INST_J || kind == INST_JAL) {
        ret->instr->u.J.LABEL_REG = new instrItem_(LABEL, LABEL_REG);
    } else {
        ret->instr->u.J.LABEL_REG = new instrItem_(REG, LABEL_REG);
    }
    return ret;

}

instrSelectedList newB(Kind_instr kind, std::string reg1, std::string reg2, std::string LABEL_){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.B.reg1 = new instrItem_(REG, reg1);
    ret->instr->u.B.reg2 = new instrItem_(REG, reg2);
    ret->instr->u.B.LABEL = new instrItem_(LABEL, LABEL_);
    return ret;
}

instrSelectedList newDIV(Kind_instr kind, std::string src1, std::string src2){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.DIV.src1 = new instrItem_(REG, src1);
    ret->instr->u.DIV.src2 = new instrItem_(REG, src2);
    return ret;
}

instrSelectedList newMflo(Kind_instr kind, std::string dst){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.MFLO.dst = new instrItem_(REG, dst);
    return ret;
}

instrSelectedList newLabel(Kind_instr kind, std::string label){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.Label.LABEL = new instrItem_(LABEL, label);
    return ret;
}

void selectAssign(InterCodeList interCode){
    instrSelectedList newInstr;
    if (interCode->code->u.assign.right->kind == OP_WRITE_ADDRESS) {    //x = *y
        std::string dst = interCode->code->u.assign.left->name;
        std::string src = interCode->code->u.assign.right->name;
        newInstr  = newL(INST_LW, dst, "0", src);
    } else if (interCode->code->u.assign.left->kind == OP_WRITE_ADDRESS) { //*x = y
        std::string dst = interCode->code->u.assign.left->name;
        std::string src = interCode->code->u.assign.right->name;
        newInstr  = newS(INST_SW, src, "0", dst);
    } else if (interCode->code->u.assign.right->kind == OP_CONSTANT) { //li
        std::string dst = interCode->code->u.assign.left->name;
        std::string imm = interCode->code->u.assign.right->name;
        newInstr = newM(INST_LI, dst, imm);
    } else if (interCode->code->u.assign.right->kind == OP_VARIABLE) {    //mv
        std::string dst = interCode->code->u.assign.left->name;
        std::string src = interCode->code->u.assign.right->name;
        newInstr = newM(INST_MOVE, dst, src);
    } else if (interCode->code->u.assign.right->kind == OP_CALL) {  //x := CALL f
        std::string dst = interCode->code->u.assign.left->name;
        std::string funcName = interCode->code->u.assign.right->name;
        newInstr = newJ(INST_JAL, funcName);    // jal f
        addInstList(newInstr);
        newInstr = newM(INST_MOVE, dst, "v0");  //move x, $v0
        newInstr->instr->u.M.src->reg_num = 2;
    }
    addInstList(newInstr);
}

void selectAdd(InterCodeList interCode) {
    instrSelectedList newInstr;
    std::string dst = interCode->code->u.binop.result->name;
    std::string src1 = interCode->code->u.binop.op1->name;
    std::string src2 = interCode->code->u.binop.op2->name;
    if (interCode->code->u.binop.op2->kind == OP_CONSTANT) {    //addi
        newInstr = newI(INST_ADDI, dst, src1, src2);
    } else {    //add
        newInstr = newR(INST_ADD, dst, src1, src2);
    }
    addInstList(newInstr);
}

void selectSub(InterCodeList interCode) {
    instrSelectedList newInstr;
    std::string dst = interCode->code->u.binop.result->name;
    std::string src1 = interCode->code->u.binop.op1->name;
    std::string src2 = interCode->code->u.binop.op2->name;
    if (interCode->code->u.binop.op2->kind == OP_CONSTANT) {    //subi用addi实现
        newInstr = newI(INST_ADDI, dst, src1, "-"+src2);
    } else {    //add
        newInstr = newR(INST_ADD, dst, src1, src2);
    }
    addInstList(newInstr);
}

void selectArg(InterCodeList InterCode){
    //TODO:栈帧的分配估计后续会在这里涉及到
}

void selectCall(InterCodeList interCode) {  //无返回值的函数CALL CALL f
    instrSelectedList newInstr;
    std::string funcName = interCode->code->u.oneop.op->name;
    newInstr = newJ(INST_JAL, funcName);    //jal f
    addInstList(newInstr);
}

void selectDec(InterCodeList interCode) {  //无返回值的函数CALL CALL f
    //TODO:
}

void selectDiv(InterCodeList interCode) { // x:= y / z
    instrSelectedList newInstr;
    std::string dst = interCode->code->u.binop.result->name;
    std::string src1 = interCode->code->u.binop.op1->name;
    std::string src2 = interCode->code->u.binop.op2->name;
    newInstr = newDIV(INST_DIV, src1, src2);
    addInstList(newInstr);
    newInstr = newMflo(INST_MFLO, dst);
    addInstList(newInstr);
}

void selectFunction(InterCodeList interCode) {
    instrSelectedList newInstr;
    std::string funcName = interCode->code->u.oneop.op->name;
    newInstr = newJ(INST_JAL, funcName);
    addInstList(newInstr);
}

void selectGoto(InterCodeList interCode){
    instrSelectedList newInstr;
    std::string labelName = interCode->code->u.oneop.op->name;
    newInstr = newJ(INST_J, labelName);
    addInstList(newInstr);
}

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

void selectLabel(InterCodeList interCode) {
    std::string labelName = interCode->code->u.oneop.op->name;
    instrSelectedList newInstr = newLabel(INST_LABEL, labelName);
    addInstList(newInstr);
}

void selectMul(InterCodeList interCode) {
    std::string dst = interCode->code->u.binop.result->name;
    std::string src1 = interCode->code->u.binop.op1->name;
    std::string src2 = interCode->code->u.binop.op2->name;
    instrSelectedList newInstr;
    if (interCode->code->u.binop.op2->kind == OP_VARIABLE) {
        
    }
    addInstList(newInstr);
}

void selectParam(InterCodeList interCode) {
    //TODO:
}

void selectInstr(InterCodeList interCode){
    instrList = new instrSelectedList_();
    interCode = interCode->next;
    while (interCode != nullptr) {
        switch (interCode->code->kind)
        {
        case IC_ASSIGN:{
            selectAssign(interCode);
            break;
        }
        case IC_ADD:{
            selectAdd(interCode);
            break;
        }
        case IC_SUB:{
            selectSub(interCode);
            break;
        }
        case IC_ARG:{
            selectArg(interCode); 
        }
        case IC_CALL:{
            selectCall(interCode);
            break;
        }
        case IC_DEC:{
            selectDec(interCode);
            break;
        }
        case IC_DIV:{
            selectDiv(interCode);
            break;
        }
        case IC_FUNCTION:{
            selectFunction(interCode);
            break;
        }
        case IC_GOTO:{
            selectGoto(interCode);
            break;
        }
        case IC_IF_GOTO:{
            selectIf(interCode);
            break;
        }
        case IC_LABEL:{
            selectLabel(interCode);
            break;
        }
        case IC_MUL:{
            selectMul(interCode);
            break;
        }
        case IC_PARAM:{
            selectParam(interCode);
            break;
        }
        default:{
            std::cout << "Error" << std::endl;
            break;
        }
        }
    }
}



