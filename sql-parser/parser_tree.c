#include "parser_tree.h"

identifier *make_sql_identifier(parse_node_type type,
                                int32_t position,
                                char *name)
{
    identifier *id = (identifier *)malloc(sizeof(identifier));
    id->common.type = PARSE_NODE_TYPE_SQL_IDENTIFIER;
    // id->common.position = position;
    strcmp(id->name, name);

    return id;
}