
#include "common.h"
#include "hash_table.h"

status init_hash_table(hash_table **htab, uint32_t cap)
{
    uint32_t step = 0;
    hash_table *ht = NULL;
    hash_elem_list *hel = NULL;

    C_TRY_THROW(ht = (hash_table *)malloc(sizeof(hash_table)),
                ERR_ALLOC_FAILURE);
    step = 1;

    ht->capacity = (cap == -1) ? 4 : cap;

    C_TRY_THROW(hel = (hash_elem_list *)malloc(sizeof(hash_elem_list) * ht->capacity),
                ERR_ALLOC_FAILURE);
    step = 2;

    *htab = ht;

    return SUCCESS;

    C_CATCH(ERR_ALLOC_FAILURE)
    {
        switch (step)
        {
        case 2:
            free(hel);
        case 1:
            free(ht);
        case 0:
            /* nothing to release */
            break;
        default:
            /* assert(0); */
            break;
        }
    }

    C_FINISH;

    return FAILURE;
}