#ifndef _PARSER_TREE_H_
#define _PARSER_TREE_H_

typedef enum _cmp_op
{
    COND_OP_NA,     /* Not a Operator */
    COND_OP_GT,     /* > */
    COND_OP_LT,     /* < */
    COND_OP_EQ,     /* = */
    COND_OP_GE,     /* >= */
    COND_OP_LE,     /* <= */
    COND_OP_NE,     /* <> */
    COND_OP_NE_X    /* != */
} cmp_op;

#endif/* _PARSER_TREE_H_ */