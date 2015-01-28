#include "makeint.h"
#include "filedef.h"
#include "variable.h"
#include "monmakeamoi.h"
#include "md5.h"

typedef char (*translate_fun)(char);

static unsigned long int str_to_ulong(const char* nptr)
    {
    char* p2;
    unsigned long N=strtoul(nptr, &p2,10);
    return N;
    }

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


char *
func_sublist(char *o, char **argv, const char *funcname)
{
  unsigned int idx = 0;
  unsigned int count = 0;

  int doneany = 0;
  const char *p;
  unsigned int len;
  
  unsigned int array_start = 0;
  unsigned int array_count = INT_MAX;
  if(argv[1]!=0)
    {
    array_start = str_to_ulong(argv[1]);
    if(argv[2]!=0)
        {
        array_count = str_to_ulong(argv[2]);
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


char *
func_startswith(char *o, char **argv, const char *funcname)
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
    if(len<=clen && strncmp(p,subsword,clen)==0)
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

char *
func_endswith(char *o, char **argv, const char *funcname)
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
    if(len<=clen && strncmp(&p[len-clen],subsword,clen)==0)
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
    if(len<=clen && (p2=strstr(p,subsword))!=0 && p2 < &p[clen] )
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


char *
func_substring_before(char *o, char **argv, const char *funcname)
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
    fprintf(stderr,"###%s %d. s=%s\n",p,len,subsword);
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


char *
func_substring_after(char *o, char **argv, const char *funcname)
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

