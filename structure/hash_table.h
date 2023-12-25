#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_ 1

#include "dlist.h"

typedef struct _hash_table_module
{
    
} hash_table_class;


typedef struct _hash_table
{
    int capacity;
    dlist buckets;
} hash_table;

#endif /* _HASH_TABLE_H_ */