#ifndef _PARSER_BASE_H_
#define _PARSER_BASE_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef enum _cmp_op_t
{
    CMP_OP_NA,     /* Not a Operator */
    CMP_OP_GT,     /* > */
    CMP_OP_LT,     /* < */
    CMP_OP_EQ,     /* = */
    CMP_OP_GE,     /* >= */
    CMP_OP_LE,     /* <= */
    CMP_OP_NE,     /* <> */
    CMP_OP_NE_X    /* != */
} cmp_op_t;

typedef enum _parse_node_t
{
    PN_TYPE_PTR_LIST,
    PN_TYPE_INT_LIST,
    PN_TYPE_SQL_ID,
    PN_TYPE_SQL_ID_QUOTED
} parse_node_t;

typedef struct _parse_node
{
    parse_node_t type;
    int32_t position;
} parse_node;

typedef struct _parse_list_elem
{
    union
    {
        void *ptr_v;
        int64_t i64_v;
    } data;
    parse_list_elem *prev;
    parse_list_elem *next;
} parse_list_elem;

typedef struct _parse_list
{
    parse_node_t type;
    int32_t count;
    parse_list_elem *head;
    parse_list_elem *tail;
} parse_list;

parse_list *parser_make_parse_list(parse_node_t type);

#endif /* _PARSER_BASE_H_ */