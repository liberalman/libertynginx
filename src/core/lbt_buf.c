

#include <lbt_config.h>
#include <lbt_core.h>


lbt_buf_t *lbt_create_temp_buf(lbt_pool_t *pool, size_t size)
{
    lbt_buf_t *b;

    //Ϊlbt_buf_t�ṹ������ռ�
    b = lbt_calloc_buf(pool);

    if (NULL == b)
    {
        return NULL;
    }

    //����һ����ʵ���ڴ�buffer
    b->start = lbt_palloc(pool, size);

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

