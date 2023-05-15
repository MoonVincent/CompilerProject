#pragma once
#include <string>
#include "type.hpp"
#include "syntaxNode.hpp"
typedef struct Operand_* Operand; 
typedef enum { OP_VARIABLE,OP_STRING,OP_CONSTANT,OP_ADDRESS,OP_LABEL,OP_FUNCTION,OP_CALL,OP_RELOP,OP_READ_ADDRESS,OP_WRITE_ADDRESS} Kind_op;
typedef enum { IC_ASSIGN, IC_ADD, IC_SUB, IC_MUL, IC_DIV, IC_LABEL, IC_FUNCTION, IC_PARAM, IC_RETURN, IC_DEC, IC_IF_GOTO, IC_GOTO, IC_ARG, IC_CALL, IC_READ, IC_WRITE} Kind_IC; 



struct Operand_ {
  Kind_op kind;
  int loc;
  std::string name;
};

// translate_Args需要用到的参数链表
typedef struct Arg_ *Arg;
struct Arg_
{
  Operand op;
  Arg next;
};
typedef struct Arglist_ *Arglist;
struct Arglist_
{
  Arg head;
  Arg cur;
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


//Arg Functions
Arglist newArglist();
Arg newArg();
void addArg(Arglist argList, Arg arg);

//产生temp和label,newtemp返回name为t0,t1.....的变量,newlabel返回name为label1,label2......的标识
Operand newtemp();
Operand newlabel();

//DEC里面需要计算数组或结构体大小
int compute_size(Type item);

//产生中间代码主入口
void translate_Program(tree root);
void translate_ExtDefList(tree root);
void translate_ExtDef(tree node);
void translate_FunDec(tree node, std::vector<std::string>& valueRecord);
void translate_VarList(tree node, std::vector<std::string>& valueRecord);
void translate_ParamDec(tree node, std::vector<std::string>& valueRecord);
void translate_CompSt(tree node, std::vector<std::string>& valueRecord);
void translate_DefList(tree node, std::vector<std::string>& valueRecord);
void translate_Def(tree node, std::vector<std::string>& valueRecord);
void translate_DecList(tree node, std::vector<std::string>& valueRecord);
void translate_Dec(tree node, std::vector<std::string>& valueRecord);
void translate_VarDec(tree node, Operand place, std::vector<std::string>& valueRecord);
void translate_Exp(tree node, Operand place);
void translate_StmtList(tree node);
void translate_Stmt(tree node);
void translate_Cond(tree node, Operand label_true, Operand label_false);
void translate_Args(tree node, Arglist argList);
void translate_ExtDecList(tree node, std::vector<std::string>& valueRecord);
Operand getValueItem(std::string key);
void deleteValueItem(std::string key);
bool insertValueItem(std::string key, Operand place);
std::string getDimensionItem(std::string key);
void deleteDimensionItem(std::string key);
bool insertDimensionItem(std::string key, std::string size);

extern InterCodeList head;