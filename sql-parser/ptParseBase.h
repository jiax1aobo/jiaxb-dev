#ifndef _PT_PARSE_BASE_H_
#define _PT_PARSE_BASE_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum ptCmpOpType
{
    PT_CMP_OP_NA,     /* Not a Operator */
    PT_CMP_OP_GT,     /* > */
    PT_CMP_OP_LT,     /* < */
    PT_CMP_OP_EQ,     /* = */
    PT_CMP_OP_GE,     /* >= */
    PT_CMP_OP_LE,     /* <= */
    PT_CMP_OP_NE,     /* <> */
    PT_CMP_OP_NE_X    /* != */
} ptCmpOpType;

typedef enum ptParseNodeType
{
    PT_PARSE_NODE_PTR_LIST,
    PT_PARSE_NODE_INT_LIST,
    PT_PARSE_NODE_SQL_ID,
    PT_PARSE_NODE_SQL_ID_QUOTED
} ptParseNodeType;

typedef struct ptParseNode
{
    ptParseNodeType type;
    int32_t pos;
} ptParseNode;

typedef struct ptParseListElem
{
    union
    {
        void *ptr_v;
        int64_t i64_v;
    } data;
    struct ptParseListElem *prev;
    struct ptParseListElem *next;
} ptParseListElem;

typedef struct ptParseList
{
    ptParseNodeType type;
    int32_t count;
    ptParseListElem *head;
    ptParseListElem *tail;
} ptParseList;

ptParseList *ptMakeList(ptParseNodeType type);

void *ptAddPtrValueToList(ptParseList *list, void *value);

typedef void (*ptCallback)(void *);

void ptTravelerParseList(ptParseList *list, ptCallback callback);

void ptIdCallback(void *elem);

#endif /* _PT_PARSE_BASE_H_ */