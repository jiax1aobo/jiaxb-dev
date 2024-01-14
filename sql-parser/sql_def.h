#ifndef _SQL_DEF_H_
#define _SQL_DEF_H_ 1

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <strings.h>

/*typedef enum _sql_keyword_category
{
	SQL_KEYWORD_RESERVED
} sql_keyword_category;*/

#define KEYWORD_MAX_LENGTH (64)

typedef struct _sql_keyword
{
	const char *name;
	uint32_t	id;
	//sql_keyword_category category;
} sql_keyword;

extern sql_keyword keyword_array[];

#define KEYWORD_ARRAY_SIZE(array) (sizeof(array)/sizeof(sql_keyword))

extern const uint32_t find_keyword(char *input_text);

/********************************************
 * A Char Poll for quoted string used in SQL
 ********************************************/

#define CHAR_POOL_MAX_SIZE (1024 * 5)

static char char_pool[CHAR_POOL_MAX_SIZE];

static uint16_t pool_water_mark = 0;

static char *_pool_alloc(uint32_t sz)
{
	char *p = NULL;
	
	if (pool_water_mark + sz > CHAR_POOL_MAX_SIZE)
	{
		fprintf(stderr, "char pool out of space!");
		exit(EXIT_FAILURE);
	}

	p = char_pool + pool_water_mark;
	pool_water_mark += sz;

	return p;
}

static char *take_off_quote(char *qstr, uint32_t len)
{
	char *p = NULL;
	uint32_t alloc = len - 1;

	p = _pool_alloc(alloc);
	/* terminated automatically */
	strncpy(p, qstr+1, alloc);

	return p;
}

#endif /* _SQL_DEF_H_ 1 */
