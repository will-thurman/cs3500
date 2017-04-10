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
%token K_COMMA


%%   //-- GRAMMAR RULES ------------------------------------
/* NOTE: Bison likes the start symbol to be the first rule */
FunctionSeq  : /* empty */                { cout << "RULE: FunctionSeq ::= empty" << endl; }
             | FunctionDec                { cout << "RULE: FunctionSeq ::= FunctionDec" << endl; }
             | FunctionDec FunctionSeq    { cout << "RULE: FunctionSeq ::= FunctionDec FunctionSeq" << endl; }
             ;
             
FunctionDec  : K_FUNC T_IDENT K_LPAREN K_RPAREN K_BEGIN StatementSeq K_END            { cout << "RULE: FunctionDec ::= FUNC identifier ( ) BEGIN StatementSeq END" << endl; }
             | K_FUNC T_IDENT K_LPAREN ParamSeq K_RPAREN K_BEGIN StatementSeq K_END   { cout << "RULE: FunctionDec ::= FUNC identifier ( ParamSeq ) BEGIN StatementSeq END" << endl; }
             
ParamSeq     : /* empty */        { cout << "RULE: ParamSeq ::= empty" << endl; }
             | T_IDENT            { cout << "RULE: ParamSeq ::= identifier" << endl; }
             | T_IDENT K_COMMA ParamSeq   { cout << "RULE: ParamSeq ::= identifier , ParamSeq" << endl;}
             ;
             
StatementSeq : statement
               { cout << "RULE: StatementSeq ::= Statement" << endl; }
             | statement StatementSeq
           { cout << "RULE: StatementSeq ::= Statement StatementSeq" << endl; }
             ;

Expression  : /* empty */                                   { cout << "RULE: Expression ::= empty" << endl; }
            | SimpleExpression                              { cout << "RULE: Expression ::= SimpleExpression" << endl; }
            | SimpleExpression T_RELATION Expression        { cout << "RULE: Expression ::= SimpleExpression T_RELATION SimpleExpression" << endl;}
            ;
            
SimpleExpression    :  /* empty */                          { cout << "RULE: SimpleExpression ::= empty" << endl; }
                    | Term                                  { cout << "RULE: SimpleExpression ::= Term" << endl; }
                    | Term T_ADDOPERATOR SimpleExpression   { cout << "RULE: SimpleExpression ::= Term AddOperator SimpleExpression" << endl; }
                    ;
                    
Term                : /* empty */                 { cout << "RULE: Term ::= empty" << endl; }
                    | Factor                      { cout << "RULE: Term ::= Factor" << endl; }
                    | Factor T_MULOPERATOR Term   { cout << "RULE: Term ::= Factor MulOperator Term" << endl; }
                    ;
                    
Factor              : /* empty */                   { cout << "RULE: Factor ::= empty" << endl; }
                    | T_INTEGER                     { cout << "RULE: Factor ::= integer" << endl; }
                    | T_DECIMAL                     { cout << "RULE: Factor ::= decimal" << endl; }
                    | T_STRING                      { cout << "RULE: Factor ::= string" << endl; }
                    | T_IDENT                       { cout << "RULE: Factor ::= identifier" << endl; }
                    | K_LPAREN Expression K_RPAREN  { cout << "RULE: Factor ::= ( Expression )" << endl; }
                    | K_NEG Factor                  { cout << "RULE: Factor ::= ~ Factor" << endl; }
                    ;
                    

                    
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
               
IfStatement    : K_IF K_LPAREN Expression K_RPAREN StatementSeq K_FI                        { cout << "RULE: IfStatement ::= IF ( Expression ) StatementSeq FI" << endl; }
               | K_IF K_LPAREN Expression K_RPAREN StatementSeq K_ELSE StatementSeq K_FI    { cout << "RULE: IfStatement ::= IF ( Expression ) StatementSeq ELSE StatementSeq FI" << endl; }
               ;
LoopStatement  : K_LOOP K_LPAREN Expression K_RPAREN StatementSeq K_POOL  
               { cout << "RULE: LoopStatement ::= LOOP ( Expression ) StatementSeq POOL" << endl; }


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