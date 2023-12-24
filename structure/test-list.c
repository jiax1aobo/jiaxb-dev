
#include <stdio.h>
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

int main(int argc, char const *argv[])
{
    mylist list;
    elem *it = NULL;
    int i = 0;
    
    dlist_init_list(&(list.handle), offsetof(elem, link));
    list.count = 0;

    elem e1;
    e1.value = 1;
    dlist_init_data(&e1, list.handle.offset);
    dlist_add_data_first(&list.handle, &e1);  
    list.count++;

    elem e2;
    e2.value = 2;
    dlist_init_data(&e2, list.handle.offset);
    dlist_add_data_first(&list.handle, &e2);
    list.count++;

    dlist_foreach_data(&(list.handle), it)
    {
        printf("[%d] = %d\n", i, it->value);
        i++;
    }

    return 0;
}
