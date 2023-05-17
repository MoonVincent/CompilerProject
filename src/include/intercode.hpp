#pragma once
#include <string>
#include "type.hpp"
#include "syntaxNode.hpp"
typedef enum { OP_VARIABLE,OP_V_STRING,OP_STRING,OP_CONSTANT,OP_LABEL,OP_FUNCTION,OP_CALL,OP_RELOP,OP_READ_ADDRESS,OP_WRITE_ADDRESS, OP_WRITE_ADDRESS_BYTE} Kind_op;
typedef enum { IC_ASSIGN, IC_ADD, IC_SUB, IC_MUL, IC_DIV, IC_LABEL, IC_FUNCTION, IC_PARAM, IC_RETURN, IC_DEC, IC_IF_GOTO, IC_GOTO, IC_ARG, IC_CALL, IC_READ, IC_WRITE} Kind_IC;

//操作数相关数据结构
typedef struct Operand_ *Operand;
struct Operand_ {
  Kind_op kind;//操作数类型
  int loc;//1表示数组在赋值语句右值,0表示左值
  std::string name;//操作数标识符
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

//单条中间代码相关数据结构
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

//中间代码双向链表
typedef struct InterCodes* InterCodeList;
struct InterCodes
{ 
  InterCode code; 
  struct InterCodes *prev, *next; 
};

//中间代码相关函数
InterCodeList newICList();
void add_ICList(InterCodeList p, InterCode q);
InterCode newAssign(Kind_IC kind, Operand right, Operand left);
InterCode newBinop(Kind_IC kind, Operand res, Operand op1, Operand op2);
InterCode newOneop(Kind_IC kind, Operand op);
InterCode newIf_goto(Kind_IC kind, Operand x, Operand relop, Operand y, Operand t);
InterCode newDec(Kind_IC kind, Operand x, int size);
void printInterCodes(std::ofstream &out,InterCodeList head);

//操作数相关函数
Operand newOperand(Kind_op kind,std::string val);
void printOperand(std::ofstream &out, Operand op);


//参数列表相关函数
Arglist newArglist();
Arg newArg(Operand op);
void addArg(Arglist argList, Arg arg);

//t0,label0,v0等临时变量、label、value产生函数
Operand newtemp();
Operand newlabel();
Operand newvalue();

// 符号表相关函数
Operand getValueItem(std::string key);
void deleteValueItem(std::string key);
bool insertValueItem(std::string key, Operand place);
std::string getDimensionItem(std::string key);
void deleteDimensionItem(std::string key);
bool insertDimensionItem(std::string key, std::string size);

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

extern InterCodeList head;