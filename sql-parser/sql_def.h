#ifndef _SQL_DEF_H_
#define _SQL_DEF_H_ 1

#include <stdint.h>

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

extern const uint32_t lookup_keyword(char *input_text);

#endif /* _SQL_DEF_H_ 1 */
