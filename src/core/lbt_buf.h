#ifndef _LBT_BUF_H_INCLUDED_
#define _LBT_BUF_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

/** �������ṹ��*/
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


/** ������ṹ��*/
struct lbt_chain_s
{
    lbt_buf_t *buf; /**< ������ */
    lbt_chain_t *next; /**< ��һ��Ԫ��*/
};

/**
* ����buffer
* @param pool �������仺�������ڴ��
* @param size buffer��С
* @return ���䵽��bufferָ��
*/
lbt_buf_t *lbt_create_temp_buf(lbt_pool_t *pool, size_t size);

#define lbt_calloc_buf(pool) lbt_pcalloc(pool, sizeof(lbt_buf_t))

#endif /* _LBT_BUF_H_INCLUDED_ */

