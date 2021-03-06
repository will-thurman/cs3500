// Will Thurman 
// cs3500
// hw4 - progparser.y

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
functionSeq  : functionDec                { cout << "RULE: FunctionSequence ::= FunctionDeclaration" << endl; }
             | functionDec functionSeq    { cout << "RULE: FunctionSequence ::= FunctionDeclaration FunctionSequence" << endl; }
             ;
             
functionDec  : K_FUNC T_IDENT K_LPAREN K_RPAREN K_BEGIN statementSeq K_END            { cout << "RULE: FunctionDeclaration ::= FUNC identifier ( ) BEGIN StatementSequence END" << endl; }
             | K_FUNC T_IDENT K_LPAREN paramSeq K_RPAREN K_BEGIN statementSeq K_END   { cout << "RULE: FunctionDeclaration ::= FUNC identifier ( ParamSequence ) BEGIN StatementSequence END" << endl; }
             ;
             
paramSeq     : /* empty */        { cout << "RULE: ParamSequence ::= empty" << endl; }
             | T_IDENT            { cout << "RULE: ParamSequence ::= identifier" << endl; }
             | T_IDENT K_COMMA paramSeq   { cout << "RULE: ParamSequence ::= identifier , ParamSequence" << endl;}
             ;
             
statementSeq : statement
               { cout << "RULE: StatementSequence ::= Statement" << endl; }
             | statement statementSeq
           { cout << "RULE: StatementSequence ::= Statement StatementSequence" << endl; }
             ;

expression  : /* empty */                                   { cout << "RULE: Expression ::= empty" << endl; }
            | simpleExpression                              { cout << "RULE: Expression ::= SimpleExpression" << endl; }
            | simpleExpression T_RELATION expression        { cout << "RULE: Expression ::= SimpleExpression T_RELATION SimpleExpression" << endl;}
            ;
            
simpleExpression    :  /* empty */                          { cout << "RULE: SimpleExpression ::= empty" << endl; }
                    | term                                  { cout << "RULE: SimpleExpression ::= Term" << endl; }
                    | term T_ADDOPERATOR simpleExpression   { cout << "RULE: SimpleExpression ::= Term AddOperator SimpleExpression" << endl; }
                    ;
                    
term                : /* empty */                 { cout << "RULE: Term ::= empty" << endl; }
                    | factor                      { cout << "RULE: Term ::= Factor" << endl; }
                    | factor T_MULOPERATOR term   { cout << "RULE: Term ::= Factor MulOperator Term" << endl; }
                    ;
                    
factor              : /* empty */                   { cout << "RULE: Factor ::= empty" << endl; }
                    | T_INTEGER                     { cout << "RULE: Factor ::= integer" << endl; }
                    | T_DECIMAL                     { cout << "RULE: Factor ::= decimal" << endl; }
                    | T_STRING                      { cout << "RULE: Factor ::= string" << endl; }
                    | T_IDENT                       { cout << "RULE: Factor ::= identifier" << endl; }
                    | K_LPAREN expression K_RPAREN  { cout << "RULE: Factor ::= ( Expression )" << endl; }
                    | K_NEG factor                  { cout << "RULE: Factor ::= ~ Factor" << endl; }
                    ;
                    

                    
statement : /* empty */     { cout << "RULE: Statement ::= empty" << endl; }
          | assignment      { cout << "RULE: Statement ::= Assignment" << endl; }
          | printStatement  { cout << "RULE: Statement ::= PrintStatement" << endl; }
          | retStatement
          | ifStatement
          | loopStatement
          ;

assignment : T_IDENT K_ASSIGN expression K_BANG
           { cout << "RULE: Assignment ::= ident := Expression ! " << endl; }

printStatement : K_PRINT K_LPAREN expression K_RPAREN K_BANG
               { cout << "RULE: PrintStatement ::= PRINT ( Expression ) !" << endl; }

retStatement   : K_RET T_IDENT K_BANG
               { cout << "RULE: RetStatement ::= RET identifier !" << endl; }
               
ifStatement    : K_IF K_LPAREN expression K_RPAREN statementSeq K_FI                        { cout << "RULE: IfStatement ::= IF ( Expression ) StatementSequence FI" << endl; }
               | K_IF K_LPAREN expression K_RPAREN statementSeq K_ELSE statementSeq K_FI    { cout << "RULE: IfStatement ::= IF ( Expression ) StatementSequence ELSE StatementSequence FI" << endl; }
               ;
loopStatement  : K_LOOP K_LPAREN expression K_RPAREN statementSeq K_POOL  
               { cout << "RULE: LoopStatement ::= LOOP ( Expression ) StatementSequence POOL" << endl; }


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
