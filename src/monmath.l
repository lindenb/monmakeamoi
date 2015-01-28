
%{
#include "monmath.tab.h"
%}

%option noyywrap

%%



[\n\t ] ;
[0-9]+	{ ECHO;monmathlval.d = atol(yytext); return NUM;}
[\+\-\*\/\(\)]	{ return yytext[0];}
\<= return LE;
\< return LT;
\>= return  GE;
> return GT;
== return  EQ;
!= return NE;
.	{printf(stderr,"SYNTAX ERROR %s.\n",yytext); exit(-1);}

%%

extern int monmathparse();

long monmath_eval_string(const char* value)
{
    YY_BUFFER_STATE str_buffer = monmath_scan_string (value);
    monmathparse();
    /*Delete the new buffer*/
    monmath_delete_buffer(str_buffer);
    return monmathlval.d;
}
