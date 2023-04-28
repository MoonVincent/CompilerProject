#include"global.hpp"
typedef struct Operand_* Operand; 
struct Operand_ { 
	enum { VARIABLE,CONSTANT,ADDRESS,LABEL,FUNCTION,RELOP,READ_ADDRESS,WRITE_ADDRESS} kind; 
	union { 
		int value; 
		char *name;
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