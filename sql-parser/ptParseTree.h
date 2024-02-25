#ifndef _PT_PARSE_TREE_H_
#define _PT_PARSE_TREE_H_

#include "ptParseBase.h"

#define SQL_ID_MAX_LEN 128

typedef struct ptIdentifier
{
    ptParseNode node;
    char name[SQL_ID_MAX_LEN];
} ptIdentifier;

ptIdentifier *ptMakeSqlId(int32_t pos, char *id);

ptIdentifier *ptMakeSqlIdQuoted(int32_t pos, char *id);

#endif/* _PT_PARSE_TREE_H_ */