.PHONY:all clean
CFLAGS= -g -Wall -I../gnumake/make-${GNU_MAKE_VERSION}-patched 
all: monmakeamoi.a

monmakeamoi.a: monmakeamoi.o  lex.monmath.o monmath.tab.o md5.o
	ar  rcs $@ $(filter %.o,$^)
	

monmakeamoi.o : monmakeamoi.c monmakeamoi.h md5.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

lex.monmath.o: lex.monmath.c monmath.tab.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

lex.monmath.c : monmath.l monmath.tab.h
	flex --nodefault --batch --prefix=monmath $<

monmath.tab.o: monmath.tab.c monmath.tab.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

monmath.tab.h: monmath.tab.c
monmath.tab.c: monmath.y
	bison  --token-table --verbose -d $<

md5.o : md5.c md5.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

clean:
	rm -f *.a *.o
