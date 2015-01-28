#include "makeint.h"
#include "filedef.h"
#include "variable.h"
#include "monmakeamoi.h"
#include "md5.h"

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

char* func_toupper (char *o, char **argv, const char *funcname UNUSED)
	{
  return _func_translate(o,argv,toupper);
	}

char* func_tolower (char *o, char **argv, const char *funcname UNUSED)
	{
  return _func_translate(o,argv,tolower);
	}

extern long monmath_eval_string(const char* value);
char* func_calc(char *o, char **argv, const char *funcname UNUSED)
	{
	char tmp[50];
	long x=monmath_eval_string(argv[0]);
	sprintf(tmp,"%ld",x);
	o = variable_buffer_output (o, tmp, strlen(tmp));
	return o;
	}




char* func_md5 (char *o, char **argv, const char *funcname UNUSED)
{
  const char *list_iterator = argv[0];
  unsigned char digest[16];
  const char *p;
  unsigned int i,len, n=0;
  CMD5* md5ptr = CMD5New();

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
      if( n > 0 ) CMD5Update(md5ptr," ",1);
      CMD5Update(md5ptr,p,len);
      ++n;
    }
  CMD5Finalize(md5ptr,digest);
  for(i=0;i< 16;++i)
    {
    char tmp[3];
    sprintf(tmp, "%02x", digest[i]);
    o = variable_buffer_output (o, tmp,2);
    }
   
  free(md5ptr);
  return o;
}


 char *
func_dichotomy(char *o, char **argv, const char *funcname)
{
  const char *iter1 = argv[0];
  const char *iter2 = argv[0];
  int is_left = funcname[strlen(funcname)-1] == 'l';
  int is_right = !is_left;
  unsigned int count = 0;
  unsigned int idx = 0;

  int doneany = 0;
  const char *p;
  unsigned int len;

  /* Find the maximum number of words we'll have.  */
  while ((p = find_next_token (&iter1, NULL)) != 0)
    {
    ++count;
    }
  
  if(count==0) return o;
  
  /* Find the maximum number of words we'll have.  */
  while ((p = find_next_token (&iter2,  &len)) != 0)
    {
    if( (is_left && idx < count/2) || (is_right && idx >= count/2) )
        {
        o = variable_buffer_output (o, p, len);
        o = variable_buffer_output (o, " ", 1);
        doneany = 1;
        }
    ++idx;
    }

  if (doneany)
    /* Kill last space.  */
    --o;

  return o;
}

