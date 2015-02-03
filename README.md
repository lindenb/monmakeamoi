# Motivation

This repository contains a patch for GNU make v 4.1. it incudes some new functions
to enhance the basic distribution of make

## Why don't you use plugins ?

I don't want to only add functions, I also want to create new variables like `${MAKE_JOB_SLOTS}`

## Why don't you use guile ?

I don't have time to learn a new language and I want to reduce the number of dependencies

## Why did you named this 'monmakeamoi' ?

It sounds like 'Mon mec à moi', a French song by Patricia Kass : https://www.youtube.com/watch?v=IpWcSEaEyR8

# Compilation

Compilation requires GNU auto-tools, GNU bison and GNU flex.

Start with a  fresh repo to avoid any loop during compilation.

To compile and create a binary under `dist/bin` just run

```bash
$ make
```

To only prepare a patched version, with a  `.configure` file:

```bash
$ make precompile
```

# New Option

## STOP-FILE

```
--stop-file=[FILE]
```

if *FILE* is present, Make will wait for the end of current jobs but will not start new jobs.


# New variables

## MAKE_JOB_SLOTS

`${MAKE_JOB_SLOTS}` is the number of parallel jobs allowed with option `-j`

```make
all:
	echo "NJOBS_SLOTS=${MAKE_JOB_SLOTS}"
```

run:

```
$ monmakeamoi -j2
echo "NJOBS_SLOTS=2"
NJOBS_SLOTS=2
```
# New Functions

Example

```make
LETTERS=A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
.PHONY:all test_dichotomy


all: test_dichotomy
	echo "Test $(toupper hello world)"
	echo "Test $(tolower HELLO WORLD)"
	echo "$(calc  (1 + 3) )"
	echo "$(calc  (2<3 ? 3 : 2) * 10 )"
	echo "NJOBS_SLOTS=${MAKE_JOB_SLOTS}"
	echo "$(md5 hello world)"
	echo "${MACHINE_PROCESSORS}"
	echo "${MACHINE_CORES}"
	echo "$(dichotomyl 1 2 3 4 5 6 7 8 9 10 11)"
	echo "$(dichotomyr 1 2 3 4 5 6 7 8 9 10 11)"
	echo "$(sublist 1 2 3 4 5 6 7 8 9 10 11)"
	echo "$(sublist 1 2 3 4 5 6 7 8 9 10 11,5)"
	echo "$(sublist 1 2 3 4 5 6 7 8 9 10 11,)"
	echo "$(sublist 1 2 3 4 5 6 7 8 9 10 11,1,3)"
	echo "$(sublist 1 2 3 4 5 6 7 8 9 10 11,,3)"
	echo "$(sublist 1 2 3 4 5 6 7 8 9 10 11,1000,3)"
	echo "$(substring-before tain,mountains tain ssss obtain captain)"
	echo "$(substring-after tain,mountains tain ssss obtain captain-america)"	
	echo "$(starts-with mo,mountains miii mo mon xxx)"
	echo "$(ends-with ics,genetics genomics biology bioinformatics)"
	echo "$(string-contains aaa, azdaaa aaad daaa abababa aizdu a)"
	echo "$(calc max(1,100,9999,-8888))"	
	echo "$(calc min(1,100,9999,-8888))"
	echo "$(calc 1>2 && 3>2)"	
	echo "$(calc 1>2 || 3>2)"	
	echo "$(escape xml, <hello>world'</hello>)"
	echo "$(escape http, Pierre Lindenbaum[Author])"
	

define divideandconquer

ifeq ($(words $(1)),"0")

else ifeq ($(words $(1)),1)

$(1)_$(1).txt :
	echo -n "$(1)" > $$@

else

$(firstword $(1))_$(lastword $(1)).txt: \
	$(firstword $(dichotomyl $(1)))_$(lastword $(dichotomyl $(1))).txt \
	$(firstword $(dichotomyr $(1)))_$(lastword $(dichotomyr $(1))).txt
	cat $$^ > $$@

$$(eval $$(call divideandconquer,$(dichotomyl $(1))))
$$(eval $$(call divideandconquer,$(dichotomyr $(1))))
endif
endef

test_dichotomy: A_Z.txt
	cat $<



$(eval $(call divideandconquer,${LETTERS}))
```

*  `$(toupper list)` convert the list to uppercase
*  `$(toupper list)` convert the list to uppercase
*  `$(calc expr)` do basic calculation using integers
*  `$(md5 list)` creates a md5 checksum of the arguments. Used to create filenames
*  `$(dichotomyl list)` break the list in two parts, returns the left part. See Divide-and-conquer in a Makefile : recursivity and parallelism. http://plindenbaum.blogspot.fr/2014/12/divide-and-conquer-in-makefile.html
*  `$(dichotomyr list)` break the list in two parts, returns the right part. 
*  `$(sublist list,start,count)` return a sublist of at most `count` items starting from the `start` element (first is 0)
*  `$(substring-before word,list)` returns a string that is the rest of a given string before a given substring. 
*  `$(substring-after word,list)` returns a string that is the rest of a given string after a given substring. 
*  `$(starts-with word,list)` returns all items in the list starting with `word`
*  `$(ends-with word,list)` returns all items in the list ending with `word`
*  `$(string-contains word,list)` returns all items in the list containing `word`
*  `$(escape language,string)` escape characters using language (currently: 'xml' and 'http' )

Run:

```
echo -n "A" > A_A.txt
echo -n "B" > B_B.txt
echo -n "C" > C_C.txt
cat B_B.txt C_C.txt > B_C.txt
cat A_A.txt B_C.txt > A_C.txt
echo -n "D" > D_D.txt
echo -n "E" > E_E.txt
echo -n "F" > F_F.txt
cat E_E.txt F_F.txt > E_F.txt
cat D_D.txt E_F.txt > D_F.txt
cat A_C.txt D_F.txt > A_F.txt
echo -n "G" > G_G.txt
echo -n "H" > H_H.txt
echo -n "I" > I_I.txt
cat H_H.txt I_I.txt > H_I.txt
cat G_G.txt H_I.txt > G_I.txt
echo -n "J" > J_J.txt
echo -n "K" > K_K.txt
cat J_J.txt K_K.txt > J_K.txt
echo -n "L" > L_L.txt
echo -n "M" > M_M.txt
cat L_L.txt M_M.txt > L_M.txt
cat J_K.txt L_M.txt > J_M.txt
cat G_I.txt J_M.txt > G_M.txt
cat A_F.txt G_M.txt > A_M.txt
echo -n "N" > N_N.txt
echo -n "O" > O_O.txt
echo -n "P" > P_P.txt
cat O_O.txt P_P.txt > O_P.txt
cat N_N.txt O_P.txt > N_P.txt
echo -n "Q" > Q_Q.txt
echo -n "R" > R_R.txt
echo -n "S" > S_S.txt
cat R_R.txt S_S.txt > R_S.txt
cat Q_Q.txt R_S.txt > Q_S.txt
cat N_P.txt Q_S.txt > N_S.txt
echo -n "T" > T_T.txt
echo -n "U" > U_U.txt
echo -n "V" > V_V.txt
cat U_U.txt V_V.txt > U_V.txt
cat T_T.txt U_V.txt > T_V.txt
echo -n "W" > W_W.txt
echo -n "X" > X_X.txt
cat W_W.txt X_X.txt > W_X.txt
echo -n "Y" > Y_Y.txt
echo -n "Z" > Z_Z.txt
cat Y_Y.txt Z_Z.txt > Y_Z.txt
cat W_X.txt Y_Z.txt > W_Z.txt
cat T_V.txt W_Z.txt > T_Z.txt
cat N_S.txt T_Z.txt > N_Z.txt
cat A_M.txt N_Z.txt > A_Z.txt
cat A_Z.txt
ABCDEFGHIJKLMNOPQRSTUVWXYZecho "Test HELLO WORLD"
Test HELLO WORLD
echo "Test hello world"
Test hello world
echo "4"
4
echo "30"
30
echo "NJOBS_SLOTS=1"
NJOBS_SLOTS=1
echo "5eb63bbbe01eeed093cb22bb8f5acdc3"
5eb63bbbe01eeed093cb22bb8f5acdc3
echo "2"
2
echo "2"
2
echo "1 2 3 4 5"
1 2 3 4 5
echo "6 7 8 9 10 11"
6 7 8 9 10 11
echo "1 2 3 4 5 6 7 8 9 10 11"
1 2 3 4 5 6 7 8 9 10 11
echo "6 7 8 9 10 11"
6 7 8 9 10 11
echo "1 2 3 4 5 6 7 8 9 10 11"
1 2 3 4 5 6 7 8 9 10 11
echo "2 3 4"
2 3 4
echo "1 2 3"
1 2 3
echo ""

echo "moun ob cap"
moun ob cap
echo "s  -america"	
s  -america
echo "mountains mo mon"
mountains mo mon
echo "genetics genomics bioinformatics"
genetics genomics bioinformatics
echo "azdaaa aaad daaa"
azdaaa aaad daaa
echo "9999"	
9999
echo "-8888"
-8888
echo "0"	
0
echo "1"	
1
echo " &lt;hello&gt;world&apos;&lt;/hello&gt;"
 &lt;hello&gt;world&apos;&lt;/hello&gt;
echo "+Pierre+Lindenbaum%5bAuthor%5d"
+Pierre+Lindenbaum%5bAuthor%5d
```

# Author

Pierre Lindenbaum PhD @yokofakun

## Contribute

- Issue Tracker: github.com/lindenb/monmakeamoi/issues`
- Source Code: github.com/lindenb/monmakeamoi

##See also

* make Manual : http://www.gnu.org/software/make/manual/make.html
* makefile2graph : https://github.com/lindenb/makefile2graph
* Divide-and-conquer in a Makefile : recursivity and parallelism. http://plindenbaum.blogspot.fr/2014/12/divide-and-conquer-in-makefile.html

##History

* 2015 : Creation

## License

The project is licensed under the MIT license.



