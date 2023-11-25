all: calc1

calc1: calc1.l calc1.y
	bison -d -b calc1 calc1.y
	flex -o calc1.yy.c calc1.l
	cc -o $@ calc1.tab.c calc1.yy.c -lfl

calc2: calc2.l calc2.y
	bison -d -b calc2 calc2.y
	flex -o calc2.yy.c calc2.l
	cc -o $@ calc2.tab.c calc2.yy.c -lfl

calcp: calc-p.l calc-p.y
	bison -d -b calc-p calc-p.y
	flex -o calc-p.yy.c calc-p.l
	cc -o $@ calc-p.tab.c calc-p.yy.c -lfl

clean:
	rm -f calc1.tab.c calc1.tab.h calc1.yy.c calc1
	rm -f calc2.tab.c calc2.tab.h calc2.yy.c calc2
	rm -f calcp.tab.c calcp.tab.h calcp.yy.c calcp

