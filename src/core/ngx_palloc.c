

#include <ngx_config.h>
#include <ngx_core.h>

ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log)
{
    ngx_pool_t *p = NULL;

    //p = ngx_memalign(NGX_POOL_ALIGNMENT, size, log);
    p = (ngx_pool_t *)malloc(size);

    if (p == NULL)
    {
        return NULL;
    }

    p->d.last = (u_char *) p + sizeof(ngx_pool_t);
    p->d.end = (u_char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(ngx_pool_t);
    //p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    p->current = p;
    //p->chain = NULL;
    //p->large = NULL;
    //p->cleanup = NULL;
    p->log = log;

    return p;
}

void ngx_destory_pool(ngx_pool_t *pool)
{

}

ngx_int_t ngx_pfree(ngx_pool_t *pool, void *p)
{
return NGX_OK;
}

void *ngx_palloc(ngx_pool_t *pool, size_t size)
{
    return malloc(size);
}

void *ngx_pcalloc(ngx_pool_t *pool, size_t size)
{
    void *p = NULL;

    p = ngx_palloc(pool, size);

    if (p)
    {
        ngx_memzero(p, size);
    }

    return p;
}

