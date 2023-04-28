#include"intercode.hpp"
#include<stdio.h>

InterCodeList newICList()
{
    InterCodeList p = new InterCodes();
    p->code = nullptr; // head pointer's content is null
    p->prev = p->next = nullptr;
    return p;
}

void delICList(InterCodeList p)
{
    InterCodeList q = p;
    while(p != nullptr)
    {
        p = p->next;
        free(q);
        q = p;
    }
}

void add_ICList(InterCodeList p, InterCode q)
{
    InterCodeList temp = p->next;
    InterCodeList tail = p;
    while(temp != nullptr)
    {
        tail = temp;
        temp = temp->next;
    }
    temp = new InterCodes();
    tail->next = temp;
    temp->code = q;
    temp->prev = tail;
    temp->next = nullptr;
}

InterCode newAssign(Kind_IC kind, Operand right, Operand left)
{
    InterCode temp = new InterCode_();
    switch(kind)
    {
        case ASSIGN:
            temp->kind = ASSIGN;
            temp->u.assign.right = right;
            temp->u.assign.left = left;
            break;
        default: break;
    }
    return temp;
}

InterCode newBinop(Kind_IC kind, Operand res, Operand op1, Operand op2)
{
    InterCode temp = new InterCode_();
    switch(kind)
    {
        case ADD:
            temp->kind = ADD;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        case SUB:
            temp->kind = SUB;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        case MUL:
            temp->kind = MUL;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        case DIV:
            temp->kind = DIV;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        default: break;
    }
    return temp;
}

InterCode newOneop(Kind_IC kind, Operand op)
{
    InterCode temp = new InterCode_();
    switch(kind)
    {
        case LABEL:
            temp->kind = LABEL;
            temp->u.oneop.op = op;
            break;
        case FUNCTION:
            temp->kind = FUNCTION;
            temp->u.oneop.op = op;
            break;
        case PARAM:
            temp->kind = PARAM;
            temp->u.oneop.op = op;
            break;
        case RETURN:
            temp->kind = RETURN;
            temp->u.oneop.op = op;
            break;
        case GOTO:
            temp->kind = GOTO;
            temp->u.oneop.op = op;
            break;
        case ARG:
            temp->kind = ARG;
            temp->u.oneop.op = op;
            break;
        case CALL:
            temp->kind = CALL;
            temp->u.oneop.op = op;
            break;
        case READ:
            temp->kind = READ;
            temp->u.oneop.op = op;
            break;
        case WRITE:
            temp->kind = WRITE;
            temp->u.oneop.op = op;
            break;
        default: break;
    }
    return temp;
}

InterCode newIf_goto(Kind_IC kind, Operand x, Operand relop, Operand y, Operand t)
{
    InterCode temp = new InterCode_();
    switch(kind)
    {
        case IF_GOTO:
            temp->kind = IF_GOTO;
            temp->u.if_goto.x = x;
            temp->u.if_goto.relop = relop;
            temp->u.if_goto.y = y;
            temp->u.if_goto.t = t;
            break;
        default: break;
    }
    return temp;
}

InterCode newDec(Kind_IC kind, Operand x, int size)
{
    InterCode temp = new InterCode_();
    switch(kind)
    {
        case DEC:
            temp->kind = DEC;
            temp->u.dec.x = x;
            temp->u.dec.size = size;
            break;
        default: break;
    }
    return temp;
}

Operand newOperand(Kind_op kind, std::string val)
{
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = kind;
    switch(kind){
    case CONSTANT_OP:
        op->u.value = atoi(val.c_str());
        break;
    case VARIABLE_OP:
    case ADDRESS_OP: 
    case LABEL_OP:
    case FUNCTION_OP:
    case RELOP_OP:
    case READ_ADDRESS_OP: 
    case WRITE_ADDRESS_OP:
        op->u.name = val;
    }
    return op;
}

void setOperand(Operand op, Kind_op kind, std::string val)
{
    op->kind = kind;
    switch (kind)
    {
    case CONSTANT_OP:
        op->u.value = atoi(val.c_str());
        break;
    case VARIABLE_OP:
    case ADDRESS_OP:
    case LABEL_OP:
    case FUNCTION_OP:
    case RELOP_OP:
    case READ_ADDRESS_OP:
    case WRITE_ADDRESS_OP:
        op->u.name = val;
    }
}

void printOperand(std::ofstream &out, Operand op)
{
    switch(op->kind)
    {
        case CONSTANT_OP:
            out << "#" << op->u.value;
            break;
        case VARIABLE_OP:
        case ADDRESS_OP:
        case LABEL_OP:
        case FUNCTION_OP:
        case RELOP_OP:
            out << op->u.name;
            break;
        case READ_ADDRESS_OP:
            out << "&" << op->u.name;
            break;
        case WRITE_ADDRESS_OP:
            out << "*" << op->u.name;
            break;
    }
}