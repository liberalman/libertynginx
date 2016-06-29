

#include <lbt_config.h>
#include <lbt_core.h>


lbt_buf_t *lbt_create_temp_buf(lbt_pool_t *pool, size_t size)
{
    lbt_buf_t *b;

    //为lbt_buf_t结构体申请空间
    b = lbt_calloc_buf(pool);

    if (NULL == b)
    {
        return NULL;
    }

    //挂载一段真实的内存buffer
    b->start = lbt_palloc(pool, size);

    if (NULL == b->start)
    {
        return NULL;
    }

    b->pos = b->start;
    b->last = b->start;
    b->end = b->last + size;
    b->temporary = 1; //表示buffer可写

    return b;
}

