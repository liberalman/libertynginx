#ifndef _NGX_BUF_H_INCLUDED_
#define _NGX_BUF_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

/** 缓冲区结构体*/
typedef struct ngx_buf_s
{
    //memory
    u_char *start;
    u_char *end;
    u_char *pos;
    u_char *last;

    //file
    //ngx_file_t *file;
    off_t file_pos;
    off_t file_last;

    //tag
    unsigned temporary: 1;
} ngx_buf_t;


/** 单链表结构体*/
struct ngx_chain_s
{
    ngx_buf_t *buf; /**< 缓冲区 */
    ngx_chain_t *next; /**< 下一个元素*/
};

/**
* 创建buffer
* @param pool 用来分配缓冲区的内存池
* @param size buffer大小
* @return 分配到的buffer指针
*/
ngx_buf_t *ngx_create_temp_buf(ngx_pool_t *pool, size_t size);

#define ngx_calloc_buf(pool) ngx_pcalloc(pool, sizeof(ngx_buf_t))

#endif /* _NGX_BUF_H_INCLUDED_ */

