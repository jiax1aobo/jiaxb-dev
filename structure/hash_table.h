#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_ 1

#include "dlist.h"
#include <stdint.h>

typedef struct _hash_elem
{
    void *key;
    void *value;
    list_node link;
} hash_elem;

typedef struct _hash_elem_list
{
    dlist handle;
    uint32_t count;
} hash_elem_list;

typedef struct _bucket_item
{
    hash_elem_list elem_list;
    list_node link;
} bucket_item;

typedef struct _bucket_list
{
    dlist handle;
    uint32_t *count; /* capacity */
} bucket_list;

typedef struct _hash_table
{
    uint32_t capacity;
    bucket_list buckets;
} hash_table;

status create_hash_table(hash_table **ht, uint32_t cap);

status destroy_hash_table(hash_table *ht, uint32_t cap);

#endif /* _HASH_TABLE_H_ */
