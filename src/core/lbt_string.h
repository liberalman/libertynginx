#ifndef _LBT_STRING_H_INCLUDED_
#define _LBT_STRING_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

/** �ַ����ṹ�� */
typedef struct
{
    size_t len; /**< �ַ������� */
    u_char *data; /** �ַ����׵�ַָ�� */
} lbt_str_t;

/*
 * msvc and icc7 compile memset() to the inline "rep stos"
 * while ZeroMemory() and bzero() are the calls.
 * icc7 may also inline several mov's of a zeroed register for small blocks.
 */
#define lbt_memzero(buf, n) (void) memset(buf, 0, n)
#define lbt_memset(buf, c, n) (void) memset(buf, c, n)

#endif /* _LBT_STRING_H_INCLUDED_ */

