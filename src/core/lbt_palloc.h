#ifndef _LBT_PALLOC_H_INCLUDED_
#define _LBT_PALLOC_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

/*
 * LBT_MAX_ALLOC_FROM_POOL should be (lbt_pagesize - 1), i.e. 4095 on x86.
 * On Windows NT it decreases a number of locked pages in a kernel.
 */

//#define LBT_MAX_ALLOC_FROM_POOL (lbt_pagesize - 1)

typedef struct {
u_char *last;
u_char *end;
lbt_pool_t *next;
lbt_uint_t failed;
} lbt_pool_data_t;

/** 内存池结构体*/
struct lbt_pool_s
{
    lbt_pool_data_t d;
    size_t max;
    lbt_pool_t *current;
    lbt_chain_t *chain;
    /*lbt_pool_large_t *large;
    lbt_pool_cleanup_t *cleanup;*/
    lbt_log_t *log;
};

void *lbt_alloc(size_t size, lbt_log_t *log);
void *lbt_calloc(size_t size, lbt_log_t *log);

lbt_pool_t *lbt_create_pool(size_t size, lbt_log_t *log);
void lbt_destory_pool(lbt_pool_t *pool);

void *lbt_palloc(lbt_pool_t *pool, size_t size);
void *lbt_pcalloc(lbt_pool_t *pool, size_t size);

#endif /* _LBT_PALLOC_H_INCLUDED_ */

