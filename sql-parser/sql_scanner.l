
%{

#include "sql_def.h"
#include "sql_parser.tab.h"



%}

%option noyywrap

comment_introducer_hint "/*+"
comment_introducer      "/*"
comment_terminator      "*/"
simple_comment          "--"[^\n]*
c_simple_comment        "//"[^\n]*

quote_symbol            "\'\'"
value_range_operator    ".."

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
// left_bracket_trigraph   "??("    // dont know what for
// right_bracket_trigraph  "??)"    // dont know what for

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

open_label  "<<"    // for psm
close_label ">>"    // for psm
assignment  ":="    // for psm

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

unsigned_range_numeric_literal  {digits}{period}{period}
unsigned_exact_numeric_literal  {digits}{period}[dDfF]?|{digits}{period}{digits}[dDfF]?|{period}{digits}[dDfF]?
unsigned_approximate_numeric_literal [+-][ ]*{digits}[eE][+-]{digits}|[+-][ ]*{unsigned_exact_numeric_literal}[eE][+-]?{digits}[dDfF]?

bracket_comment_1   {comment_introducer}{comment_terminator}|{comment_introducer}([^+])([^*]|(\*+[^*/]))*\**{comment_terminator}
bracket_comment     {bracket_comment_1}

quote_string    {quote_symbol}|{quote}([^\']|{quote_symbol})+{quote}
double_quote_string {double_quote}[^\"]*{double_quote}

not_applicable  [\000-\010\012-\014\016-\037\041\140\176\177-\377]+

with_time_zone  [wW][iI][tT][hH]{white_space}[tT][iI][mM][eE]{white_space}[zZ][oO][nN][eE]
with_data  [wW][iI][tT][hH]{white_space}[dD][aA][tT][aA]
with_no_data [wW][iI][tT][hH]{white_space}[nN][oO]{white_space}[dD][aA][tT][aA]


%%

%%

const sql_keyword keyword_list[] =
{
    { "CREATE", TOK_CREATE, SQL_KEYWORD_RESERVED },
    { "DATABASE", TOK_DATABASE, SQL_KEYWORD_RESERVED },
    { "TABLE", TOK_TABLE, SQL_KEYWORD_RESERVED }
};