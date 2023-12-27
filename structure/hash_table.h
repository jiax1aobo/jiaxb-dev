#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_ 1

#include "dlist.h"
#include <stdint.h>

typedef struct _hash_elem
{
    void *key;
    list_node link;
} hash_elem;

typedef struct _hash_elem_list
{
    dlist handle;
    uint32_t count;
} hash_elem_list;

typedef struct _bucket_list
{
    hash_elem_list elem_list;
    bucket_list *next;
} bucket_list;

typedef struct _hash_table
{
    int capacity;
    bucket_list hash_bucket;
} hash_table;

void *init_hash_table()

#endif /* _HASH_TABLE_H_ */