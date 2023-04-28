#include"global.hpp"
typedef enum { VARIABLE,CONSTANT,ADDRESS,LABEL,FUNCTION,RELOP,READ_ADDRESS,WRITE_ADDRESS} Kind_op;
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
   enum { ASSIGN, ADD, SUB, MUL,DIV,LABEL,FUNCTION,PARAM,RETURN,DEC,IF_GOTO,GOTO,ARG,CALL,READ,WRITE} kind; 
   union { 
   struct { Operand right, left; } assign; 
   struct { Operand result, op1, op2; } binop; 
   struct { Operand op; } oneop; 
   struct {	Operand	x,relop,y,t; } if_goto;
   struct { Operand x; int size; } dec;
  } u; 
} ;

struct InterCodes { InterCode code; struct InterCodes *prev, *next; };


//Operand Functions
Operand newOperand(Kind_op kind,char *val);
void setOperand(Operand op, Kind_op kind, char *val);
void printOperand(std::ofstream &out, Operand op);
