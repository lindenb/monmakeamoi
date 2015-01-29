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

