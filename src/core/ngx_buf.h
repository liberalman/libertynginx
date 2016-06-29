#ifndef _NGX_BUF_H_INCLUDED_
#define _NGX_BUF_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

/** �������ṹ��*/
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


/** ������ṹ��*/
struct ngx_chain_s
{
    ngx_buf_t *buf; /**< ������ */
    ngx_chain_t *next; /**< ��һ��Ԫ��*/
};

/**
* ����buffer
* @param pool �������仺�������ڴ��
* @param size buffer��С
* @return ���䵽��bufferָ��
*/
ngx_buf_t *ngx_create_temp_buf(ngx_pool_t *pool, size_t size);

#define ngx_calloc_buf(pool) ngx_pcalloc(pool, sizeof(ngx_buf_t))

#endif /* _NGX_BUF_H_INCLUDED_ */

