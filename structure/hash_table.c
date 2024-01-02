
#include "common.h"
#include "hash_table.h"
#include <string.h>

status create_hash_table(hash_table **htab, uint32_t cap)
{
    uint32_t step = 0;
    hash_table *ht = NULL;
    bucket_item *bi = NULL;
    int32_t i;

    C_TRY(ht = (hash_table *)malloc(sizeof(hash_table)));
    step = 1;

    ht->capacity = (cap == 0) ? 4 : cap;

    ht->buckets.count = &(ht->capacity);
    dlist_init_list(&(ht->buckets.handle), offsetof(bucket_item, link));

    C_TRY(bi = (bucket_item *)malloc(sizeof(bucket_item) * ht->capacity));
    step = 2;

    for (i = 0; i < ht->capacity; i++)
    {
        dlist_init_data(&(bi[i]), ht->buckets.handle.offset);
        dlist_add_data_last(&(ht->buckets.handle), &(bi[i]));

        dlist_init_list(&(bi[i].elem_list.handle), offsetof(hash_elem, link));
        bi[i].elem_list.count = 0;
    }

    *htab = ht;

    return SUCCESS;

    C_FINISH;

    switch (step)
    {
    case 2:
        free(bi);
    case 1:
        free(ht);
    case 0:
        /* nothing to release */
        break;
    default:
        /* assert(0); */
        break;
    }

    return FAILURE;
}

status destroy_hash_table(hash_table *ht)
{
    bucket_item *bi = ht->buckets.handle.link.next;

    free(bi);
    free(ht);
    
    return SUCCESS;
}

status insert_hash_table(hash_table *ht, hash_elem *he, int32_t kty)
{
    uint32_t hc = 0;
    uint32_t idx = 0;
    bucket_list *blist = NULL;
    bucket_item *bitem = NULL;
    hash_elem_list *elist = NULL;
    uint32_t i = 0;

    blist = &(ht->buckets);

    if (kty == 0)
    {
        hc = byte_hash_code(he->key, strlen(he->key), 0);
    }
    else
    {
        /* assert(kty == 1); */
        hc = integer_hash_code(he->key);
    }

    idx = hc % ht->capacity;

    dlist_foreach_data(&(blist->handle), bitem)
    {
        if (i == idx)
        {
            break;
        }
        else
        {
            bitem = dlist_get_next_data(&(blist->handle), bitem);
        }
    }
    
    elist = &(bitem->elem_list);
    dlist_add_data_first(&(elist->handle), he);

    return SUCCESS;

    C_FINISH;

    return FALSE;
}