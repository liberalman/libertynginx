#ifndef _LBT_BUF_H_INCLUDED_
#define _LBT_BUF_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

/** 缓冲区结构体*/
typedef struct lbt_buf_s
{
    //memory
    u_char *start;
    u_char *end;
    u_char *pos;
    u_char *last;

    //file
    //lbt_file_t *file;
    off_t file_pos;
    off_t file_last;

    //tag
    unsigned temporary: 1;
} lbt_buf_t;


/** 单链表结构体*/
struct lbt_chain_s
{
    lbt_buf_t *buf; /**< 缓冲区 */
    lbt_chain_t *next; /**< 下一个元素*/
};

/**
* 创建buffer
* @param pool 用来分配缓冲区的内存池
* @param size buffer大小
* @return 分配到的buffer指针
*/
lbt_buf_t *lbt_create_temp_buf(lbt_pool_t *pool, size_t size);

#define lbt_calloc_buf(pool) lbt_pcalloc(pool, sizeof(lbt_buf_t))

#endif /* _LBT_BUF_H_INCLUDED_ */

