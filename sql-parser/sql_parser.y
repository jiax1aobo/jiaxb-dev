
%{

#include <stdio.h>
#include <stdlib.h>
#include "parser_tree.h"
extern int yylex(void);
extern void yyerror(const char *);
%}

%union {
    int ival;
    double fval;
    char *sval;
    cmp_op cval;
}

%type <ival> TOK_INTEGER
%type <fval> TOK_FLOAT
%type <cval> cond_op
%token <sval> TOK_IDENTIFIER

%left TOK_PLUS_SIGN
%left TOK_MINUS_SIGN
%left TOK_ASTERISK_SIGN
%left TOK_SOLIDUS_SIGN
%right TOK_LEFT_PAREN
%left TOK_RIGHT_PAREN
%left TOK_COMMA
%left TOK_AND
%left TOK_OR
%left TOK_CONCAT_OP
%left TOK_LIKE
%left TOK_IN
%left TOK_BETWEEN
%left TOK_NOT
%left TOK_IS
%right TOK_AT

%token
TOK_CREATE
TOK_DATABASE
TOK_TABLE
TOK_FROM
TOK_SELECT
TOK_WHERE
TOK_VARCHAR

%token
TOK_COMM
TOK_PERIOD
TOK_QUOTE
TOK_DOUBLE_QUOTE
TOK_BACK_SOLIDUS
TOK_PERCENT
TOK_AMPERSAND
TOK_COLON
TOK_SEMICOLON
TOK_UNDERSCORE
TOK_QUESTION_MARK
TOK_LESS_THAN_OP
TOK_GREATER_THAN_OP
TOK_EQUAL_OP
TOK_NOT_EQUAL_OP
TOK_NOT_EQUAL_OP_EXT
TOK_LESS_THAN_EQUAL_OP
TOK_GREATER_THAN_EQUAL_OP
TOK_INTEGER
TOK_FLOAT
TOK_EOF

%%

start:
    ddl
    {
        printf("DDL:\n");
    }
    | TOK_EOF
    {
        printf("EOF\n");
        exit(1);
    }
;

ddl:
    create_table
    {
        printf("\tCREATE TABLE:\n");
    }
;

create_table:
    TOK_CREATE TOK_TABLE TOK_IDENTIFIER
    {
        printf("\t\tCREATE TABLE %s\n", $3);
    }
;

cond_op:
    TOK_GREATER_THAN_OP {$$ = COND_OP_GT;}
    | TOK_LESS_THAN_OP  {$$ = COND_OP_LT;}
    | TOK_EQUAL_OP {$$ = COND_OP_EQ;}
    | TOK_GREATER_THAN_EQUAL_OP {$$ = COND_OP_GE;}
    | TOK_LESS_THAN_EQUAL_OP {$$ = COND_OP_LE;}
    | TOK_NOT_EQUAL_OP {$$ = COND_OP_NE;}
    | TOK_NOT_EQUAL_OP_EXT {$$ = COND_OP_NE_X;}
;

%%
int main(int argc, char **argv)
{
	while(yyparse() != 0)
	{
		printf("parsing error occured!\n");
	}
	return 0;
}

void yyerror(const char *s)
{
    printf("yyerror: %s\n", s);
}