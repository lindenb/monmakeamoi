%name-prefix="monmath"
%{
#include <stdio.h>
#include <stdlib.h>
#include "monmath.h"
#include "makeint.h"
%}
%union	{
	long d;
	}

%{

#include "monmath.h"

extern int yylex(YYSTYPE *yylval_param,YYLTYPE* loc,void* yyscanner);

void yyerror(YYLTYPE* loc,MonMathHandlePtr handle, const char* message)
	{
	ON (fatal, NILF, _("[" __FILE__ "]: %s"),message);
	exit(EXIT_FAILURE);
	}


%}

%error-verbose
%pure-parser
%locations
%parse-param {MonMathHandlePtr handler}
%lex-param {void* handle_to_the_scanner}

%{
#define handle_to_the_scanner (handler->scanner)
%}

%token END_OF_INPUT LT LE GT GE EQ NE
%token<d> NUM
%type<d> exp input
%left '-' '+'
%left '*' '/'
%left LT GT LE GE EQ NE
%nonassoc NEG

%start input

%%

input: exp 
	{
	$$ = $1;
	handler->retval=$1;
	}



exp:
			NUM                { $$ = $1; }
		| exp '+' exp        { $$ = $1 + $3;}
		| exp '-' exp        { $$ = $1 - $3;}
		| exp '*' exp        { $$ = $1 * $3;}
		| exp '/' exp        { $$ = $1 / $3; }
		| '-' exp  %prec NEG { $$ = -$2;}
		| '(' exp ')'        { $$ = $2;  }
		| exp LT exp        { $$ = ($1 < $3 ?  1:0);}
		| exp GT exp        { $$ = ($1 > $3 ?  1:0);}
		| exp LE exp        { $$ = ($1 <= $3 ? 1:0);}
		| exp GE exp        { $$ = ($1 >= $3 ? 1:0);}
		| exp EQ exp        { $$ = ($1 == $3 ? 1:0);}
		| exp NE exp        { $$ = ($1 != $3 ? 1:0);}
		| '('  exp '?'  exp ':' exp ')'  { $$ = ($2 != 0 ? $4 : $6);}
		;

%%

