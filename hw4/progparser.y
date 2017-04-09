// -- PREAMBLE ------------------------------------------
%{
#include <iostream>
using namespace std;

  // Things from Flex that Bison needs to know
extern int yylex();
extern int line_num;
extern char* yytext;

  // Prototype for Bison's error message function
int yyerror(const char *p);
%}

//-- TOKEN DEFINITIONS --
// what tokens to expect from Flex
%token T_IDENT
%token T_INTEGER
%token T_DECIMAL
%token T_STRING
%token T_RELATION
%token T_ADDOPERATOR
%token T_MULOPERATOR

%token K_BANG
%token K_ASSIGN
%token K_NEG
%token K_LPAREN
%token K_RPAREN
%token K_PRINT
%token K_RET
%token K_IF
%token K_FI
%token K_ELSE
%token K_LOOP
%token K_POOL
%token K_FUNC
%token K_BEGIN
%token K_END


%%   //-- GRAMMAR RULES ------------------------------------
/* NOTE: Bison likes the start symbol to be the first rule */
statementSeq : statement
               { cout << "RULE: StatementSeq ::= Statement" << endl; }
             | statement statementSeq
           { cout << "RULE: StatementSeq ::= Statement StatementSeq" << endl; }
             ;

Expression  : /* empty */                                       { cout << "RULE: Expression ::= empty" << endl; }
            | SimpleExpression                                  { cout << "RULE: Expression ::= SimpleExpression" << endl; }
            | SimpleExpression T_RELATION SimpleExpression      { cout << "RULE: Expression ::= SimpleExpression T_RELATION SimpleExpression" << endl;}
            ;
            
SimpleExpression    :  /* empty */
statement : /* empty */     { cout << "RULE: Statement ::= empty" << endl; }
          | assignment      { cout << "RULE: Statement ::= Assignment" << endl; }
          | PrintStatement  { cout << "RULE: Statement ::= PrintStatement" << endl; }
          ;

assignment : T_IDENT K_ASSIGN T_DECIMAL K_BANG
           { cout << "RULE: Assignment ::= ident := decimal ! " << endl; }

PrintStatement : K_PRINT K_LPAREN T_INTEGER K_RPAREN K_BANG
               { cout << "RULE: PrintStatement ::= PRINT ( integer ) !" << endl; }

RetStatement   : K_RET T_IDENT K_BANG
               { cout << "RULE: RetStatement ::= RET identifier !" << endl; }
               
IfStatement    : K_IF K_LPAREN Expression

%% //-- EPILOGUE ---------------------------------------------
// Bison error function 
int yyerror(const char *p)
{
  cout << "ERROR: In line " << line_num << " with token \'"
       << yytext << "\'" << endl;
}

int main()
{
  int failcode;
  cout << "Hello Flex + Bison" << endl;
  failcode = yyparse();

  if (failcode)
    cout << "INVALID!" << endl;
  else
    cout << "CORRECT" << endl;
  return 0;
}