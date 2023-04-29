#pragma once
#include "global.hpp"
typedef enum { OP_VARIABLE,OP_CONSTANT,OP_ADDRESS,OP_LABEL,OP_FUNCTION,OP_RELOP,OP_READ_ADDRESS,OP_WRITE_ADDRESS} Kind_op;
typedef enum { ASSIGN, ADD, SUB, MUL, DIV, LABEL, FUNCTION, PARAM, RETURN, DEC, IF_GOTO, GOTO, ARG, CALL, READ, WRITE} Kind_IC; 
typedef struct Operand_* Operand; 


struct Operand_ {
  Kind_op kind;
  union { 
		int value; 
		std::string name;
	} u; 
}; 

typedef struct InterCode_* InterCode; 
struct InterCode_ 
{ 
   Kind_IC kind;
   union { 
   struct { Operand right, left; } assign; 
   struct { Operand result, op1, op2; } binop; 
   struct { Operand op; } oneop; 
   struct {	Operand	x,relop,y,t; } if_goto;
   struct { Operand x; int size; } dec;
  } u; 
} ;

typedef struct InterCodes* InterCodeList;
struct InterCodes
{ 
  InterCode code; 
  struct InterCodes *prev, *next; 
};

InterCodeList newICList();
void delICList(InterCodeList p);
void add_ICList(InterCodeList p, InterCode q);
InterCode newAssign(Kind_IC kind, Operand right, Operand left);
InterCode newBinop(Kind_IC kind, Operand res, Operand op1, Operand op2);
InterCode newOneop(Kind_IC kind, Operand op);
InterCode newIf_goto(Kind_IC kind, Operand x, Operand relop, Operand y, Operand t);
InterCode newDec(Kind_IC kind, Operand x, int size);
void printInterCodes(std::ofstream &out,InterCodeList head);

//Operand Functions
Operand newOperand(Kind_op kind,std::string val);
void setOperand(Operand op, Kind_op kind, std::string val);
void printOperand(std::ofstream &out, Operand op);

//产生temp和label,newtemp返回name为t0,t1.....的变量,newlabel返回name为label1,label2......的标识
Operand newtemp();
Operand newlabel();

//DEC里面需要计算数组或结构体大小
int compute_size(Type item);

//产生中间代码主入口
void translate_Program(tree root);
void translate_ExtDefList(tree root);
void translate_ExtDef(tree node);
void translate_FunDec(tree node);
void translate_CompSt(tree node);
void translate_DefList(tree node);
void translate_Def(tree node);
void translate_DecList(tree node);
void translate_Dec(tree node);
void translate_VarDec(tree node, Operand place);
void translate_Exp(tree node, Operand place);
void translate_StmtList(tree node);
void translate_Stmt(tree node);
void translate_Cond(tree node, Operand label_true, Operand label_false);

// to do
// void translate_Args(tree node, ArgList argList);
