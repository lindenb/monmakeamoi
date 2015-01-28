%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();


void yyerror(const char* s)
	{
	fprintf(stderr,"ERRORRRR \"%s\"\n",s);
	exit(-1);
	}
%}
%union	{
	long d;
	}
%error-verbose

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
	fprintf(stderr,"XXXXXXXXXXXXXXXXXx %d\n",$$);
	}

exp:
			NUM                { $$ = $1;           }
		| exp '+' exp        { $$ = $1 + $3;   fprintf(stderr,"XXXXXXXXXXXXXXXXXx %d\n",$$);   }
		| exp '-' exp        { $$ = $1 - $3;      }
		| exp '*' exp        { $$ = $1 * $3;      }
		| exp '/' exp        { $$ = $1 / $3;      }
		| '-' exp  %prec NEG { $$ = -$2;          }
		| '(' exp ')'        { $$ = $2;           }
		| exp LT exp        { $$ = ($1 < $3 ?  1:0);}
		| exp GT exp        { $$ = ($1 > $3 ?  1:0);}
		| exp LE exp        { $$ = ($1 <= $3 ? 1:0);}
		| exp GE exp        { $$ = ($1 >= $3 ? 1:0);}
		| exp EQ exp        { $$ = ($1 == $3 ? 1:0);}
		| exp NE exp        { $$ = ($1 != $3 ? 1:0);}
		;

%%

