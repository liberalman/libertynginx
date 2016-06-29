

#include <lbt_config.h>
#include <lbt_core.h>

lbt_pool_t *lbt_create_pool(size_t size, lbt_log_t *log)
{
    lbt_pool_t *p = NULL;

    //p = lbt_memalign(LBT_POOL_ALIGNMENT, size, log);
    p = (lbt_pool_t *)malloc(size);

    if (p == NULL)
    {
        return NULL;
    }

    p->d.last = (u_char *) p + sizeof(lbt_pool_t);
    p->d.end = (u_char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(lbt_pool_t);
    //p->max = (size < LBT_MAX_ALLOC_FROM_POOL) ? size : LBT_MAX_ALLOC_FROM_POOL;

    p->current = p;
    //p->chain = NULL;
    //p->large = NULL;
    //p->cleanup = NULL;
    p->log = log;

    return p;
}

void lbt_destory_pool(lbt_pool_t *pool)
{

}

lbt_int_t lbt_pfree(lbt_pool_t *pool, void *p)
{
return LBT_SUCCESS;
}

void *lbt_palloc(lbt_pool_t *pool, size_t size)
{
    return malloc(size);
}

void *lbt_pcalloc(lbt_pool_t *pool, size_t size)
{
    void *p = NULL;

    p = lbt_palloc(pool, size);

    if (p)
    {
        lbt_memzero(p, size);
    }

    return p;
}

