#include <parser_base.h>
#include <parser_tree.h>

/* TODO: 内存分配检查！！！ */

parse_list *parser_make_parse_list(parse_node_t type)
{
    parse_list *list = (parse_list *)malloc(sizeof(parse_list));

    list->type = type;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void parser_add_ptr_value_to_list(parse_list *list, void *value)
{
    parse_list_elem *elem = (parse_list_elem *)malloc(sizeof(parse_list_elem));
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

identifier *parser_make_sql_id(int32_t pos, char *name)
{
    identifier *id = (identifier *)malloc(sizeof(identifier));
    id->node.type = PN_TYPE_SQL_ID;
    id->node.position = pos;
    strcmp(id->name, name);

    return id;
}

identifier *parser_make_sql_id_quoted(int32_t pos, char *name)
{
    identifier *id = (identifier *)malloc(sizeof(identifier));
    id->node.type = PN_TYPE_SQL_ID_QUOTED;
    id->node.position = pos;
    strcmp(id->name, name);

    return id;
}
