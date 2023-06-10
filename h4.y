%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

extern int yylex(); /* The next token function. */
extern char *yytext; /* The matched token text. */
extern int yyleng;
extern int yyerror(char *);

extern SymTab *table;
extern SymEntry *entry;
%}

%union {
SymTab * SymbolTable;
char * string;
}

%type <string> Id
%type <SymbolTable> Expr
%type <SymbolTable> Term
%type <SymbolTable> Factor

%token SetLit
%token Ident


%%
Prog : StmtSeq {printSymTab();};
StmtSeq : Stmt StmtSeq { };
StmtSeq : { };
Stmt : Id '=' Expr ';' {storeVar($1, $3);};
Expr : Expr '+' Term  {$$ = doUnion($1, $3);};
Expr : Term   {$$ = $1;};
Term : Term '*' Factor    {$$ = doIntersection($1, $3);};
Term : Factor       {$$ = $1;};
Factor : '(' Expr ')'   {$$ = $2;};
Factor : Id     {$$ = getVal($1);};
Factor : SetLit {$$ = makeSet(strdup(yytext)); };
Id : Ident      {$$ = strdup(yytext);};
%%

int yyerror(char *s) {
  writeIndicator(getCurrentColumnNum());
  writeMessage("Illegal Character in YACC");
  return 1;
}
