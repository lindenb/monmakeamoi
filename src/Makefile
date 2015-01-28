.PHONY:all clean
CFLAGS= -O3 -Wall -I../gnumake/make-${GNU_MAKE_VERSION}-patched 
all: monmakeamoi.a

monmakeamoi.a: monmakeamoi.o  lex.monmath.o monmath.tab.o
	ar  rcs $@ $(filter %.o,$^)
	

monmakeamoi.o : monmakeamoi.c monmakeamoi.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

lex.monmath.o: lex.monmath.c monmath.tab.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

lex.monmath.c : monmath.l monmath.tab.h
	flex --prefix=monmath $<

monmath.tab.o: monmath.tab.c monmath.tab.h
	$(CC) -c -o $@ $(CFLAGS) -Wall $<

monmath.tab.h: monmath.tab.c
monmath.tab.c: monmath.y
	bison --name-prefix=monmath -d $<

clean:
	rm -f *.a *.o
