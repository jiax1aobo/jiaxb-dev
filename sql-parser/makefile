all: parser
parser:
	#bison -H -b ptSqlParser ptSqlParser.y
	bison -d -b ptSqlParser ptSqlParser.y
	flex -o ptSqlScanner.yy.c ptSqlScanner.l
	gcc --std=c99 ptSqlParser.tab.c ptSqlScanner.yy.c ptParseTree.c

clean:
	rm -f ptSqlParser.tab.* ptSqlScanner.yy.c a.out
