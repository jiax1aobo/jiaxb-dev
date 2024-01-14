#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>



#define ID_MAX_LEN 64

typedef enum kwt
{
    KW_T_CREATE = 0,
    KW_T_TABLE,
    KW_T_ID,
    KW_T_DATABASE,
    KW_T_INDEX,
    KW_T_COLUMN
}kwt;

typedef struct kw
{
    const char      *name;
    const uint32_t   id;
}kw;

kw kwarr[] =
{
    {"COLUMN", KW_T_COLUMN},
    {"CREATE",KW_T_CREATE},
    {"DATABASE", KW_T_DATABASE},
    {"ID", KW_T_ID},
    {"INDEX", KW_T_INDEX},
    {"TABLE", KW_T_TABLE},
};

kw *lookup(char *input)
{
    uint32_t len;
    char tmp_buff[ID_MAX_LEN + 1];
    kw *l;
    kw *h;
    kw *m;
    kw *res;
    int32_t diff;
    uint32_t arr_sz;

    len = 0;
    while(input[len] != '\0')
    {
        len++;
    }

    if(len > ID_MAX_LEN)
    {
        res = NULL;
    }
    else
    {
        for (int j = 0; j < len; j++)
        {
            tmp_buff[j] = toupper(input[j]);
        }
        tmp_buff[len] = '\0';

        arr_sz = sizeof(kwarr) / sizeof(kw);
        l = kwarr;
        h = &kwarr[arr_sz - 1];

        res = NULL;
        while(l <= h)
        {
            m = l + ((h - l) / 2);

            diff = strcmp(m->name, tmp_buff);

            if(diff == 0)
            {
                res = m;
                break;
            }
            else if(diff < 0)
            {
                l = m + 1;
            }
            else
            {
                h = m - 1;
            }
        }
    }

    return res;
}

int main(int argc, char const *argv[])
{
    char *list[] =
    {
        "create",
        "table",
        "database",
        "myself",
    };
    uint32_t sz = (sizeof(list) / sizeof(char *));
    kw *it;

    for(int i = 0; i < sz; i++)
    {
        it = lookup(list[i]);
        if (it)
        {
            printf("kw: %s\n", it->name);
        }
        else
        {
            it = &kwarr[3];

            printf("id: %s\n", it->name);
        }
    }

    return 0;
}
