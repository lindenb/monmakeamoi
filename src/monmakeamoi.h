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
MON_MAKE_FUN_DECL(func_escape);

/*         Name            MIN MAX EXP? Function */
#define MON_MAKE_A_MOI_FUNCTION_TABLE \
FT_ENTRY ("toupper",       0,  1,  1,  func_toupper),\
FT_ENTRY ("tolower",       0,  1,  1,  func_tolower),\
FT_ENTRY ("calc",          1,  1,  1,  func_calc),\
FT_ENTRY ("md5",           0,  1,  1,  func_md5),\
FT_ENTRY ("dichotomyl",    0,  1,  1,  func_dichotomy),\
FT_ENTRY ("dichotomyr",    0,  1,  1,  func_dichotomy),\
FT_ENTRY ("sublist",       1,  3,  1,  func_sublist),\
FT_ENTRY ("starts-with",    1,  2,  1,  func_startswith),\
FT_ENTRY ("ends-with",      1,  2,  1,  func_endswith),\
FT_ENTRY ("string-contains",      1,  2,  1,  func_contains),\
FT_ENTRY ("substring-before",      2,  2,  1,  func_substring_before),\
FT_ENTRY ("substring-after",      2,  2,  1,  func_substring_after),\
FT_ENTRY ("escape",      2,  2,  1,  func_escape)

#endif

