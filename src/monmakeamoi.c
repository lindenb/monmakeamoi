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
#include "makeint.h"
#include "filedef.h"
#include "variable.h"
#include "monmakeamoi.h"
#include "md5.h"
/** used by toupper && tolower */
typedef int (*translate_fun)(int);

/* convert number to ulong */
static unsigned long int str_to_ulong(const char* nptr,unsigned long n)
    {
    char* p2;
    unsigned long N=strtoul(nptr, &p2,10);
    if(isspace(*p2) || *p2==0)  return N;
    ON (fatal, NILF, _("[" __FILE__ "]: Syntax error cannot convert: \"%s\" to unsigned interger."),nptr);
    return -1;
    }

/** called by toupper && tolower */
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

/** function toupper */
char* func_toupper (char *o, char **argv, const char *funcname UNUSED)
	{
  return _func_translate(o,argv,toupper);
	}

/** function tolower */
char* func_tolower (char *o, char **argv, const char *funcname UNUSED)
	{
  return _func_translate(o,argv,tolower);
	}

/** function mathematical eval */
extern long monmath_eval_string(const char* value);//defined in monmath.l

char* func_calc(char *o, char **argv, const char *funcname UNUSED)
	{
	char tmp[50];
	long x = monmath_eval_string(argv[0]);
	sprintf(tmp,"%ld",x);
	o = variable_buffer_output (o, tmp, strlen(tmp));
	return o;
	}

/** function MD5 sum */
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


char *
func_sublist(char *o, char **argv, const char *funcname)
{
  unsigned int idx = 0;

  int doneany = 0;
  const char *p;
  unsigned int len;
  
  unsigned int array_start = 0;
  unsigned int array_count = INT_MAX;
  if(argv[1]!=0)
    {
    array_start = str_to_ulong(argv[1],strlen(argv[1]));
    if(argv[2]!=0)
        {
        array_count = str_to_ulong(argv[2],strlen(argv[2]));
        }
    }
  const char *iter1 = argv[0];

  
  if(array_count==0) return o;
  
  /* Find the maximum number of words we'll have.  */
  while ((p = find_next_token (&iter1,  &len)) != 0)
    {
    if( idx >= array_start )
        {
        if( idx < array_start + array_count )
            {
            o = variable_buffer_output (o, p, len);
            o = variable_buffer_output (o, " ", 1);
            doneany = 1;
            }
        else
            {
            break;
            }
        }
    ++idx;
    }
  if (doneany)
    /* Kill last space.  */
    --o;

  return o;
}

/** function $(starts-with key,list) */
char *func_startswith(char *o, char **argv, const char *funcname)
{
  const char *subsword = argv[0];
  unsigned int clen = strlen(argv[0]);
  const char *list_iterator = argv[1];
  

  int doneany = 0;
  const char *p;
  unsigned int len;
   
  if( clen == 0 ) return o; 

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
    if(len>=clen && strncmp(p,subsword,clen)==0)
        {
        o = variable_buffer_output (o, p, len);
        o = variable_buffer_output (o, " ", 1);
        doneany = 1;
        }
    }
 	
  if (doneany)
    /* Kill last space.  */
    --o;
  return o;
}

/** function $(ends-with key,list) */
char * func_endswith(char *o, char **argv, const char *funcname)
{
  const char *subsword = argv[0];
  unsigned int clen = strlen(argv[0]);
  const char *list_iterator = argv[1];
  

  int doneany = 0;
  const char *p;
  unsigned int len;
   
  if( clen == 0 ) return o; 

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
    if(len>=clen && strncmp(&p[len-clen],subsword,clen)==0)
        {
        o = variable_buffer_output (o, p, len);
        o = variable_buffer_output (o, " ", 1);
        doneany = 1;
        }
    }
 	
  if (doneany)
    /* Kill last space.  */
    --o;
  return o;
}

/** function $(string-contains key,list) */
char *
func_contains(char *o, char **argv, const char *funcname)
{
  const char *subsword = argv[0];
  unsigned int clen = strlen(argv[0]);
  const char *list_iterator = argv[1];
  int doneany = 0;
  const char *p;
  const char *p2;
  unsigned int len;
   
  if( clen == 0 ) return o; 

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
    if(len>=clen && (p2=strstr(p,subsword))!=0 && p2 < &p[len] )
        {
        o = variable_buffer_output (o, p, len);
        o = variable_buffer_output (o, " ", 1);
        doneany = 1;
        }
    }
 	
  if (doneany)
    /* Kill last space.  */
    --o;
  return o;
}

/** function $(substring-before key,list) */
char* func_substring_before(char *o, char **argv, const char *funcname)
{
  const char *subsword = argv[0];
  unsigned int clen = strlen(subsword);
  const char *list_iterator = argv[1];
  

  int doneany = 0;
  const char *p;
  const char *p2;
  unsigned int len;
   
  if( clen == 0 ) return o; 

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
    if(len>clen && (p2=strstr(p,subsword))!=0 && p2 < &p[len] )
        {
        o = variable_buffer_output (o, p, p2-p);
        o = variable_buffer_output (o, " ", 1);
        doneany = 1;
        }
    }
 	
  if (doneany)
    /* Kill last space.  */
    --o;
  return o;
}

/** function $(substring-after key,list) */
char* func_substring_after(char *o, char **argv, const char *funcname)
{
  const char *subsword = argv[0];
  unsigned int clen = strlen(argv[0]);
  const char *list_iterator = argv[1];
  

  int doneany = 0;
  const char *p;
  const char *p2;
  unsigned int len;
   
  if( clen == 0 ) return o; 

  while ((p = find_next_token (&list_iterator, &len)) != 0)
    {
    if(len>clen && (p2=strstr(p,subsword))!=0 && p2 < &p[len] )
        {
        o = variable_buffer_output (o, &p2[clen], len-(clen+p2-p));
        o = variable_buffer_output (o, " ", 1);
        doneany = 1;
        }
    }
 	
  if (doneany)
    /* Kill last space.  */
    --o;
  return o;
}

/** function $(substring-after key,list) */
char* func_escape(char *o, char **argv, const char *funcname)
{
  const char *language = argv[0];
  const char *p = argv[1];
  unsigned int i,len=strlen(p);
   
	if( strcmp(language,"xml") == 0)
		{
	 	for(i=0;i< len;++i)
	      {
	      switch(p[i])
	      	{
	      	case '<' : o = variable_buffer_output (o, "&lt;",4); break;
	      	case '>' : o = variable_buffer_output (o, "&gt;",4); break;
	      	case '&' : o = variable_buffer_output (o, "&amp;",5); break;
	      	case '\'' : o = variable_buffer_output (o,"&apos;",6); break;
	      	case '\"' : o = variable_buffer_output (o,"&quot;",6); break;
	      	default: o = variable_buffer_output (o, &p[i],1); break;
	      	}
	      }
		}
	else if( strcmp(language,"http") == 0)
		{
	 	for(i=0;i< len;++i)
	      {
	      if(isalpha(p[i]) || isdigit(p[i]))
	      	{
	      	o = variable_buffer_output (o,&p[i],1); 
	      	}
	      else if(p[i]==' ')
	      	{
	      	o = variable_buffer_output (o,"+",1);
	      	}
	      else
	      	{
	      	char tmp[10];
	      	sprintf(tmp, "%%%02x", p[i]);
	      	o = variable_buffer_output (o,tmp,3);
	      	}
	      }
		}
  return o;
}


