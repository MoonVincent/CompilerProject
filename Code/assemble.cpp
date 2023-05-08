#include "assemble.hpp"
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
    ret->instr->u.M.src = new instrItem_(REG, srcName);
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

void selectInstr(InterCodeList interCode){
    instrList = new instrSelectedList_();
    interCode = interCode->next;
    while (interCode != nullptr) {
        switch (interCode->code->kind)
        {
        case IC_ASSIGN:{
            if (interCode->code->u.assign.right->kind == OP_CONSTANT) {

            } else {

            }
            break;
        }
        case IC_ADD:
            break;
        case IC_ARG:
            break;       
        case IC_CALL:
            break;
        case IC_DEC:
            break;
        case IC_DIV:
            break;
        case IC_FUNCTION:
            break;
        case IC_GOTO:
            break;
        case IC_IF_GOTO:
            break;
        case IC_LABEL:
            break;
        case IC_MUL:
            break;
        case IC_PARAM:
            break;
        
        default:
            break;
        }
    }
}

