#include "assemble.hpp"
#include <iostream>
#include <unordered_map>
instrSelectedList instrList;
instrSelectedList instrListHead;
int line = 0;
int currentFrameSize = 0; //当前栈帧的大小，因为一定会存储ra和fp，因此初始大小为16
bool isGlobal = true;
std::unordered_map<std::string, std::pair<int, int>> activeRecord;
std::unordered_map<std::string, int> vrTranslation;
std::unordered_map<std::string, int> offset;
std::unordered_map<std::string, int> globalArrays;
struct regInfo regs[32];
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
    ++line;
    updateActiveRecord(dstName, line);
    updateActiveRecord(srcName, line);

    return ret;
}

instrSelectedList newR(Kind_instr kind, std::string dst, std::string src1, std::string src2){
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

instrSelectedList newI(Kind_instr kind, std::string dst, std::string src, std::string imm){
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

instrSelectedList newL(Kind_instr kind, std::string dst, std::string imm, std::string src){
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

instrSelectedList newLa(Kind_instr kind, std::string dst, std::string tag) {
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.La.dst = new instrItem_(REG, dst);
    ret->instr->u.La.tag = new instrItem_(LABEL, tag);
    ++line;
    return ret;
}

instrSelectedList newS(Kind_instr kind, std::string src, std::string imm, std::string dst){
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

instrSelectedList newJ(Kind_instr kind, std::string LABEL_REG){
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

instrSelectedList newB(Kind_instr kind, std::string reg1, std::string reg2, std::string LABEL_){
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

instrSelectedList newDIV(Kind_instr kind, std::string src1, std::string src2){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.DIV.src1 = new instrItem_(REG, src1);
    ret->instr->u.DIV.src2 = new instrItem_(REG, src2);
    ++line;
    updateActiveRecord(src1, line);
    updateActiveRecord(src2, line);
    return ret;
}

instrSelectedList newMflo(Kind_instr kind, std::string dst){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.MFLO.dst = new instrItem_(REG, dst);
    ++line;
    updateActiveRecord(dst, line);
    return ret;
}

instrSelectedList newLabel(Kind_instr kind, std::string label){
    instrSelectedList ret = new instrSelectedList_();
    ret->instr = new instrSelected_();
    ret->instr->kind = kind;
    ret->instr->u.Label.LABEL = new instrItem_(LABEL, label);
    ++line;
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
        if (dst[0] == 'v') {
            int off = getValueOffset(dst, 8);
            newInstr = newS(INST_SW, src, "-" + std::to_string(off), "$fp");  //TODO:
        } else if (src[0] == 'v') {
            if (globalArrays.find(src) == globalArrays.end()) {
                int off = getValueOffset(src, 8);
                newInstr = newL(INST_LW, dst, "-" + std::to_string(off), "$fp");  //TODO:
            } else {
                newInstr = newLa(INST_LA, dst, src);
            }
        } else {
            newInstr = newM(INST_MOVE, dst, src);
        }
    } else if (interCode->code->u.assign.right->kind == OP_CALL) {  //x := CALL f
        std::string dst = interCode->code->u.assign.left->name;
        std::string funcName = interCode->code->u.assign.right->name;
        newInstr = newJ(INST_JAL, funcName);    // jal f
        addInstList(newInstr);
        newInstr = newM(INST_MOVE, dst, "$v0");  //move x, $v0
        //newInstr->instr->u.M.src->reg_num = 2; 
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

void selectArg(InterCodeList interCode, int argNum){
    //TODO:栈帧的分配估计后续会在这里涉及到
    std::string argName = interCode->code->u.oneop.op->name;
    instrSelectedList newInstr = newM(INST_MOVE, "$a" + std::to_string(argNum), argName);
    addInstList(newInstr);

}

void selectCall(InterCodeList interCode) {  //无返回值的函数CALL CALL f
    instrSelectedList newInstr;
    std::string funcName = interCode->code->u.oneop.op->name;
    newInstr = newJ(INST_JAL, funcName);    //jal f
    addInstList(newInstr);
}

void selectDec(InterCodeList interCode) {
    if (isGlobal) {
        std::string name = interCode->code->u.dec.x->name;
        int size = interCode->code->u.dec.size;
        globalArrays.insert({name, size});
    } else {
        std::string name = interCode->code->u.dec.x->name;
        int size = interCode->code->u.dec.size;
        getValueOffset(name, size);
    }
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
    newInstr = newLabel(INST_LABEL, funcName);
    addInstList(newInstr);
    newInstr = newI(INST_ADDI, "$sp", "$sp", "-16");
    addInstList(newInstr);
    newInstr = newS(INST_SW, "$ra", "8", "$sp");
    addInstList(newInstr);
    newInstr = newS(INST_SW, "$fp", "0", "$sp");
    addInstList(newInstr);
    newInstr = newI(INST_ADDI, "$fp", "$sp", "16");
    currentFrameSize += 16;
    addInstList(newInstr);
    offset.clear();
    isGlobal = false;
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
    instrSelectedList newInstr = newR(INST_MUL, dst, src1, src2);
    addInstList(newInstr);
}

void selectParam(InterCodeList interCode, int paramNum) {

    std::string param = interCode->code->u.oneop.op->name;
    offset.insert({param, paramNum * 4 + 12});

}

void selectReturn(InterCodeList interCode) {
    std::string ret = interCode->code->u.oneop.op->name;
    instrSelectedList newInstr = newM(INST_MOVE, "$sp", "$fp");
    addInstList(newInstr);
    newInstr = newL(INST_LW, "$ra", "-8", "$fp");
    addInstList(newInstr);
    newInstr = newL(INST_LW, "$fp", "-16", "$fp");
    addInstList(newInstr);
    newInstr = newM(INST_MOVE, "$v0", ret);
    addInstList(newInstr);

    newInstr = newJ(INST_JR, "$ra");
    addInstList(newInstr);
    currentFrameSize = 0;
    isGlobal = true;
}

void selectInstr(InterCodeList interCode){
    instrList = new instrSelectedList_();
    instrListHead = instrList;
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
            int argNum = 0;
            while (interCode->code->kind == IC_ARG){
                selectArg(interCode, argNum); 
                interCode = interCode->next;
                ++argNum;
            }
            interCode = interCode->prev;
            break;
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
            int paramNum = -1;
            while (interCode->code->kind == IC_PARAM) {
                ++paramNum;
                selectParam(interCode, paramNum);
                interCode = interCode->next;
            }
            interCode = interCode->prev;
            int size = 8 * (paramNum + 1);
            instrSelectedList newInstr = newI(INST_ADDI, "$sp", "$sp", "-" + std::to_string(size));
            addInstList(newInstr);
            if (paramNum >= 0) {
                newInstr = newS(INST_SW, "$a0", std::to_string(size - 8), "$sp");
                addInstList(newInstr);
            }
            if (paramNum >= 1) {
                newInstr = newS(INST_SW, "$a1", std::to_string(size - 16), "$sp");
                addInstList(newInstr);
            }
            if (paramNum >= 2) {
                newInstr = newS(INST_SW, "$a2", std::to_string(size - 24), "$sp");
                addInstList(newInstr);
            }
            if (paramNum >= 3) {
                newInstr = newS(INST_SW, "$a3", std::to_string(size - 32), "$sp");
                addInstList(newInstr);
            }

            break;
        }
        case IC_RETURN:{
            selectReturn(interCode);
            break;
        }
        case IC_READ:{
            std::string dst = interCode->code->u.oneop.op->name;
            instrSelectedList newInstr = newJ(INST_JAL, "read");
            addInstList(newInstr);
            newInstr = newM(INST_MOVE, dst, "$v0");
            addInstList(newInstr);
            break;
        }
        case IC_WRITE:{
            std::string src = interCode->code->u.oneop.op->name;
            instrSelectedList newInstr = newM(INST_MOVE, "$a0", src);
            addInstList(newInstr);
            newInstr = newJ(INST_JAL, "write");
            addInstList(newInstr);
            break;
        }
        default:{
            std::cout << "Error" << std::endl;
            break;
        }
        }
        interCode = interCode->next;
    }
    std::ofstream sr("test.sr");
    printSelectedInstr(sr, instrListHead);
    printActiveRecord();
    initializeRegs();
    allocateRegister();
    std::ofstream rr("test.rr");
    printAllocatedInstr(rr, instrListHead);
}

void allocateRegister() {
    instrSelectedList instrs = instrListHead;
    line = 0;
    instrs = instrs->next;
    while(instrs != nullptr) {
        ++line;
        switch(instrs->instr->kind){
            case INST_ADD:
            case INST_SUB:
            case INST_MUL:{
                std::string dst = instrs->instr->u.R.dst->value;
                std::string src1 = instrs->instr->u.R.src1->value;
                std::string src2 = instrs->instr->u.R.src2->value;
/*                 instrs->instr->u.R.dst->regNum = getRegister(dst);
                instrs->instr->u.R.src1->regNum = getRegister(src1);
                instrs->instr->u.R.src1->regNum = getRegister(src2); */
                instrs->instr->u.R.dst->value = regs[getRegister(dst)].name;
                instrs->instr->u.R.src1->value = regs[getRegister(src1)].name;
                instrs->instr->u.R.src2->value = regs[getRegister(src2)].name;
                break;
            }
            case INST_MOVE:{
                std::string dst = instrs->instr->u.M.dst->value;
                std::string src = instrs->instr->u.M.src->value;
/*                 instrs->instr->u.M.dst->regNum = getRegister(dst);
                instrs->instr->u.M.src->regNum = getRegister(src); */
                instrs->instr->u.M.dst->value = regs[getRegister(dst)].name;
                instrs->instr->u.M.src->value = regs[getRegister(src)].name;
                break;
            }
            case INST_LI:{
                std::string dst = instrs->instr->u.M.dst->value;
/*                 instrs->instr->u.M.dst->regNum = getRegister(dst); */
                instrs->instr->u.M.dst->value = regs[getRegister(dst)].name;
                break;
            }
            case INST_ADDI:{
                std::string dst = instrs->instr->u.I.dst->value;
/*                 instrs->instr->u.I.dst->regNum = getRegister(dst);*/   
                std::string src = instrs->instr->u.I.src->value;             
                instrs->instr->u.I.dst->value = regs[getRegister(dst)].name;
                instrs->instr->u.I.src->value = regs[getRegister(src)].name;
                break;
            }
            case INST_LW:{
                std::string dst = instrs->instr->u.L.dst->value;
                std::string src = instrs->instr->u.L.src->value;
/*                 instrs->instr->u.L.dst->regNum = getRegister(dst);
                instrs->instr->u.L.src->regNum = getRegister(src); */
                instrs->instr->u.L.dst->value = regs[getRegister(dst)].name;
                instrs->instr->u.L.src->value = regs[getRegister(src)].name;
                break;
            }
            case INST_SW:{
                std::string src = instrs->instr->u.S.src->value;
                std::string dst = instrs->instr->u.S.dst->value;
/*                 instrs->instr->u.S.src->regNum = getRegister(src);
                instrs->instr->u.S.dst->regNum = getRegister(dst); */
                instrs->instr->u.S.src->value = regs[getRegister(src)].name;
                instrs->instr->u.S.dst->value = regs[getRegister(dst)].name;
                break;
            }
            case INST_JR:{
                std::string reg = instrs->instr->u.J.LABEL_REG->value;
/*                 instrs->instr->u.J.LABEL_REG->regNum = getRegister(reg); */
                instrs->instr->u.J.LABEL_REG->value = regs[getRegister(reg)].name;
                break;
            }
            case INST_BEQ:
            case INST_BGE:
            case INST_BGT:
            case INST_BLE:
            case INST_BLT:
            case INST_BNE:{
                std::string reg1 = instrs->instr->u.B.reg1->value;
                std::string reg2 = instrs->instr->u.B.reg2->value;
/*                 instrs->instr->u.B.reg1->regNum = getRegister(reg1);
                instrs->instr->u.B.reg2->regNum = getRegister(reg2); */
                instrs->instr->u.B.reg1->value = regs[getRegister(reg1)].name;
                instrs->instr->u.B.reg2->value = regs[getRegister(reg2)].name;
                break;
            }
            case INST_DIV:{
                std::string src1 = instrs->instr->u.DIV.src1->value;
                std::string src2 = instrs->instr->u.DIV.src2->value;
/*                 instrs->instr->u.DIV.src1->regNum = getRegister(src1);
                instrs->instr->u.DIV.src2->regNum = getRegister(src2); */
                instrs->instr->u.DIV.src1->value = regs[getRegister(src1)].name;
                instrs->instr->u.DIV.src2->value = regs[getRegister(src2)].name;
                break;
            }
            case INST_MFLO:{
                std::string dst = instrs->instr->u.MFLO.dst->value;
/*                 instrs->instr->u.MFLO.dst->regNum = getRegister(dst); */
                instrs->instr->u.MFLO.dst->value = regs[getRegister(dst)].name;
                break;
            }
            case INST_LABEL:{
                std::cout << "LABEL" << std::endl;
                break;
            }
            case INST_JAL:
            case INST_J:{
                std::cout << "J and JAL" << std::endl;
                break;
            }
            case INST_LA:{
                std::string dst = instrs->instr->u.La.dst->value;
                instrs->instr->u.La.dst->value = regs[getRegister(dst)].name;
                break;
            }
            default:{
                std::cout << "Error in select" << std::endl;
            }

        }
        instrs = instrs->next;
    }
}

int getRegister(std::string regName) {
    if (regName == "$sp") {
        return 29;
    }
    if (regName == "$v0") {
        return 2;
    }
    if (regName == "$ra") {
        return 31;
    }
    if (regName == "$a0") {
        return 4;
    }
    if (regName == "$a1") {
        return 5;
    }
    if (regName == "$a2") {
        return 6;
    }
    if (regName == "$a3") {
        return 7;
    }
    if (regName == "$fp") {
        return 30;
    }
    auto target = vrTranslation.find(regName);
    if (target == vrTranslation.end()) {
        return getAvaiableReg(regName);
    } else {
        return target->second;
    }
}

void updateActiveRecord(std::string regName, int lineNum) {
    if (regName[0] != 't') {
        return ;
    }
    auto target = activeRecord.find(regName);
    if (target == activeRecord.end()) {
        activeRecord.insert({regName, {lineNum, lineNum}});
    } else {
        target->second.second = lineNum;
    }
}

int getAvaiableReg(std::string vrName){
    for (int i = 8; i <= 15; ++i) {
        if (line > regs[i].avaliableLine) {
            vrTranslation.insert({vrName, i});
            regs[i].avaliableLine = activeRecord.find(vrName)->second.second;
            return i;
        }
    }
    std::cout << "In getAvaliableReg" << std::endl;
    exit(-1);
    return -1;
}

int getValueOffset(std::string valueName, int size) {
    auto target = offset.find(valueName);
    if (target == offset.end()) {
        int off = currentFrameSize;
        offset.insert({valueName, currentFrameSize});
        currentFrameSize += size;
        instrSelectedList newInstr = newI(INST_ADDI, "$sp", "$sp", "-" + std::to_string(size));
        addInstList(newInstr);
        return off;
    } else {
        return target->second;
    }
}

void printActiveRecord(){
    std::ofstream record("record.i");
    for (auto iter = activeRecord.begin(); iter != activeRecord.end(); ++iter) {
        record << iter->first << " <" << iter->second.first << ", " << iter->second.second << ">" << std::endl;
    }
}

void printAllocatedInstr(std::ofstream& out, instrSelectedList instrs){
    instrs = instrs->next;
    if (globalArrays.size() > 0) {
        out << ".data" << std::endl;
        for (auto array : globalArrays) {
            out << "    " << array.first << ":" << std::endl;
            out << "        .space " << array.second << std::endl;
        }
    }
    out << ".global main" << std::endl;
    out << ".text" << std::endl;
    while (instrs != nullptr) {
        switch(instrs->instr->kind){
            case INST_ADD:{
                out << "    add " << instrs->instr->u.R.dst->value << ", " 
                    << instrs->instr->u.R.src1->value << ", "
                    << instrs->instr->u.R.src2->value << std::endl;
                break;
            }
            case INST_ADDI:{
                out << "    addi " << instrs->instr->u.I.dst->value << ", " 
                    << instrs->instr->u.I.src->value << ", "
                    << instrs->instr->u.I.imm->value << std::endl;
                break;
            }
            case INST_BEQ:{
                out << "    beq " << instrs->instr->u.B.reg1->value << ", " 
                    << instrs->instr->u.B.reg2->value << ", "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BGE:{
                out << "    bge " << instrs->instr->u.B.reg1->value << ", " 
                    << instrs->instr->u.B.reg2->value << ", "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BGT:{
                out << "    bgt " << instrs->instr->u.B.reg1->value << ", " 
                    << instrs->instr->u.B.reg2->value << ", "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BLE:{
                out << "    ble " << instrs->instr->u.B.reg1->value << ", " 
                    << instrs->instr->u.B.reg2->value << ", "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BLT:{
                out << "    blt " << instrs->instr->u.B.reg1->value << ", " 
                    << instrs->instr->u.B.reg2->value << ", "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BNE:{
                out << "    bne " << instrs->instr->u.B.reg1->value << ", " 
                    << instrs->instr->u.B.reg2->value << ", "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_DIV:{
                out << "    div " << instrs->instr->u.DIV.src1->value << ", " 
                    << instrs->instr->u.DIV.src2->value << "" << std::endl;
                break;
            }
            case INST_J:{
                out << "    j " << instrs->instr->u.J.LABEL_REG->value << std::endl;
                break;
            }
            case INST_JAL:{
                out << "    jal " << instrs->instr->u.J.LABEL_REG->value << std::endl;
                break;
            }
            case INST_JR:{
                out << "    jr " << instrs->instr->u.J.LABEL_REG->value << std::endl;
                break;
            }
            case INST_LABEL:{
                out << instrs->instr->u.Label.LABEL->value <<":" << std::endl;
                break;
            }
            case INST_LI:{
                out << "    li " << instrs->instr->u.M.dst->value << ", "
                    << instrs->instr->u.M.src->value << std::endl;
                break;
            }
            case INST_LW:{
                out << "    lw " << instrs->instr->u.L.dst->value << ", "
                    << instrs->instr->u.L.imm->value << "("
                    << instrs->instr->u.L.src->value << ")" << std::endl;
                break;
            }
            case INST_MFLO:{
                out << "    mflo " << instrs->instr->u.MFLO.dst->value << std::endl;
                break;
            }
            case INST_MOVE:{
                out << "    move " << instrs->instr->u.M.dst->value << ", "
                    << instrs->instr->u.M.src->value << std::endl;
                break;
            }
            case INST_MUL:{
                out << "    mul " << instrs->instr->u.R.dst->value << ", " 
                    << instrs->instr->u.R.src1->value << ", "
                    << instrs->instr->u.R.src2->value << std::endl;
                break;
            }
            case INST_SUB:{
                out << "    sub " << instrs->instr->u.R.dst->value << ", " 
                    << instrs->instr->u.R.src1->value << ", "
                    << instrs->instr->u.R.src2->value << std::endl;
                break;
            }
            case INST_SW:{
                out << "    sw " << instrs->instr->u.S.src->value << ", "
                    << instrs->instr->u.S.imm->value << "("
                    << instrs->instr->u.S.dst->value << ")" << std::endl;
                break;
            }
            case INST_LA:{
                out << "    la " << instrs->instr->u.La.dst->value << ", "
                    << instrs->instr->u.La.tag->value << std::endl;
                break;
            }
            default:{
                std::cout << "Error in print" << std::endl;
            }
        }
        instrs = instrs->next;
    }
}

void printSelectedInstr(std::ofstream& out, instrSelectedList instrs){
    instrs = instrs->next;
    while (instrs != nullptr) {
        switch(instrs->instr->kind){
            case INST_ADD:{
                out << "    add reg(" << instrs->instr->u.R.dst->value << "), reg(" 
                    << instrs->instr->u.R.src1->value << "), reg("
                    << instrs->instr->u.R.src2->value << ")" << std::endl;
                break;
            }
            case INST_ADDI:{
                out << "    addi reg(" << instrs->instr->u.I.dst->value << "), reg(" 
                    << instrs->instr->u.I.src->value << "), "
                    << instrs->instr->u.I.imm->value << std::endl;
                break;
            }
            case INST_BEQ:{
                out << "    beq reg(" << instrs->instr->u.B.reg1->value << "), reg(" 
                    << instrs->instr->u.B.reg2->value << "), "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BGE:{
                out << "    bge reg(" << instrs->instr->u.B.reg1->value << "), reg(" 
                    << instrs->instr->u.B.reg2->value << "), "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BGT:{
                out << "    bgt reg(" << instrs->instr->u.B.reg1->value << "), reg(" 
                    << instrs->instr->u.B.reg2->value << "), "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BLE:{
                out << "    ble reg(" << instrs->instr->u.B.reg1->value << "), reg(" 
                    << instrs->instr->u.B.reg2->value << "), "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BLT:{
                out << "    blt reg(" << instrs->instr->u.B.reg1->value << "), reg(" 
                    << instrs->instr->u.B.reg2->value << "), "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_BNE:{
                out << "    bne reg(" << instrs->instr->u.B.reg1->value << "), reg(" 
                    << instrs->instr->u.B.reg2->value << "), "
                    << instrs->instr->u.B.LABEL->value << std::endl;
                break;
            }
            case INST_DIV:{
                out << "    div reg(" << instrs->instr->u.DIV.src1->value << "), reg(" 
                    << instrs->instr->u.DIV.src2->value << ")" << std::endl;
                break;
            }
            case INST_J:{
                out << "    j " << instrs->instr->u.J.LABEL_REG->value << std::endl;
                break;
            }
            case INST_JAL:{
                out << "    jal " << instrs->instr->u.J.LABEL_REG->value << std::endl;
                break;
            }
            case INST_JR:{
                out << "    jr " << instrs->instr->u.J.LABEL_REG->value << std::endl;
                break;
            }
            case INST_LABEL:{
                out << instrs->instr->u.Label.LABEL->value <<":" << std::endl;
                break;
            }
            case INST_LI:{
                out << "    li reg(" << instrs->instr->u.M.dst->value << "), "
                    << instrs->instr->u.M.src->value << std::endl;
                break;
            }
            case INST_LW:{
                out << "    lw reg(" << instrs->instr->u.L.dst->value << "), "
                    << instrs->instr->u.L.imm->value << "(reg("
                    << instrs->instr->u.L.src->value << "))" << std::endl;
                break;
            }
            case INST_MFLO:{
                out << "    mflo reg(" << instrs->instr->u.MFLO.dst->value << ")" << std::endl;
                break;
            }
            case INST_MOVE:{
                out << "    move reg(" << instrs->instr->u.M.dst->value << "), reg("
                    << instrs->instr->u.M.src->value << ")" << std::endl;
                break;
            }
            case INST_MUL:{
                out << "    mul reg(" << instrs->instr->u.R.dst->value << "), reg(" 
                    << instrs->instr->u.R.src1->value << "), reg("
                    << instrs->instr->u.R.src2->value << ")" << std::endl;
                break;
            }
            case INST_SUB:{
                out << "    sub reg(" << instrs->instr->u.R.dst->value << "), reg(" 
                    << instrs->instr->u.R.src1->value << "), reg("
                    << instrs->instr->u.R.src2->value << ")" << std::endl;
                break;
            }
            case INST_SW:{
                out << "    sw reg(" << instrs->instr->u.S.src->value << "), "
                    << instrs->instr->u.S.imm->value << "(reg("
                    << instrs->instr->u.S.dst->value << "))" << std::endl;
                break;
            }
            default:{
                std::cout << "Error in print" << std::endl;
            }
        }
        instrs = instrs->next;
    }
}

void initializeRegs() {
    regs[0].name = "$zero";
    regs[0].avaliableLine = -1;
    regs[1].name = "$at";
    regs[1].avaliableLine = -1;
    regs[2].name = "$v0";
    regs[2].avaliableLine = -1;
    regs[3].name = "$v1";
    regs[3].avaliableLine = -1;
    regs[4].name = "$a0";
    regs[4].avaliableLine = -1;
    regs[5].name = "$a1";
    regs[5].avaliableLine = -1;
    regs[6].name = "$a2";
    regs[6].avaliableLine = -1;
    regs[7].name = "$a3";
    regs[7].avaliableLine = -1;
    regs[8].name = "$t0";
    regs[8].avaliableLine = -1;
    regs[9].name = "$t1";
    regs[9].avaliableLine = -1;
    regs[10].name = "$t2";
    regs[10].avaliableLine = -1;
    regs[11].name = "$t3";
    regs[11].avaliableLine = -1;
    regs[12].name = "$t4";
    regs[12].avaliableLine = -1;
    regs[13].name = "$t5";
    regs[13].avaliableLine = -1;
    regs[14].name = "$t6";
    regs[14].avaliableLine = -1;
    regs[15].name = "$t7";
    regs[15].avaliableLine = -1;
    regs[16].name = "$s0";
    regs[16].avaliableLine = -1;
    regs[17].name = "$s1";
    regs[17].avaliableLine = -1;
    regs[18].name = "$s2";
    regs[18].avaliableLine = -1;
    regs[19].name = "$s3";
    regs[19].avaliableLine = -1;
    regs[20].name = "$s4";
    regs[20].avaliableLine = -1;
    regs[21].name = "$s5";
    regs[21].avaliableLine = -1;
    regs[22].name = "$s6";
    regs[22].avaliableLine = -1;
    regs[23].name = "$s7";
    regs[23].avaliableLine = -1;
    regs[24].name = "$t8";
    regs[24].avaliableLine = -1;
    regs[25].name = "$t9";
    regs[25].avaliableLine = -1;
    regs[26].name = "$k0";
    regs[26].avaliableLine = -1;
    regs[27].name = "$k1";
    regs[27].avaliableLine = -1;
    regs[28].name = "$gp";
    regs[28].avaliableLine = -1;
    regs[29].name = "$sp";
    regs[29].avaliableLine = -1;
    regs[30].name = "$fp";
    regs[30].avaliableLine = -1;
    regs[31].name = "$ra";
    regs[31].avaliableLine = -1;
}



