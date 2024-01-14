
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
%token <sval> TOK_IDENTIFIER TOK_QUOTED_STRING

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
    /* empty rule */
    {
        /* empty action for blank line */
    }
    | ddl TOK_SEMICOLON
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
    create_table_stmt
    {
    }
;

create_table_stmt:
    TOK_CREATE TOK_TABLE identifier_chain
    TOK_LEFT_PAREN
    table_column_definition
    TOK_RIGHT_PAREN
    {
        printf("创建表:\t");
    }
;

identifier_chain:
    identifier
    {
        /* @todo */
    }
    | identifier_chain TOK_PERIOD identifier
    {
        /* @todo */
        printf("\t(period)\t");
    }
;

identifier:
    TOK_IDENTIFIER
    {
        $$ = $1;
    }
    | TOK_QUOTED_STRING
    {
        $$ = $1;
    }
;

table_column_definition_list:
    table_column_definition
    {

    }
    | table_column_definition_list TOK_COMMA table_column_definition
    {

    }
;

table_column_definition:


/*regular_identifier:
    TOK_IDENTIFIER
    {
        $$ = $1;
    }
;*/

/*delimited_identifier:
    TOK_QUOTED_STRING
    {
        $$ = $1;
    }
;*/

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