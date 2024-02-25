
%{

#include <stdio.h>
#include <stdlib.h>
#include "ptParseTree.h"
#include "ptParseBase.h"
extern int yylex(void);
extern void yyerror(const char *);

#define ADDR_POOL_MAX_SIZE 1024
int addr_curr_cnt = 0;
void *addr_pool[ADDR_POOL_MAX_SIZE];

#define ADD_TO_ADDR_POOL(addr) \
    addr_pool[(addr_curr_cnt++) % ADDR_POOL_MAX_SIZE] = (void *)(addr)

#define CLEANUP_ADDR_POOL()                         \
    do \
    {                                            \
        int i;                                      \
        for(i = 0; i < ADDR_POOL_MAX_SIZE; i++) \
        {   \
            if(addr_pool[i] != NULL)\
            {              \
                free(addr_pool[i]);                 \
            }\
            else \
            {                                \
                break;                              \
            }                                       \
        }                                           \
    } while(0) 
%}

%union {
    int64_t ival;
    double fval;
    char *sval;
    ptCmpOpType cval;
    ptParseNode *node;
}

%type <ival> TOK_INTEGER
%type <fval> TOK_FLOAT
%type <cval> cond_op
%token <sval> TOK_IDENTIFIER TOK_QUOTED_STRING
%type <cval> TOK_EQ TOK_NE TOK_LT TOK_GT TOK_LE TOK_GE
%type <cval> TOK_PLUS_SIGN TOK_MINUS_SIGN TOK_ASTERISK_SIGN TOK_SOLIDUS_SIGN
%type <cval> TOK_LEFT_PAREN TOK_RIGHT_PAREN TOK_COMMA
%type <cval> TOK_AND TOK_OR TOK_CONCAT_OP TOK_LIKE TOK_IN
%type <cval> TOK_BETWEEN TOK_NOT TOK_IS
%type <cval> TOK_AT
%type <node> identifier
            identifier_chain
            ddl

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
    %empty 
    {
        /* empty action for blank line */
    }
    | start ddl TOK_SEMICOLON 
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
    /*create_table_stmt
    {
    }*/
    identifier_chain 
    {
        /* for test case */
        $$ = $1;
        ptTravelerParseList((ptParseList *)$1, ptIdCallback);
        printf("\n");
    }
;

/*create_table_stmt:
    TOK_CREATE TOK_TABLE identifier_chain
    TOK_LEFT_PAREN
    table_column_definition
    TOK_RIGHT_PAREN
    {
        printf("创建表:\t");
    }
;*/

identifier_chain:
    identifier
    {
        ptParseList *list = ptMakeParseList(PT_PARSE_NODE_PTR_LIST);
        $$ = (ptParseNode *)list;
        ADD_TO_ADDR_POOL(list);
        ADD_TO_ADDR_POOL(ptAddPtrValueToList(list, $1));
    }
    | identifier_chain TOK_PERIOD identifier
    {
        ADD_TO_ADDR_POOL(ptAddPtrValueToList((ptParseList *)$1, $3));
        $$ = $1;
    }
;

identifier:
    TOK_IDENTIFIER
    {
        $$ = (ptParseNode *)ptMakeSqlId(-1, (char *)$1);
        ADD_TO_ADDR_POOL($$);
    }
    | TOK_QUOTED_STRING
    {
        $$ = (ptParseNode *)ptMakeSqlIdQuoted(-1, (char *)$1);
        ADD_TO_ADDR_POOL($$);
    }
;

/*table_column_definition_list:
    table_column_definition
    {

    }
    | table_column_definition_list TOK_COMMA table_column_definition
    {

    }
;*/

//table_column_definition:


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
    TOK_GREATER_THAN_OP {$$ = CMP_OP_GT;}
    | TOK_LESS_THAN_OP  {$$ = CMP_OP_LT;}
    | TOK_EQUAL_OP {$$ = CMP_OP_EQ;}
    | TOK_GREATER_THAN_EQUAL_OP {$$ = CMP_OP_GE;}
    | TOK_LESS_THAN_EQUAL_OP {$$ = CMP_OP_LE;}
    | TOK_NOT_EQUAL_OP {$$ = CMP_OP_NE;}
    | TOK_NOT_EQUAL_OP_EXT {$$ = CMP_OP_NE_X;}
;

%%

int main(int argc, char **argv)
{
	while(yyparse() != 0)
	{
		printf("parsing error occured!\n");
	}

    CLEANUP_ADDR_POOL();

	return 0;
}

void yyerror(const char *s)
{
    printf("yyerror: %s\n", s);
}