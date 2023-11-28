
%{

#include "sql_def.h"
#include "sql_parser.tab.h"



%}

%option noyywrap

/* comment_introducer_hint "/*+" */
/* comment_introducer      "/*" */
/* comment_terminator      "*\/" */
simple_comment          "--"[^\n]*
/* c_simple_comment        "//"[^\n]* */

quote_symbol            "\'\'"
/* value_range_operator    ".." */

plus_sign       "+"
minus_sign      "-"
asterisk        "*"
solidus         "/"
comma           ","
period          "."
quote           "\'"
double_quote    "\""
reverse_solidus "\\"

percent         "%"
ampersand       "&"
left_paren      "("
right_paren     ")"
left_bracket    "["
right_bracket   "]"
left_brace      "{"
right_brace     "}"
/* left_bracket_trigraph   "??("  */
/* right_bracket_trigraph  "??)" */

colon           ":"
semicolon       ";"
underscore      "_"
question_mark   "?"
circumflex      "^"
vertical_bar    "|"

less_than_operator          "<"
greater_than_operator       ">"
equal_operator              "="
not_equal_operator          {less_than_operator}{greater_than_operator}
not_equal_operator_expand   "!="
less_than_equal_operator    {less_than_operator}{equal_operator}
greater_than_equal_operator {greater_than_operator}{equal_operator}

concatenate_operator    "||"

dollar_sign "$"

sharp   "#"
at_sign "@"

outer_mark  {left_paren}[ \t\n\r\v\f]*{plus_sign}[ \t\n\r\v\f]*{right_paren}
keep_mark   {left_paren}[ \t\n\r\v\f]*[kK][eE][eE][pP][ \t\n\r\v\f]*{right_paren}

/* open_label  "<<" */
/* close_label ">>" */
/* assignment  ":=" */

white_space [ \t\n\r\v\f]+
digit       [0-9]
digits      {digit}+
hex_digit   [a-fA-F0-9]
hex_digits  {white_space}*{hex_digit}{white_space}*{hex_digit}{white_space}*
hex_string  [xX]{quote}{hex_digits}*{quote}

identifier_start    [a-zA-Z\200-\377_]
identifier_continue [a-zA-Z\200-\377_0-9\$]
identifier          {identifier_start}{identifier_continue}*
host_variable       {colon}{identifier}

unsigned_integer_literal    {digits}[dDfF]?
positive_integer_literal    [+][ ]*{digits}
negative_integer_literal    [-][ ]*{digits}

/* unsigned_range_numeric_literal  {digits}{period}{period} */
unsigned_exact_numeric_literal  {digits}{period}[dDfF]?|{digits}{period}{digits}[dDfF]?|{period}{digits}[dDfF]?
unsigned_approximate_numeric_literal [+-][ ]*{digits}[eE][+-]{digits}|[+-][ ]*{unsigned_exact_numeric_literal}[eE][+-]?{digits}[dDfF]?

/* bracket_comment_1   {comment_introducer}{comment_terminator}|{comment_introducer}([^+])([^*]|(\*+[^*\/]))*\**{comment_terminator} */
/* bracket_comment     {bracket_comment_1} */

quote_string    {quote_symbol}|{quote}([^\']|{quote_symbol})+{quote}
double_quote_string {double_quote}[^\"]*{double_quote}

not_applicable  [\000-\010\012-\014\016-\037\041\140\176\177-\377]+

/* with_time_zone  [wW][iI][tT][hH]{white_space}[tT][iI][mM][eE]{white_space}[zZ][oO][nN][eE] */
/* with_data  [wW][iI][tT][hH]{white_space}[dD][aA][tT][aA] */
/* with_no_data [wW][iI][tT][hH]{white_space}[nN][oO]{white_space}[dD][aA][tT][aA] */

/* not_deferrable  [nN][oO][tT]{white_space}[dD][eE][fF][eE][rR][rR][aA][bB][lL][eE] */
/* not_enforced    [nN][oO][tT]{white_space}[eE][nN][fF][oO][rR][cC][eE][dD] */

/* in_reverse      [iI][nN]{white_space}[rR][eE][vV][eE][rR][sS][eE] */

/* end_exec [eE][nN][dD]{white_space}[eE][xX][eE][cC] */

/* connect_by          [cC][oO][nN][nN][eE][cC][tT]{white_space}[bB][yY] */
/* connect_by_nocycle  [cC][oO][nN][nN][eE][cC][tT]{white_space}[bB][yY]{white_space}[nN][oO][cC][yY][cC][lL][eE] */

/* // order_siblings_by [oO][rR][dD][eE][rR]{white_space}[sS][iI][bB][lL][iI][nN][gG][sS]{white_space}[bB][yY] */
/* package_body    [pP][aA][cC][kK][aA][gG][eE]{white_space}[bB][oO][dD][yY] */

/* is_distinct_from [iI][sS]{white_space}[dD][iI][sS][tT][iI][nN][cC][tT]{white_space}[fF][rR][oO][mM] */
/* is_not_distinct_from [iI][sS]{white_space}[nN][oO][tT]{white_space}[dD][iI][sS][tT][iI][nN][cC][tT]{white_space}[fF][rR][oO][mM] */

/* partition_by    [pP][aA][rR][tT][iI][tT][iI][oO][nN]{white_space}[bB][yY] */

/* unbounded_following [uU][nN][bB][oO][uU][nN][dD][eE][dD]{white_space}[fF][oO][lL][lL][oO][wW][iI][nN][gG] */
/* unbounded_preceding [uU][nN][bB][oO][uU][nN][dD][eE][dD]{white_space}[pP][rR][eE][cC][eE][dD][iI][nN][gG] */

%%
{simple_comment}    { /* do nothing */ }

{plus_sign}         { return TOK_PLUS_SIGN; }
{minus_sign}        { return TOK_MINUS_SIGN; }
{asterisk}          { return TOK_ASTERISK; }
{solidus}   { return TOK_SOLIDUS; }
{comma} { return TOK_COMMA; }
{period}    { return TOK_PERIOD; }
{quote} { return TOK_QUOTE; }
{double_quote} { return TOK_DOUBLE_QUOTE; }
{reverse_solidus} { return TOK_REVERSE_SOLIDUS; }

{percent} { return TOK_PERCENT; }
{ampersand} { return TOK_AMPERSAND; }
{left_paren} { return TOK_LEFT_PAREN; }
{right_paren} { return TOK_RIGHT_PAREN; }
{left_bracket} { return TOK_LEFT_BRACKET; }
{right_bracket} { return TOK_RIGHT_BRACKET; }
{left_brace} { return TOK_LEFT_BRACE; }
{right_brace} { return TOK_RIGHT_BRACE; }

{colon} { return TOK_COLON; }
{semicolon} { return TOK_SEMICOLON; }
{underscore} { return TOK_UNDERSCORE; }
{question_mark} { return TOK_QUESTION_MARK; }
{circumflex} { return TOK_CIRCUMFLEX; }
{vertical_bar} { return TOK_VERTICAL_BAR; }

{less_than_operator}    { return TOK_LESS_THAN_OPERATOR; }
{greater_than_operator}    { return TOK_GREATER_THAN_OPERATOR; }
{equal_operator} { return TOK_EQUAL_OPERATOR; }
{not_equal_operator} { return TOK_NOT_EQUAL_OPERATOR; }
{not_equal_operator_expand} { return TOK_NOT_EQUAL_OPERATOR_EXPAND; }
{less_than_equal_operator} { return TOK_LESS_THAN_EQUAL_OPERATOR; }
{greater_than_equal_operator} { return TOK_GREATER_THAN_EQUAL_OPERATOR; }

{concatenate_operator} { return TOK_CONCATENATE_OPERATOR; }

{dollar_sign} { return TOK_DOLLAR_SIGN; }
{sharp} { return TOK_SHARP;}
{at_sign} { return TOK_AT_SIGN; }

{white_space} { /* ignore white space */ }

{unsigned_approximate_numeric_literal} { return TOK_UNSIGNED_APPROXIMATE_NUMERIC_LITERAL; }
{unsigned_exact_numeric_literal} { return TOK_UNSIGNED_EXACT_NUMERIC_LITERAL; }
{unsigned_integer_literal} { return TOK_UNSIGNED_INTEGER_LITERAL; }

{identifier} {

}

{quote_string} {
    yyleng -= 2;
    
}
%%

const sql_keyword keyword_list[] =
{
    { "CREATE", TOK_CREATE, SQL_KEYWORD_RESERVED },
    { "DATABASE", TOK_DATABASE, SQL_KEYWORD_RESERVED },
    { "INTEGER", TOK_INTEGER, SQL_KEYWORD_RESERVED },
    { "TABLE", TOK_TABLE, SQL_KEYWORD_RESERVED },
    { "VARCHAR", TOK_VARCHAR, SQL_KEYWORD_RESERVED }
};