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

void printInterCodes(std::ofstream &out, InterCodeList head)
{
    InterCodeList cur = head->next;
    while(cur!=NULL)
    {
        switch (cur->code->kind)
        {
        case LABEL:
            out << "LABEL ";
            printOperand(out, cur->code->u.oneop.op);
            out << " :";
            break;
        case FUNCTION:
            out << "FUNCTION ";
            printOperand(out, cur->code->u.oneop.op);
            out << " :";
            break;
        case ASSIGN:
            printOperand(out, cur->code->u.assign.left);
            out << " := ";
            printOperand(out, cur->code->u.assign.right);
            break;
        case ADD:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " + ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case SUB:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " - ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case MUL:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " * ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case DIV:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " / ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case GOTO:
            out << "GOTO ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case IF_GOTO:
            out << "IF ";
            printOperand(out, cur->code->u.if_goto.x);
            out << " ";
            printOperand(out, cur->code->u.if_goto.relop);
            out << " ";
            printOperand(out, cur->code->u.if_goto.y);
            out << " GOTO ";
            printOperand(out, cur->code->u.if_goto.t);
            break;
        case RETURN:
            out << "RETURN ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case DEC:
            out << "DEC ";
            printOperand(out, cur->code->u.dec.x);
            out << " ";
            out << cur->code->u.dec.size;
            break;
        case ARG:
            out << "ARG ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case CALL:
            printOperand(out, cur->code->u.assign.left);
            out << " := CALL ";
            printOperand(out, cur->code->u.assign.right);
            break;
        case PARAM:
            out << "PARAM ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case READ:
            out << "READ ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case WRITE:
            out << "WRITE ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        }
        out << "\n";
        cur = cur->next;
    }
}


Operand newOperand(Kind_op kind, std::string val)
{
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = kind;
    switch(kind)
    {
        case OP_CONSTANT:
            op->u.value = atoi(val.c_str());
            break;
        case OP_VARIABLE:
        case OP_ADDRESS: 
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
        case OP_READ_ADDRESS: 
        case OP_WRITE_ADDRESS:
            op->u.name = val;
    }
    return op;
}

int num_temp = 0;
int num_label = 0;
Operand newtemp()
{
    char buf[20];
    sprintf(buf, "t%d", num_temp);
    num_temp++;
    std::string name(buf);
    Operand op = newOperand(OP_VARIABLE,name);
    return op;
}

Operand newlabel()
{
    char buf[20];
    sprintf(buf, "label%d", num_label);
    num_label++;
    std::string name(buf);
    Operand op = newOperand(OP_LABEL, name);
    return op;
}
/*
将op所对应的值赋值为kind和val
*/
void setOperand(Operand op, Kind_op kind, std::string val)
{
    op->kind = kind;
    switch (kind)
    {
    case OP_CONSTANT:
        op->u.value = atoi(val.c_str());
        break;
    case OP_VARIABLE:
    case OP_ADDRESS:
    case OP_LABEL:
    case OP_FUNCTION:
    case OP_RELOP:
    case OP_READ_ADDRESS:
    case OP_WRITE_ADDRESS:
        op->u.name = val;
    }
}
/*
打印一个操作数到out中
*/
void printOperand(std::ofstream &out, Operand op)
{
    switch(op->kind)
    {
        case OP_CONSTANT:
            out << "#" << op->u.value;
            break;
        case OP_VARIABLE:
        case OP_ADDRESS:
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
            out << op->u.name;
            break;
        case OP_READ_ADDRESS:
            out << "&" << op->u.name;
            break;
        case OP_WRITE_ADDRESS:
            out << "*" << op->u.name;
            break;
    }
}

/*
传入一个符号表item,输出该item需要分配的空间大小,以字节为单位
*/
int compute_size(Type item)
{
    if (item == NULL)
            return 0;
    switch(item->kind)
    {
        case INT:
        case FLOAT:
            return 4;
        case ARRAY:
            return item->u.array.elemSize*compute_size(item->u.array.elemType);
        case STRUCTURE:
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

/*
产生中间代码主入口
*/
void Generate(tree root)
{
    if (root == NULL)
        return;
    // Program → ExtDefList
    if (root->children[0]->key == "ExtDefList")
        translate_ExtDefList(root->children[0]);
}

void translate_ExtDefList(tree node)
{
    if(node == NULL)
        return;
    // ExtDefList -> ExtDef ExtDefList
    //             | e
    while(node)
    {
        translate_ExtDef(node->children[0]);
        translate_ExtDefList(node->children[1]);
    }
}

void translate_ExtDef(tree node)
{
    if(node == NULL)
        return;
    // ExtDef → Specifier ExtDecList SEMI
    //          | Specifier SEMI 
    //          | Specifier FunDec CompSt
    if(node->children[1]->key == "FunDec")
    {
        translate_FunDec(node->children[1]);
        translate_CompSt(node->children[2]);
    }
}

void translate_FunDec(tree node)
{
    // to do
}

void translate_CompSt(tree node)
{
    if (node == NULL)
        return;
    // CompSt → LC DefList StmtList RC
    translate_DefList(node->children[1]);
    translate_StmtList(node->children[2]);
}

void translate_DefList(tree node)
{
    if (node == NULL)
        return;
    // DefList → Def DefList
    //           |e
    while(node)
    {
        translate_Def(node->children[0]);
        node = node->children[1];
    }
}

void translate_Def(tree node)
{
    if (node == NULL)
        return;
    // Def → Specifier DecList SEMI
    translate_DecList(node->children[1]);
}

void translate_DecList(tree node)
{
    if (node == NULL)
        return;
    // DecList → Dec
    //          | Dec COMMA DecList
    while(node)
    {
        translate_Dec(node->children[0]);
        if(node->childCnt == 3)
            node = node->children[2];
        else
            break;
    }
}

void translate_Dec(tree node)
{
    if (node == NULL)
        return;
    // Dec → VarDec
    //      | VarDec ASSIGNOP Exp

    if (node->childCnt == 1)
        translate_VarDec(node->children[0], NULL);
    // Dec -> VarDec ASSIGNOP Exp
    else
    {
        Operand t1 = newtemp();
        translate_VarDec(node->children[0], t1);
        Operand t2 = newtemp();
        translate_Exp(node->children[2], t2);
        //to do
        //genInterCode(IR_ASSIGN, t1, t2);
    }
}

void translate_VarDec(tree node,Operand place)
{
    if (node == NULL)
        return;
    // VarDec → ID
    //          | VarDec LB INT RB
    // to do
}
void translate_Exp(tree node, Operand place)
{
    if (node == NULL)
        return;
    // Exp → Exp ASSIGNOP Exp
    // | Exp AND Exp
    // | Exp OR Exp
    // | Exp RELOP Exp
    // | Exp PLUS Exp
    // | Exp MINUS Exp
    // | Exp STAR Exp
    // | Exp DIV Exp
    // | LP Exp RP
    // | MINUS Exp
    // | NOT Exp
    // | ID LP Args RP
    // | ID LP RP
    // | Exp LB Exp RB
    // | Exp DOT ID
    // | ID
    // | INT
    // | FLOAT
    // to do
}
void translate_StmtList(tree node)
{
    if (node == NULL)
        return;
    // StmtList -> Stmt StmtList
    //           | e
    while(node)
    {
        translate_Stmt(node->children[0]);
        node = node->children[1];
    }
}

void translate_Stmt(tree node)
{
    if (node == NULL)
        return;
    // Stmt -> Exp SEMI
    //       | CompSt
    //       | RETURN Exp SEMI
    //       | IF LP Exp RP Stmt
    //       | IF LP Exp RP Stmt ELSE Stmt
    //       | WHILE LP Exp RP Stmt
    //to do
}

void translateCond(tree node, Operand label_true, Operand label_false)
{
    if (node == NULL)
        return;
    // Exp -> Exp AND Exp
    //      | Exp OR Exp
    //      | Exp RELOP Exp
    //      | NOT Exp
    //to do
}

//to do
// void translateArgs(tree node, ArgList argList)
// {
//     if (node == NULL)
//         return;
//     // Args -> Exp COMMA Args
//     //       | Exp
//     // to do
// }