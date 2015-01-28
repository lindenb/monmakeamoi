
%{
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



([+|\-])?[0-9]+	{ yyget_lval(yyscanner)->d = atol(yyget_text(yyscanner)); return NUM;}
[\+\-\*\/\(\)\:\?]	{ return yyget_text(yyscanner)[0];}
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
