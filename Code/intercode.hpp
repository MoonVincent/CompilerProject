#include"global.hpp"
typedef enum { VARIABLE,CONSTANT,ADDRESS,LABEL,FUNCTION,RELOP,READ_ADDRESS,WRITE_ADDRESS} Kind_op;
typedef enum { ASSIGN, ADD, SUB, MUL, DIV, LABEL, FUNCTION, PARAM, RETURN, DEC, IF_GOTO, GOTO, ARG, CALL, READ, WRITE} kind_IC; 
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
   kind_IC kind;
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
InterCode newAssign(kind_IC kind, Operand right, Operand left);
InterCode newBinop(kind_IC kind, Operand res, Operand op1, Operand op2);
InterCode newOneop(kind_IC kind, Operand op);
InterCode newIf_goto(kind_IC kind, Operand x, Operand relop, Operand y, Operand t);
InterCode newDec(kind_IC kind, Operand x, int size);
//Operand Functions
Operand newOperand(Kind_op kind,char *val);
void setOperand(Operand op, Kind_op kind, char *val);
void printOperand(std::ofstream &out, Operand op);
