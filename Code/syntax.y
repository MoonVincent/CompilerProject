Exp:Exp ASSIGNOP Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   |Exp AND Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp OR Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp RELOP Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp PLUS Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp MINUS Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp STAR Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp DIV Exp {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | LP Exp RP {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | MINUS Exp {$$=buildTree(2,NO_LINE,false,"Exp",NO_VALUE,$1,$2);}
   | NOT Exp {$$=buildTree(2,NO_LINE,false,"Exp",NO_VALUE,$1,$2);}
   | ID LP Args RP {$$=buildTree(4,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3,$4);}
   | ID LP RP {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | Exp LB Exp RB {$$=buildTree(4,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3,$4);}
   | Exp DOT ID {$$=buildTree(3,NO_LINE,false,"Exp",NO_VALUE,$1,$2,$3);}
   | ID {$$=buildTree(1,NO_LINE,false,"Exp",NO_VALUE,$1);}
   | INT {$$=buildTree(1,NO_LINE,false,"Exp",NO_VALUE,$1);}
   | FLOAT {$$=buildTree(1,NO_LINE,false,"Exp",NO_VALUE,$1);}
   ;
Args:Exp COMMA Args {$$=buildTree(3,NO_LINE,false,"Args",NO_VALUE,$1,$2,$3);}
   | Exp {$$=buildTree(1,NO_LINE,false,"Args",NO_VALUE,$1);}
   ;