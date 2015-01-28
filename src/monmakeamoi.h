#ifndef MON_MAKE_A_MOI_H
#define MON_MAKE_A_MOI_H

#define MON_MAKE_FUN_DECL(NAME) extern char* NAME(char *o, char **argv, const char *funcname)

MON_MAKE_FUN_DECL(func_toupper);
MON_MAKE_FUN_DECL(func_tolower);
MON_MAKE_FUN_DECL(func_calc);
MON_MAKE_FUN_DECL(func_md5);
MON_MAKE_FUN_DECL(func_dichotomy);
MON_MAKE_FUN_DECL(func_sublist);

/*         Name            MIN MAX EXP? Function */
#define MON_MAKE_A_MOI_FUNCTION_TABLE \
FT_ENTRY ("toupper",       0,  1,  1,  func_toupper),\
FT_ENTRY ("tolower",       0,  1,  1,  func_tolower),\
FT_ENTRY ("calc",          1,  1,  1,  func_calc),\
FT_ENTRY ("md5",           0,  1,  1,  func_md5),\
FT_ENTRY ("dichotomyl",    0,  1,  1,  func_dichotomy),\
FT_ENTRY ("dichotomyr",    0,  1,  1,  func_dichotomy),\
FT_ENTRY ("sublist",       1,  3,  1,  func_sublist)\

#endif

