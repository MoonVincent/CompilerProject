#include"intercode.hpp"

Operand newOperand(Kind_op kind, std::string val)
{
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = kind;
    switch(kind){
    case CONSTANT:
        op->u.value = atoi(val.c_str());
        break;
    case VARIABLE:
    case ADDRESS: 
    case LABEL:
    case FUNCTION:
    case RELOP:
    case READ_ADDRESS: 
    case WRITE_ADDRESS:
        op->u.name = val;
    }
    return op;
}

void setOperand(Operand op, Kind_op kind, std::string val)
{
    op->kind = kind;
    switch (kind)
    {
    case CONSTANT:
        op->u.value = atoi(val.c_str());
        break;
    case VARIABLE:
    case ADDRESS:
    case LABEL:
    case FUNCTION:
    case RELOP:
    case READ_ADDRESS:
    case WRITE_ADDRESS:
        op->u.name = val;
    }
}

void printOperand(std::ofstream &out, Operand op)
{
    switch(op->kind)
    {
        case CONSTANT:
            out << "#" << op->u.value;
            break;
        case VARIABLE:
        case ADDRESS:
        case LABEL:
        case FUNCTION:
        case RELOP:
            out << op->u.name;
            break;
        case READ_ADDRESS:
            out << "&" << op->u.name;
            break;
        case WRITE_ADDRESS:
            out << "*" << op->u.name;
            break;
    }
}