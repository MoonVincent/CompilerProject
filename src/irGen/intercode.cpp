#include"../include/intercode.hpp"
#include "../include/global.hpp"
#include<stdio.h>
#include <iostream>
InterCodeList head = newICList();

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
        case IC_ASSIGN:
            temp->kind = IC_ASSIGN;
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
        case IC_ADD:
            temp->kind = IC_ADD;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        case IC_SUB:
            temp->kind = IC_SUB;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        case IC_MUL:
            temp->kind = IC_MUL;
            temp->u.binop.result = res;
            temp->u.binop.op1 = op1;
            temp->u.binop.op2 = op2;
            break;
        case IC_DIV:
            temp->kind = IC_DIV;
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
        case IC_LABEL:
            temp->kind = IC_LABEL;
            temp->u.oneop.op = op;
            break;
        case IC_FUNCTION:
            temp->kind = IC_FUNCTION;
            temp->u.oneop.op = op;
            break;
        case IC_PARAM:
            temp->kind = IC_PARAM;
            temp->u.oneop.op = op;
            break;
        case IC_RETURN:
            temp->kind = IC_RETURN;
            temp->u.oneop.op = op;
            break;
        case IC_GOTO:
            temp->kind = IC_GOTO;
            temp->u.oneop.op = op;
            break;
        case IC_ARG:
            temp->kind = IC_ARG;
            temp->u.oneop.op = op;
            break;
        case IC_CALL:
            temp->kind = IC_CALL;
            temp->u.oneop.op = op;
            break;
        case IC_READ:
            temp->kind = IC_READ;
            temp->u.oneop.op = op;
            break;
        case IC_WRITE:
            temp->kind = IC_WRITE;
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
        case IC_IF_GOTO:
            temp->kind = IC_IF_GOTO;
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
        case IC_DEC:
            temp->kind = IC_DEC;
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
    while(cur)
    {
        switch (cur->code->kind)
        {
        case IC_LABEL:
            out << "LABEL ";
            printOperand(out, cur->code->u.oneop.op);
            out << " :";
            break;
        case IC_FUNCTION:
            out << "FUNCTION ";
            printOperand(out, cur->code->u.oneop.op);
            out << " :";
            break;
        case IC_ASSIGN:
            printOperand(out, cur->code->u.assign.left);
            out << " := ";
            printOperand(out, cur->code->u.assign.right);
            break;
        case IC_ADD:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " + ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case IC_SUB:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " - ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case IC_MUL:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " * ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case IC_DIV:
            printOperand(out, cur->code->u.binop.result);
            out << " := ";
            printOperand(out, cur->code->u.binop.op1);
            out << " / ";
            printOperand(out, cur->code->u.binop.op2);
            break;
        case IC_GOTO:
            out << "GOTO ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case IC_IF_GOTO:
            out << "IF ";
            printOperand(out, cur->code->u.if_goto.x);
            out << " ";
            printOperand(out, cur->code->u.if_goto.relop);
            out << " ";
            printOperand(out, cur->code->u.if_goto.y);
            out << " GOTO ";
            printOperand(out, cur->code->u.if_goto.t);
            break;
        case IC_RETURN:
            out << "RETURN ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case IC_DEC:
            out << "DEC ";
            printOperand(out, cur->code->u.dec.x);
            out << " ";
            out << cur->code->u.dec.size;
            break;
        case IC_ARG:
            out << "ARG ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case IC_CALL:
            printOperand(out, cur->code->u.assign.right);
            break;
        case IC_PARAM:
            out << "PARAM ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case IC_READ:
            out << "READ ";
            printOperand(out, cur->code->u.oneop.op);
            break;
        case IC_WRITE:
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
    Operand op = new Operand_();
    op->kind = kind;
    op->loc = 1;
    switch(kind)
    {
        case OP_CONSTANT:
        case OP_VARIABLE:
        case OP_ADDRESS: 
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
        case OP_READ_ADDRESS: 
        case OP_WRITE_ADDRESS:
        case OP_CALL:
            op->name = val;
    }
    return op;
}

int num_temp = 0;
int num_label = 0;
int num_value = 0;
Operand newtemp()
{
    std::string name = "t" + std::to_string(num_temp);
    ++num_temp;
    Operand op = newOperand(OP_VARIABLE, name);
    return op;
}

Operand newlabel()
{
    std::string name = "label" + std::to_string(num_label);
    ++num_label;
    Operand op = newOperand(OP_LABEL, name);
    return op;
}

Operand newvalue()
{
    std::string name = "v" + std::to_string(num_value);
    ++num_value;
    Operand op = newOperand(OP_VARIABLE, name);
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
    case OP_VARIABLE:
    case OP_ADDRESS:
    case OP_LABEL:
    case OP_FUNCTION:
    case OP_RELOP:
    case OP_READ_ADDRESS:
    case OP_WRITE_ADDRESS:
        op->name = val;
    }
}
/*
打印一个操作数到out中
*/
void printOperand(std::ofstream &out, Operand op)
{
    if(!op)
        return;
    switch(op->kind)
    {
        case OP_CONSTANT:
            out << "#" << op->name;
            break;
        case OP_CALL:
            out << "CALL "<<op->name;
            break;
        case OP_VARIABLE:
        case OP_ADDRESS:
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
            out << op->name;
            break;
        case OP_READ_ADDRESS:
            out << "&" << op->name;
            break;
        case OP_WRITE_ADDRESS:
            out << "*" << op->name;
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
    case INT_SEMA:
    case FLOAT_SEMA:
            return 4;
    case ARRAY_SEMA:
            return item->u.array.elemSize*compute_size(item->u.array.elemType);
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

/*
产生中间代码主入口
*/
void translate_Program(tree root)
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
        node = node->children[1];
    }
}

void translate_ExtDef(tree node)
{
    if(node == NULL)
        return;
    // ExtDef → Specifier ExtDecList SEMI
    //          | Specifier SEMI 
    //          | Specifier FunDec CompSt
    if (node->children[1]->key == "FunDec") {
        translate_FunDec(node->children[1]);
        translate_CompSt(node->children[2]);
    } else if (node->children[1]->key == "ExtDecList") {
        translate_ExtDecList(node->children[1]);
    }
}

void translate_ExtDecList(tree node) {
    if (node == nullptr) {
        return ;
    }
    //ExtDecList -> VarDec
    //           -> VarDec COMMA ExtDecList
    Operand place = newvalue();
    translate_VarDec(node->children[0], place);
    if (node->childCnt == 3) {
        translate_ExtDecList(node->children[2]);
    }
}

void translate_FunDec(tree node)
{
    if (node == NULL)
        return;
    // to do
    // FunDec -> ID LP VarList RP
    //         | ID LP RP
    InterCode x =  newOneop(IC_FUNCTION,newOperand(OP_FUNCTION,node->children[0]->value));
    add_ICList(head,x);
    if(node->childCnt == 4)
        translate_VarList(node->children[2]);
}

void translate_VarList(tree node)
{
    if (node == NULL)
        return;
    // VarList → ParamDec COMMA VarList
    //          | ParamDec
    translate_ParamDec(node->children[0]);
    if(node->childCnt == 3)
        translate_VarList(node->children[2]);
}

void translate_ParamDec(tree node)
{
    if (node == NULL)
        return;
    // ParamDec → Specifier VarDec
    // VarDec → ID
    //          | VarDec LB INT RB
    tree temp = node->children[1];
    //直到找到ID
    while(temp->childCnt != 1){
        temp = temp->children[0];
    }
    Operand param = newvalue();
    insertValueItem(temp->children[0]->value, param);
    InterCode x = newOneop(IC_PARAM, param);
    add_ICList(head,x);
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

    if (node->childCnt == 1){
        Operand v1 = newvalue();
        translate_VarDec(node->children[0], v1);
    }
    // Dec -> VarDec ASSIGNOP Exp
    else
    {
        tree temp = node;
        while (temp->childCnt != 1) {
            temp = temp->children[0];
        }
        Operand v1 = newvalue();
        translate_VarDec(node->children[0], v1);
        Operand t2 = newtemp();
        translate_Exp(node->children[2], t2);
        //to do
        InterCode x = newAssign(IC_ASSIGN,t2,v1);
        add_ICList(head,x);
    }
}

void translate_VarDec(tree node,Operand place)
{
    if (node == NULL)
        return;
    // VarDec → ID
    //          | VarDec LB INT RB
    if (node->childCnt == 4) {
            int size = 1;
        while(node->childCnt == 4) {
            size = size * std::stoi(node->children[2]->value);
            node = node->children[0];
        }
        size = size * 8;
        InterCode x = newDec(IC_DEC, place, size);
        add_ICList(head, x);
    }

    insertValueItem(node->children[0]->value, place);


}

void translate_Exp(tree node, Operand place)
{
    if (node == NULL)
        return;
    if(node->childCnt == 4)
    {
        //Exp → ID LP Args RP
        if(node->children[0]->key == "ID")
        {
            Arglist list = newArglist();
            translate_Args(node->children[2], list);
            if(node->children[0]->value == "write")
            {
                InterCode x = newOneop(IC_WRITE, list->head->op);
                add_ICList(head, x);
                Operand zero = newOperand(OP_CONSTANT,"0");

                if(place)
                {
                    x = newAssign(IC_ASSIGN, zero, place);
                    add_ICList(head, x);
                }
                return ;
            }
            Arg p = list->head;
            while(p != nullptr)
            {
                InterCode x = newOneop(IC_ARG, p->op);
                add_ICList(head, x);
                p = p->next;
            }
            Operand id = newOperand(OP_CALL, node->children[0]->value);
            InterCode x;
            if (place)
                x = newAssign(IC_ASSIGN, id, place);
            else
                x = newOneop(IC_CALL,id);
            add_ICList(head, x);
            return;
        }
        // | Exp LB Exp RB
        else{
            Operand t1 = newtemp();
            Operand t2 = newtemp();
            translate_Exp(node->children[2], t1);
            Operand tmp = newtemp();
            InterCode x = newAssign(IC_ASSIGN, newOperand(OP_CONSTANT, "8"), tmp);
            add_ICList(head, x);
            x = newBinop(IC_MUL, t2, t1, tmp);
            add_ICList(head, x);

            Operand t3 = newtemp();
            translate_Exp(node->children[0], t3);  
            if(node->children[0]->childCnt==1)
            {

                if(place->loc == 0)
                {
                    Operand new_place = newOperand(OP_VARIABLE, place->name);
                    add_ICList(head, newBinop(IC_ADD, new_place, t3, t2));
                    place->kind = OP_WRITE_ADDRESS;
                }
                else
                {
                    Operand new_place = newOperand(OP_WRITE_ADDRESS, place->name);
                    add_ICList(head, newBinop(IC_ADD, place, t3, t2));
                    add_ICList(head, newAssign(IC_ASSIGN, new_place, place));
                }
            }
            else
            {
                x = newBinop(IC_ADD, place, t3, t2);
                add_ICList(head, x);
            }
        }
    }

    // | Exp DOT ID

    else if(node->childCnt == 3)
    {
        // | ID LP RP
        if(node->children[0]->key == "ID")
        {
            if(node->children[0]->value == "read")
            {
                InterCode x = newOneop(IC_READ, place);
                add_ICList(head, x);
                return;
            }
            else
            {
                Operand id = newOperand(OP_CALL,node->children[0]->value);
                InterCode x = newAssign(IC_ASSIGN, id, place);
                add_ICList(head, x);
            }
        }
        // | LP Exp RP
        if(node->children[0]->key == "LP")
        {
            translate_Exp(node->children[1], place);
        }
        // | Exp ASSIGNOP Exp
        if(node->children[1]->key == "ASSIGNOP")
        {
            Operand t1 = newtemp();
            translate_Exp(node->children[2], t1);
            if (node->children[0]->children[0]->key == "ID")
            {
                Operand v = getValueItem(node->children[0]->children[0]->value);
                add_ICList(head,newAssign(IC_ASSIGN,t1,v));

                if(place)
                    add_ICList(head, newAssign(IC_ASSIGN, v, place));
            }
            else
            {
                Operand t2 = newtemp();
                t2->loc = 0;
                translate_Exp(node->children[0],t2);
                add_ICList(head,newAssign(IC_ASSIGN, t1, t2));
                if(place)
                    add_ICList(head, newAssign(IC_ASSIGN, t2, place));
            }
        }
        // | Exp AND Exp
        // | Exp OR Exp
        // | Exp RELOP Exp
        if(node->children[1]->key == "AND" || node->children[1]->key == "OR" || node->children[1]->key == "RELOP")
        {
            Operand label1 = newlabel();
            Operand label2 = newlabel();
            Operand constant = newOperand(OP_CONSTANT,"0");
            InterCode insert = newAssign(IC_ASSIGN, constant, place);
            add_ICList(head, insert);

            translate_Cond(node, label1, label2);

            InterCode p = newOneop(IC_LABEL, label1);
            add_ICList(head, p);

            Operand one = newOperand(OP_CONSTANT,"1");
            InterCode q = newAssign(IC_ASSIGN, one, place);
            add_ICList(head, q);

            InterCode two = newOneop(IC_LABEL, label2);
            add_ICList(head, two);
        }
        // | Exp PLUS Exp
        if(node->children[1]->key == "PLUS")
        {
            Operand t1 = newtemp();
            Operand t2 = newtemp();
            translate_Exp(node->children[0], t1);
            translate_Exp(node->children[2], t2);
            InterCode insert = newBinop(IC_ADD, place, t1, t2);
            add_ICList(head, insert);
        }
        // | Exp MINUS Exp
        if(node->children[1]->key == "MINUS")
        {
            Operand t1 = newtemp();
            Operand t2 = newtemp();
            translate_Exp(node->children[0], t1);
            translate_Exp(node->children[2], t2);
            InterCode insert = newBinop(IC_SUB, place, t1, t2);
            add_ICList(head, insert);
        }
        // | Exp STAR Exp
        if(node->children[1]->key == "STAR")
        {
            Operand t1 = newtemp();
            Operand t2 = newtemp();
            translate_Exp(node->children[0], t1);
            translate_Exp(node->children[2], t2);
            InterCode insert = newBinop(IC_MUL, place, t1, t2);
            add_ICList(head, insert);
        }
        // | Exp DIV Exp
        if(node->children[1]->key == "DIV")
        {
            Operand t1 = newtemp();
            Operand t2 = newtemp();
            translate_Exp(node->children[0], t1);
            translate_Exp(node->children[2], t2);
            InterCode insert = newBinop(IC_DIV, place, t1, t2);
            add_ICList(head, insert);
        }
    }
    else if(node->childCnt == 2)
    {
        // | MINUS Exp
        if(node->children[0]->key == "MINUS")
        {
            Operand t1 = newtemp();
            translate_Exp(node->children[1], t1);
            Operand zero =  newOperand(OP_CONSTANT,"0");
            InterCode x = newBinop(IC_SUB, place, zero, t1);
            add_ICList(head, x);
        }
        // | NOT Exp
        if(node->children[0]->key == "NOT")
        {
            Operand label1 = newlabel();
            Operand label2 = newlabel();
            Operand constant = newOperand(OP_CONSTANT,"0");
            InterCode insert = newAssign(IC_ASSIGN, constant, place);
            add_ICList(head, insert);

            translate_Cond(node, label1, label2);

            InterCode p = newOneop(IC_LABEL, label1);
            add_ICList(head, p);

            Operand one = newOperand(OP_CONSTANT,"1");
            InterCode q = newAssign(IC_ASSIGN, one, place);
            add_ICList(head, q);

            InterCode two = newOneop(IC_LABEL, label2);
            add_ICList(head, two);
        }
    }
    else{
        // | ID
        if(node->children[0]->key == "ID")
        {
            std::string value = node->children[0]->value;
            Operand val = getValueItem(value);
            InterCode x = newAssign(IC_ASSIGN, val, place);
            add_ICList(head, x);
        }
        // | INT
        else if(node->children[0]->key == "INT")
        {
            std::string value = node->children[0]->value;
            Operand val = newOperand(OP_CONSTANT, value);
            InterCode x = newAssign(IC_ASSIGN, val, place);
            add_ICList(head, x);
        }
        // | FLOAT
        else{
            std::string value = node->children[0]->value;
            Operand val = newOperand(OP_CONSTANT, value);
            InterCode x = newAssign(IC_ASSIGN, val, place);
            add_ICList(head, x);
        }
    }
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
    if(node->children[0]->key == "Exp")
    {
        translate_Exp(node->children[0], nullptr);
    }
    //       | CompSt
    if(node->children[0]->key == "CompSt")
    {
        translate_CompSt(node->children[0]);
    }
    //       | RETURN Exp SEMI
    if(node->children[0]->key == "RETURN")
    {
        Operand t1 = newtemp();
        translate_Exp(node->children[1], t1);
        InterCode x = newOneop(IC_RETURN, t1);
        add_ICList(head, x);
    }
    if(node->children[0]->key == "IF")
    {
        //   | IF LP Exp RP Stmt ELSE Stmt
        if(node->childCnt > 5)
        {
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
        else{
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
    if(node->children[0]->key == "WHILE")
    {
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

void translate_Cond(tree node, Operand label_true, Operand label_false)
{
    if (node == NULL)
        return;
    // Exp -> Exp AND Exp
    //      | Exp OR Exp
    //      | Exp RELOP Exp
    //      | NOT Exp
    //to do

    // Exp -> Exp RELOP Exp
    if(node->children[1]->key == "RELOP")
    {
        Operand t1,t2;
        t1 = newtemp();
        translate_Exp(node->children[0], t1);
        t2 = newtemp();
        translate_Exp(node->children[2], t2);
        Operand relop = newOperand(OP_RELOP,node->children[1]->value);

        add_ICList(head, newIf_goto(IC_IF_GOTO, t1, relop, t2, label_true));
        add_ICList(head, newOneop(IC_GOTO,label_false));
    }
    // Exp -> NOT Exp
    else if(node->children[0]->key == "NOT")
        translate_Cond(node->children[1],label_false,label_true);
    // Exp -> Exp AND Exp
    else if (node->children[1]->key == "AND")
    {
        Operand label1 = newlabel();
        translate_Cond(node->children[0],label1,label_false);
        add_ICList(head,newOneop(IC_LABEL,label1));
        translate_Cond(node->children[2],label_true,label_false);
    }

    // Exp ->Exp OR Exp
    else if (node->children[1]->key == "OR")
    {
        Operand label1 = newlabel();
        translate_Cond(node->children[0], label_true, label1);
        add_ICList(head, newOneop(IC_LABEL, label1));
        translate_Cond(node->children[2], label_true, label_false);
    }

    //(other cases)
    else
    {
        Operand t1 = newtemp();
        translate_Exp(node,t1);
        add_ICList(head,newIf_goto(IC_IF_GOTO,t1,newOperand(OP_RELOP,"!="),newOperand(OP_CONSTANT,"0"),label_true));
        add_ICList(head,newOneop(IC_GOTO,label_false));
    }
}


Arglist newArglist()
{
    Arglist head = new Arglist_();
    head->head = NULL;
    head->cur = NULL;
    return head;
}

Arg newArg(Operand op)
{
    Arg temp = new Arg_();
    temp->op = op;
    temp->next = NULL;
    return temp;
}

void addArg(Arglist argList, Arg arg)
{
    if (argList->head == NULL)
    {
        argList->head = arg;
        argList->cur = arg;
    }
    else
    {
        argList->head = arg;
        argList->head->next = argList->cur;
        argList->cur = arg;
    }
}

void translate_Args(tree node, Arglist argList)
{
    if (node == NULL)
        return;
    // Args -> Exp COMMA Args
    //       | Exp

    // Args -> Exp
    Operand t1 = newtemp();
    translate_Exp(node->children[0], t1);
    Arg temp = newArg(t1);
    addArg(argList, temp);

    // Args -> Exp COMMA Args
    if (node->childCnt == 3)
    {
        translate_Args(node->children[2], argList);
    }
}

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