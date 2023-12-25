#ifndef _DLIST_H_
#define _DLIST_H_ 1

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef struct _list_node
{
    void *next;
    void *prev;
} list_node;

typedef struct _dlist
{
    list_node link;  /* entire doubly list */
    uint64_t offset; /* offset of list_node in data */
} dlist;

#define dlist_get_link(_pdata, _off) \
    ((list_node *)((char *)(_pdata) + (_off)))

#define dlist_get_data(_plink, _off) \
    ((void *)((char *)(_plink) - (_off)))

#define dlist_init_list(_plist, _off) \
    {                                 \
        (_plist)->link.next = NULL;   \
        (_plist)->link.prev = NULL;   \
        (_plist)->offset = (_off);    \
    }

#define dlist_init_data(_pdata, _off)                    \
    {                                                    \
        (dlist_get_link(_pdata, _off))->next = (_pdata); \
        (dlist_get_link(_pdata, _off))->prev = (_pdata); \
    }

#define dlist_get_first_data(_plist) \
    ((_plist)->link.next == NULL ? (dlist_get_data(_plist, (_plist)->offset)) : (_plist)->link.next)

#define dlist_get_last_data(_plist) \
    ((_plist)->link.prev == NULL ? (dlist_get_data(_plist, (_plist)->offset)) : (_plist)->link.prev)

/* invalid for NULL */
#define dlist_get_next_data(_plist, _pdata) \
    ((dlist_get_link(_pdata, (_plist)->offset))->next == NULL ? (dlist_get_data(_plist, (_plist)->offset)) : (dlist_get_link(_pdata, (_plist)->offset))->next)

/* invalid for NULL */
#define dlist_get_prev_data(_plist, _pdata) \
    ((dlist_get_link(_pdata, (_plist)->offset))->prev == NULL ? (dlist_get_data(_plist, (_plist)->offset)) : (dlist_get_link(_pdata, (_plist)->offset))->prev)

/* TRUE for empty
 * FALSE for non-empty */
#define dlist_is_empty(_plist) \
    (((dlist_get_first_data(_plist)) == (dlist_get_data(_plist, (_plist)->offset))) ? TRUE : FALSE)

#define dlist_add_data_first(_plist, _pdata)                                        \
    {                                                                               \
        (dlist_get_link(_pdata, (_plist)->offset))->prev = NULL;                    \
        (dlist_get_link(_pdata, (_plist)->offset))->next = (_plist)->link.next;     \
        if ((_plist)->link.next != NULL)                                            \
        {                                                                           \
            (dlist_get_link((_plist)->link.next, (_plist)->offset))->prev = _pdata; \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            (_plist)->link.prev = _pdata;                                           \
        }                                                                           \
        (_plist)->link.next = _pdata;                                               \
    }

#define dlist_add_data_last(_plist, _pdata)                                         \
    {                                                                               \
        (dlist_get_link(_pdata, (_plist)->offset))->next = NULL;                    \
        (dlist_get_link(_pdata, (_plist)->offset))->prev = (_plist)->link.prev;     \
        if ((_plist)->link.prev != NULL)                                            \
        {                                                                           \
            (dlist_get_link((_plist)->link.prev, (_plist)->offset))->next = _pdata; \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            (_plist)->link.next = _pdata;                                           \
        }                                                                           \
        (_plist)->link.prev = _pdata;                                               \
    }

#define dlist_insert_data_after(_plist, _pdata, _prev)                 \
    {                                                                  \
        void *_next = (dlist_get_link(_prev, (_plist)->offset))->next; \
        (dlist_get_link(_prev, (_plist)->offset))->next = _pdata;      \
        (dlist_get_link(_pdata, (_plist)->offset))->prev = _prev;      \
        (dlist_get_link(_pdata, (_plist)->offset))->next = _next;      \
        if (_next != NULL)                                             \
        {                                                              \
            (dlist_get_link(_next, (_plist)->offset))->prev = _pdata;  \
        }                                                              \
        else                                                           \
        {                                                              \
            (_plist)->link.prev = _pdata;                              \
        }                                                              \
    }

#define dlist_insert_data_before(_plist, _pdata, _next)                \
    {                                                                  \
        void *_prev = (dlist_get_link(_next, (_plist)->offset))->prev; \
        (dlist_get_link(_next, (_plist)->offset))->prev = _pdata;      \
        (dlist_get_link(_pdata, (_plist)->offset))->next = _next;      \
        (dlist_get_link(_pdata, (_plist)->offset))->prev = _prev;      \
        if (_prev != NULL)                                             \
        {                                                              \
            (dlist_get_link(_prev, (_plist)->offset))->next = _pdata;  \
        }                                                              \
        else                                                           \
        {                                                              \
            (_plist)->link.next = _pdata;                              \
        }                                                              \
    }

#define dlist_foreach_data(_plist, _pdata)                   \
    for (_pdata = dlist_get_first_data(_plist);              \
         _pdata != dlist_get_data(_plist, (_plist)->offset); \
         _pdata = dlist_get_next_data(_plist, _pdata))

#define dlist_foreach_data_safe(_plist, _pdata, _next)                                       \
    for (_pdata = dlist_get_first_data(_plist), _next = dlist_get_next_data(_plist, _pdata); \
         _pdata != dlist_get_data(_plist, (_plist)->offset);                                 \
         _pdata = pnext, _next = dlist_get_next_data(_plist, _pdata))

#define dlist_foreach_data_from(_plist, _from, _pdata)       \
    for (_pdata = _from;                                     \
         _pdata != dlist_get_data(_plist, (_plist)->offset); \
         _pdata = dlist_get_next_data(_plist, _pdata))

#define dlist_foreach_data_from_safe(_plist, _from, _pdata, _next)    \
    for (_pdata = _from, _next = dlist_get_next_data(_plist, _pdata); \
         _pdata != dlist_get_data(_plist, (_plist)->offset);          \
         _pdata = _next, _next = dlist_get_next_data(_plist, _pdata))

#define dlist_reverse_foreach_data(_plist, _pdata)           \
    for (_pdata = dlist_get_last_data(_plist);               \
         _pdata != dlist_get_data(_plist, (_plist)->offset); \
         _pdata = dlist_get_prev_data(_plist, _pdata))

#define dlist_reverse_foreach_data_safe(_plist, _pdata, _prev)                              \
    for (_pdata = dlist_get_last_data(_plist), _prev = dlist_get_prev_data(_plist, _pdata); \
         _pdata != dlist_get_data(_plist, (_plist)->offset);                                \
         _pdata = _prev, _prev = dlist_get_prev_data(_plist, _pdata))

#define dlist_reverse_foreach_data_from(_plist, _from, _pdata) \
    for (_pdata = _from;                                       \
         _pdata != dlist_get_data(_plist, (_plist)->offset);   \
         _pdata = dlist_get_prev_data(_plist, _pdata))

#define dlist_reverse_foreach_data_from_safe(_plist, _from, _pdata, _prev) \
    for (_pdata = _from, _prev = dlist_get_prev_data(_plist, _pdata);      \
         _pdata != dlist_get_data(_plist, (_plist)->offset);               \
         _pdata = _prev, _prev = dlist_get_prev_data(_plist, _pdata))

#endif /* _DLIST_H_ */