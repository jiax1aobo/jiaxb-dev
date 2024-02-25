#include "ptParseBase.h"
#include "ptParseTree.h"

/* TODO: malloc()内存分配检查！！！ */

ptParseList *ptMakeParseList(ptParseNodeType type)
{
    ptParseList *list = (ptParseList *)malloc(sizeof(ptParseList));

    list->type = type;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void *ptAddPtrValueToList(ptParseList *list, void *value)
{
    ptParseListElem *elem = (ptParseListElem *)malloc(sizeof(ptParseListElem));
    elem->data.ptr_v = value;
    elem->next = NULL;
    elem->prev = NULL;

    if (list->count == 0) {
        list->head = list->tail = elem;
    }
    else
    {
        list->tail->next = elem;
        elem->prev = list->tail;
        list->tail = elem;
    }
    list->count++;
}

void ptTravelerParseList(ptParseList *list, ptCallback callback)
{
    ptParseListElem *elem = list->head;
    while (elem != NULL) {
        callback(elem->data.ptr_v);
        elem = elem->next;
    }
}

void ptIdCallback(void *elem)
{
    ptIdentifier *e = (ptIdentifier *)elem;
    if (e != NULL) {
        ptParseNode node = e->node;
        switch (node.type) {
            case PT_PARSE_NODE_SQL_ID:
                printf("SQL ID: %s\n", e->name);
                break;
            case PT_PARSE_NODE_SQL_ID_QUOTED:
                printf("SQL ID Quoted: %s\n", e->name);
                break;
            default:
                break;
        }
    }
}

ptIdentifier *ptMakeSqlId(int32_t pos, char *name)
{
    ptIdentifier *id = (ptIdentifier *)malloc(sizeof(ptIdentifier));
    id->node.type = PT_PARSE_NODE_SQL_ID;
    id->node.pos = pos;
    strcmp(id->name, name);

    return id;
}

ptIdentifier *ptMakeSqlIdQuoted(int32_t pos, char *name)
{
    ptIdentifier *id = (ptIdentifier *)malloc(sizeof(ptIdentifier));
    id->node.type = PT_PARSE_NODE_SQL_ID_QUOTED;
    id->node.pos = pos;
    strcmp(id->name, name);

    return id;
}
