#include "makeint.h"
#include "filedef.h"
#include "variable.h"
#include "monmakeamoi.h"

typedef char (*translate_fun)(char);

static char *
_func_translate(char *o, char **argv,translate_fun _fun)
{
	unsigned int i;
  const char *list_iterator = argv[0];

  int doneany = 0;
  const char *p;
  unsigned int len;

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
     for(i=0;i< len;++i)
     		{
     		char c = _fun(p[i]);
        o = variable_buffer_output (o, &c, 1);
        }
      o = variable_buffer_output (o, " ", 1);
      doneany = 1;
    }
 	
  if (doneany)
    /* Kill last space.  */
    --o;
  return o;
}

char* func_toupper (char *o, char **argv, const char *funcname)
	{
  return _func_translate(o,argv,toupper);
	}

char* func_tolower (char *o, char **argv, const char *funcname)
	{
  return _func_translate(o,argv,tolower);
	}

extern long monmath_eval_string(const char* value);
char* func_calc(char *o, char **argv, const char *funcname)
	{
	char tmp[50];
	long x=monmath_eval_string(argv[0]);
	sprintf(tmp,"%ld",x);
	o = variable_buffer_output (o, tmp, strlen(tmp));
	return o;
	}

