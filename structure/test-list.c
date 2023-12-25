
#include <stdio.h>
#include <unistd.h>
#include "dlist.h"

typedef struct elem
{
    int value;
    list_node link;
} elem;

typedef struct mylist
{
    int count;
    dlist handle;
} mylist;

void add_first(mylist *ls, elem *el, int v, int off)
{
    el->value = v;
    dlist_init_data(el, ls->handle.offset);
    dlist_add_data_first(&(ls->handle), el);
    (ls->count)++;
}

void add_last(mylist *ls, elem *el, int v, int off)
{
    el->value = v;
    dlist_init_data(el, ls->handle.offset);
    dlist_add_data_last(&(ls->handle), el);
    (ls->count)++;
}

void insert_before(mylist *ls, elem *el, elem *aft, int v, int off)
{
    el->value = v;
    dlist_init_data(el, ls->handle.offset);
    dlist_insert_data_before(&(ls->handle), el, aft);
    (ls->count)++;
}

void insert_after(mylist *ls, elem *el, elem *bef, int v, int off)
{
    el->value = v;
    dlist_init_data(el, ls->handle.offset);
    dlist_insert_data_after(&(ls->handle), el, bef);
    (ls->count)++;
}

int main(int argc, char const *argv[])
{
    mylist list;
    elem *it = NULL;
    int i = 0;
    
    dlist_init_list(&(list.handle), offsetof(elem, link));
    list.count = 0;

    // [1]
    elem e1;
    add_first(&list, &e1, 1, list.handle.offset);
    
    // [2, 1]
    elem e2;
    add_first(&list, &e2, 2, list.handle.offset);

    // [2, 1, 3]
    elem e3;
    add_last(&list, &e3, 3, list.handle.offset);

    // [2, 4, 1, 3]
    elem e4;
    insert_before(&list, &e4, &e1, 4, list.handle.offset);

    // [2, 4, 5, 1, 3]
    elem e5;
    insert_after(&list, &e5, &e4, 5, list.handle.offset);

    i = 0;
    dlist_foreach_data(&(list.handle), it)
    {
        printf("[%d] = %d,\t", i, it->value);
        i++;
    }
    printf("\n");

    i = 0;
    dlist_reverse_foreach_data(&(list.handle), it)
    {
        printf("[%d] = %d,\t", i, it->value);
        i++;
    }
    printf("\n");

    return 0;
}
