#ifndef _PARSER_TREE_H_
#define _PARSER_TREE_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define SQL_IDENTIFIER_MAX_LEN 128

typedef enum _cmp_op
{
    CMP_OP_NA,     /* Not a Operator */
    CMP_OP_GT,     /* > */
    CMP_OP_LT,     /* < */
    CMP_OP_EQ,     /* = */
    CMP_OP_GE,     /* >= */
    CMP_OP_LE,     /* <= */
    CMP_OP_NE,     /* <> */
    CMP_OP_NE_X    /* != */
} cmp_op;

typedef enum _parse_node_type
{
    PARSE_NODE_TYPE_SQL_IDENTIFIER,
    PARSE_NODE_TYPE_SQL_IDENTIFIER_QUOTED
} parse_node_type;

typedef struct _parse_node_common
{
    parse_node_type type;
    int32_t position;
} parse_node_common;

typedef struct _identifier
{
    parse_node_common common;
    char name[SQL_IDENTIFIER_MAX_LEN];
} identifier;

typedef struct _identifier_chain
{
    parse_node_common common;
    identifier id;
    identifier_chain *next;
} identifier_chain;

identifier *make_sql_identifier(parse_node_type type,
                                int32_t position,
                                char *id);

identifier *make_sql_identifier_quoted(parse_node_type type,
                                       int32_t position,
                                       char *id);

#endif/* _PARSER_TREE_H_ */