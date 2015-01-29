%name-prefix="monmath"
%{
/* The MIT License

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   contact: Pierre Lindenbaum PhD @yokofakun

History:
   * Jan 2015 first commit

*/
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

%token END_OF_INPUT LT LE GT GE EQ NE MAX MIN LOGICAL_AND LOGICAL_OR
%token<d> NUM
%type<d> exp input max_items min_items
%left '-' '+'
%left '*' '/'
%left LOGICAL_AND
%left LOGICAL_OR
%left LT GT LE GE EQ NE
%left MIN 
%left MAX

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
		| exp LOGICAL_AND  exp  { $$ = ($1!=0 &&  $3!=0 ?  1:0);}
		| exp LOGICAL_OR  exp  { $$ = ($1!=0 ||  $3!=0 ?  1:0);}
		| MAX '(' max_items ')' { $$ = $3;} 
		| MIN '(' min_items ')' { $$ = $3;}
		;

max_items: max_items ',' exp { $$=($1>$3?$1:$3);}  | exp { $$=$1;};
min_items: min_items ',' exp { $$=($1<$3?$1:$3);}  | exp { $$=$1;};

%%

