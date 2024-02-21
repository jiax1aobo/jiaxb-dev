#ifndef _PARSER_TREE_H_
#define _PARSER_TREE_H_

#include <parser_base.h>

#define SQL_IDENTIFIER_MAX_LEN 128

typedef struct _identifier
{
    parse_node node;
    char name[SQL_IDENTIFIER_MAX_LEN];
} identifier;

typedef struct _identifier_chain
{
    parse_node node;
    identifier name;
    identifier_chain *next;
} identifier_chain;

identifier *parser_make_sql_id(int32_t pos, char *id);

identifier *parser_make_sql_id_quoted(int32_t pos, char *id);

#endif/* _PARSER_TREE_H_ */