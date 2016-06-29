

#include <ngx_config.h>
#include <ngx_core.h>


ngx_buf_t *ngx_create_temp_buf(ngx_pool_t *pool, size_t size)
{
    ngx_buf_t *b;

    //Ϊngx_buf_t�ṹ������ռ�
    b = ngx_calloc_buf(pool);

    if (NULL == b)
    {
        return NULL;
    }

    //����һ����ʵ���ڴ�buffer
    b->start = ngx_palloc(pool, size);

    if (NULL == b->start)
    {
        return NULL;
    }

    b->pos = b->start;
    b->last = b->start;
    b->end = b->last + size;
    b->temporary = 1; //��ʾbuffer��д

    return b;
}

