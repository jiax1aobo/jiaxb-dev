#ifndef _COMMON_H_
#define _COMMON_H_ 1

typedef enum _status
{
    SUCCESS = 0,
    FAILURE = 1
} status;

#define C_FINISH       \
    goto FINISH_LABEL; \
    FINISH_LABEL:

#define C_TRY(_expr)           \
    do                         \
    {                          \
        if (!(_expr))          \
        {                      \
            goto FINISH_LABEL; \
        }                      \
    } while (0)

#define C_TRY_THROW(_expr, _label) \
    do                             \
    {                              \
        if (!(_expr))              \
        {                          \
            goto _label;           \
        }                          \
    } while (0)

#define C_CATCH(_label) \
    goto FINISH_LABEL;  \
    _label:

#define C_RAMP(_label) \
    _label:

#endif /* _COMMON_H_ */