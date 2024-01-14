%{

#include <stdlib.h>
#include "parser_tree.h"
#include "sql_parser.tab.h"
#include "sql_def.h"

//#define yywrap() (1)

%}

back_solidus "\\"
plus_sign "+"
minus_sign "-"
asterisk "*"
solidus "/"
comma ","
period "."
quote "\'"
double_quote "\""
percent "%"
ampersand "$"
left_paren "("
right_paren ")"
/* bracket:[], brace: {},  */
colon ":"
semicolon ";"
underscore "_"
concat_op "||"
/* question_mark: ? */
exclamation_mark "!"
less_than_op "<"
greater_than_op ">"
equal_op "="
not_equal_op {less_than_op}{greater_than_op}
not_equal_op_ext {exclamation_mark}{equal_op}
less_than_equal_op {less_than_op}{equal_op}
greater_than_equal_op {greater_than_op}{equal_op}

digit [0-9]
digits {digit}+

alphabet [A-Za-z]

identifier_start [A-Za-z_]
identifier_continue [A-Za-z_0-9]
identifier {identifier_start}{identifier_continue}+
quoted_string {quote}([^\'\n]|(\'\'))*{quote}

integer [-+]?[1-9]{digits}
float [-+]?{digits}{period}{digits}


%%

{greater_than_op}       {return TOK_GREATER_THAN_OP;}
{less_than_op}          {return TOK_LESS_THAN_OP;}
{equal_op}              {return TOK_EQUAL_OP;}
{greater_than_equal_op} {return TOK_GREATER_THAN_EQUAL_OP;}
{less_than_equal_op}    {return TOK_LESS_THAN_EQUAL_OP;}
{not_equal_op}          {return TOK_NOT_EQUAL_OP;}
{not_equal_op_ext}      {return TOK_NOT_EQUAL_OP_EXT;}
{integer}       {yylval.ival = atoi(yytext); return TOK_INTEGER;}
{float}         {yylval.fval = atof(yytext); return TOK_FLOAT;}
{identifier}    {return find_keyword(yylval.sval = yytext);}
{quoted_string} {yylval.sval = take_off_quote(yytext, yyleng); return TOK_QUOTED_STRING;}

<<EOF>> {return TOK_EOF;}

%%

sql_keyword keyword_array[] =
{
    /* A */
    /* B */
    /* C */
    {"CREATE", TOK_CREATE},
    /* D */
    /* E */
    /* F */
    {"FLOAT", TOK_FLOAT},
    {"FROM", TOK_FROM},
    /* G */
    /* H */
    /* I */
    {"INTEGER", TOK_INTEGER},
    /* J */
    /* K */
    /* L */
    /* M */
    /* N */
    /* O */
    /* P */
    /* Q */
    /* R */
    /* S */
    {"SELECT", TOK_SELECT},
    /* T */
    {"TABLE", TOK_TABLE},
    /* U */
    /* V */
    {"VARCHAR", TOK_VARCHAR},
    /* W */
    {"WHERE", TOK_WHERE}
    /* X */
    /* Y */
    /* Z */
};

uint64_t kw_arr_sz = KEYWORD_ARRAY_SIZE(keyword_array);

const uint32_t find_keyword(char *input)
{
    uint32_t len;
    char tmp_buff[KEYWORD_MAX_LENGTH + 1];
    sql_keyword *l;
    sql_keyword *h;
    sql_keyword *m;
    sql_keyword *res;
    uint32_t ret;
    int32_t diff;

    len = 0;
    while(input[len] != '\0')
    {
        len++;
    }

    if(len > KEYWORD_MAX_LENGTH)
    {
        res = NULL;
    }
    else
    {
        res = NULL;
        l = keyword_array;
        h = &keyword_array[kw_arr_sz - 1];

        while(l <= h)
        {
            m = l + ((h - l) / 2);

            diff = strcasecmp(input, m->name);

            if(diff == 0)
            {
                res = m;
                break;
            }
            else if(diff > 0)
            {
                l = m + 1;
            }
            else
            {
                h = m - 1;
            }
        }
    }

    if(res == NULL)
    {
        ret = TOK_IDENTIFIER;
    }
    else
    {
        ret = res->id;
    }

    return ret;
}

int yywrap(void)
{
    return 1;
}