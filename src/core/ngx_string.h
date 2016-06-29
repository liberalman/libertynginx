#ifndef _NGX_STRING_H_INCLUDED_
#define _NGX_STRING_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

/** 字符串结构体 */
typedef struct
{
    size_t len; /**< 字符串长度 */
    u_char *data; /** 字符串首地址指针 */
} ngx_str_t;

/*
 * msvc and icc7 compile memset() to the inline "rep stos"
 * while ZeroMemory() and bzero() are the calls.
 * icc7 may also inline several mov's of a zeroed register for small blocks.
 */
#define ngx_memzero(buf, n) (void) memset(buf, 0, n)
#define ngx_memset(buf, c, n) (void) memset(buf, c, n)

#endif /* _NGX_STRING_H_INCLUDED_ */

