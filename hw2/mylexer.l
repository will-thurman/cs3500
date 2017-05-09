
/* This is c++ code embeded in the flex. it will execute like normal */
%{
#include <iostream>
using namespace std;

int tokens = 0;
int lines = 0;
%}

%option noyywrap /* This is an option, there are a lot of these, this one has something to do with lines I think */

/* These are definitions. They let you give a pattern a name, like variables in c++ */

DIGIT					[0-9]
INTCONST			[+|-]?[0-9]+
DECCONST			{INTCONST}+\.{DIGIT}+
SCICONST			{DECCONST}[E][+|-]?[1-9][0-9]*
HEXCONST			[0-9A-F]+[H]
BINCONST			[01]+B
STRCONST			\"(([A-Za-z0-9])[ ]*)+\"
EMCONST				{IDENT}(\.{IDENT})*@{IDENT}(.{IDENT})*\.(com|net|edu)
KEYWORD				"if"|"while"|"else"|"end"|"banana"|"then"
OPERATOR			"+"|"/"|"&"|"*"|"-"|"<"|">"
IDENT					[a-zA-Z][a-zA-Z0-9]*
COMMENT				[%].*[\n]

/* Between these two parentheses is where flex does it's parsing. It will search for what is on the left side, and execute what's inbetween the { }s.
   The semicolon means do nothing */
%%
{KEYWORD}								{ cout <<"#" << tokens << " TOKEN: KEYWORD \t LEXEME: " << yytext << endl; tokens++; }
{SCICONST}							{ cout <<"#" << tokens << " TOKEN: SCICONST \t LEXEME: " << yytext << endl; tokens++; }
{DECCONST}							{ cout <<"#" << tokens << " TOKEN: DECCONST \t LEXEME: " << yytext << endl; tokens++; }
{INTCONST}		   				{ cout <<"#" << tokens << " TOKEN: INTCONST \t LEXEME: " << yytext << endl; tokens++; }
{HEXCONST}							{ cout <<"#" << tokens << " TOKEN: HEXCONST \t LEXEME: " << yytext << endl; tokens++; }
{BINCONST}							{ cout <<"#" << tokens << " TOKEN: BINCONST \t LEXEME: " << yytext << endl; tokens++; }
{EMCONST}								{ cout <<"#" << tokens << " TOKEN: EMCONST \t LEXEME: " << yytext << endl; tokens++; }
{STRCONST}							{ cout <<"#" << tokens << " TOKEN: STRCONST \t LEXEME: " << yytext << endl; tokens++; }
{OPERATOR}							{ cout <<"#" << tokens << " TOKEN: OPERATOR \t LEXEME: " << yytext << endl; tokens++; }
{IDENT}									{ cout <<"#" << tokens << " TOKEN: IDENT \t LEXEME: " << yytext << endl; tokens++; }
{COMMENT}								{ lines++; }
[ \t]+									;
[\n\r]									{ lines++; }
.												{ cout <<"#" << tokens << " TOKEN: ? \t\t LEXEME: " << yytext << endl; tokens++; }

%%

int main()
{
/* in main, we call yylex() to tell flex to do it's thing. anything else you want to do can be done as well, like extra output */
	yylex();
	cout << lines << " lines processed." << endl;
	return 0;
}