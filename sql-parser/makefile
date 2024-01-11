all: parser
parser:
	bison -H -b sql_parser sql_parser.y
	flex -o sql_scanner.yy.c sql_scanner.l
	gcc sql_parser.tab.c sql_scanner.yy.c
