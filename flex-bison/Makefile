all: calc1

calc1: calc1.l calc1.y
	bison -d -b calc1 calc1.y
	flex -o calc1.yy.c calc1.l
	cc -o $@ calc1.tab.c calc1.yy.c -lfl

clean:
	rm -f calc1.tab.c calc1.tab.h calc1.yy.c calc1
