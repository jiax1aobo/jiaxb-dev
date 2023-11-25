#ifndef _SQL_DEF_H_
#define _SQL_DEF_H_ 1

typedef enum sql_keyword_category
{
	SQL_KEYWORD_RESERVED
} sql_keyword_category;

typedef struct sql_keyword
{
	const char *name;
	short		id;
	sql_keyword_category category;
} sql_keyword;

#endif /* _SQL_DEF_H_ 1 */
