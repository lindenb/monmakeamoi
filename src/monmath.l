
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
typedef void* lex_extra_param_t;
#include "monmath.h"
#include "monmath.tab.h"
#include "makeint.h"

void monmatherror (YYLTYPE* loc,MonMathHandlePtr handler, char const *msg);


int monmathwrap (yyscan_t yyscanner )
    {
    return 1;
    }

%}

%option bison-bridge
%option bison-locations
%option reentrant
%option yylineno



%%


max {return MAX;}
min { return MIN;}
\&\& { return LOGICAL_AND;}
\|\|	{ return LOGICAL_OR; }
([+|\-])?[0-9]+	{ yyget_lval(yyscanner)->d = atol(yyget_text(yyscanner)); return NUM;}
[\+\-\*\/\(\)\:\?,]	{ return yyget_text(yyscanner)[0];}
\<= return LE;
\< return LT;
\>= return  GE;
> return GT;
== return  EQ;
!= return NE;
[\n\t\r ] ;
.	{
    ON (fatal, NILF, _("[" __FILE__ "]: Syntax error: %s"),yyget_text(yyscanner));
    exit(EXIT_FAILURE);
    }

%%

extern int monmathparse();

long monmath_eval_string(const char* value)
{
    yyscan_t myscanner;
    MonMathHandle handler;
    memset(&handler,0,sizeof(MonMathHandle));
    
    monmathlex_init_extra(&handler,&myscanner);
    handler.scanner= myscanner;
 
    /*Copy string into new buffer and Switch buffers*/
    monmath_scan_string(value, myscanner);
    
    monmathparse(&handler);
    
    monmathlex_destroy(myscanner);
    return handler.retval;
}
