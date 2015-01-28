#ifndef MON_MAKE_A_MOI_H
#define MON_MAKE_A_MOI_H

#define MON_MAKE_FUN_DECL(NAME) extern char* NAME(char *o, char **argv, const char *funcname)

MON_MAKE_FUN_DECL(func_toupper);
MON_MAKE_FUN_DECL(func_tolower);
MON_MAKE_FUN_DECL(func_calc);
MON_MAKE_FUN_DECL(func_md5);
MON_MAKE_FUN_DECL(func_dichotomy);
MON_MAKE_FUN_DECL(func_sublist);
MON_MAKE_FUN_DECL(func_startswith);
MON_MAKE_FUN_DECL(func_endswith);
MON_MAKE_FUN_DECL(func_contains);
MON_MAKE_FUN_DECL(func_substring_before);
MON_MAKE_FUN_DECL(func_substring_after);

/*         Name            MIN MAX EXP? Function */
#define MON_MAKE_A_MOI_FUNCTION_TABLE \
FT_ENTRY ("toupper",       0,  1,  1,  func_toupper),\
FT_ENTRY ("tolower",       0,  1,  1,  func_tolower),\
FT_ENTRY ("calc",          1,  1,  1,  func_calc),\
FT_ENTRY ("md5",           0,  1,  1,  func_md5),\
FT_ENTRY ("dichotomyl",    0,  1,  1,  func_dichotomy),\
FT_ENTRY ("dichotomyr",    0,  1,  1,  func_dichotomy),\
FT_ENTRY ("sublist",       1,  3,  1,  func_sublist),\
FT_ENTRY ("startswith",    1,  2,  1,  func_startswith),\
FT_ENTRY ("endswith",      1,  2,  1,  func_endswith),\
FT_ENTRY ("contains",      1,  2,  1,  func_contains),\
FT_ENTRY ("substring-before",      2,  2,  1,  func_substring_before),\
FT_ENTRY ("substring-after",      2,  2,  1,  func_substring_after)

#endif

