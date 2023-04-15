	CompSt: LC DefList StmtList RC {&& = buildTree(4, NO_LINE, false, "CompSt", NO_VALUE, $1, $2, $3, $4);}
	      ;

 StmtList: Stmt StmtList {$$ = buildTree(2, NO_LINE, false, "StmtList", NO_VALUE, $1, $2);}
  	      | {$$ = nullptr;}
  	      ;

  	 Stmt: Exp SEMI {$$ = buildTree(2, NO_LINE, false, "Stmt", NO_VALUE, $1, $2);}
  	  	  | CompSt {$$ = buildTree(1, NO_LINE, false, "Stmt", NO_VALUE, $1);}
  	  	  | RETURN Exp SEMI {$$ = buildTree(3, NO_LINE, false, "Stmt", NO_VALUE, $1, $2, $3);}
  	  	  | IF LP Exp RP Stmt {$$ = buildTree(5, NO_LINE, false, "Stmt", NO_VALUE, $1, $2, $3, $4, $5);}
  	  	  | IF LP Exp RP Stmt ELSE Stmt {$$ = buildTree(7, NO_LINE, false, "Stmt", NO_VALUE, $1, $2, $3, $4, $5, $6, $7);}
  	  	  | WHILE LP Exp RP Stmt {$$ = buildTree(5, NO_LINE, false, "Stmt", NO_VALUE, $1, $2, $3, $4, $5);}
  	  	  ;

   DefList: Def DefList {$$ = buildTree(2, NO_LINE, false, "DefList", NO_VALUE, $1, $2);}
          | {$$=nullptr}
          ;

       Def: Specifier DecList SEMI {$$ = buildTree(3, NO_LINE, false, "Def", NO_VALUE, $!, $2, $3);}
          ;

   DecList: Dec {$$ = buildTree(1, NO_LINE, false, "DecList", NO_VALUE, $1);}
          | Dec COMMA DecList {$$ = buildTree(3, NO_LINE, false, "DecList", NO_VALUE, $1, $2, $3);}
          ;

       Dec: VarDec {$$ = buildTree(1, NO_LINE, false, "Dec", NO_VALUE, $1);}
          | VarDec ASSIGNOP Exp {$$ = buildTree(3, NO_LINE, false, "Dec", NO_VALUE, $1, $2, $3);}
          ;

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