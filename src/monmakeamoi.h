#ifndef MON_MAKE_A_MOI_H
#define MON_MAKE_A_MOI_H

#define MON_MAKE_FUN_DECL(NAME) extern char* NAME(char *o, char **argv, const char *funcname)

MON_MAKE_FUN_DECL(func_toupper);
MON_MAKE_FUN_DECL(func_tolower);
MON_MAKE_FUN_DECL(func_calc);

/*         Name            MIN MAX EXP? Function */
#define MON_MAKE_A_MOI_FUNCTION_TABLE \
FT_ENTRY ("toupper",       0,  1,  1,  func_toupper),\
FT_ENTRY ("tolower",       0,  1,  1,  func_tolower),\
FT_ENTRY ("calc",       	 1,  1,  1,  func_calc),

#endif

