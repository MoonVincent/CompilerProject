#include "global.hpp"
typedef enum { VARIABLE_OP,CONSTANT_OP,ADDRESS_OP,LABEL_OP,FUNCTION_OP,RELOP_OP,READ_ADDRESS_OP,WRITE_ADDRESS_OP} Kind_op;
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
