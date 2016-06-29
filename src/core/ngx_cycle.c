

#include <ngx_config.h>
#include <ngx_core.h>

// ��ʼ������
ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle)
{
    PRINT_STACK_IN("in\n");
    void *rv;
    ngx_cycle_t *cycle = NULL, **old = NULL;
    ngx_log_t *log = NULL;
    ngx_uint_t i = 0;
    ngx_core_module_t *module;
    ngx_pool_t *pool;

    log = old_cycle->log;

    //�����ڴ�أ����ڱ�����޸�������Ϣ��
    pool = ngx_create_pool(NGX_CYCLE_POOL_SIZE, log);

    if (NULL == pool)
    {
        return NULL;
    }

    pool->log = log; //���ڴ����־

    //����һ���������ڴ���з���һ������ngx_cycle_t���ڴ�顣
    cycle = ngx_pcalloc(pool, sizeof(ngx_cycle_t));

    if (cycle == NULL)
    {
        ngx_destory_pool(pool); //�����ڴ��
        return NULL;
    }

    cycle->pool = pool; //�󶨴������ڴ�ص�cycle���ڴ��ָ���ϣ��Ժ����ȫ�ֵ��á�
    cycle->log = log; //��������־
    //cycle->new_log.log_level = NGX_LOG_ERR; //��־������Ϊerr��
    cycle->old_cycle = old_cycle;

    cycle->conf_prefix.len = old_cycle->conf_prefix.len;
    cycle->conf_ctx = (void *)1;
    cycle->free_connection_n = 2;

    //����ģ������
    for (i = 0; ngx_modules[i]; i++)
    {
        if (ngx_modules[i]->type != NGX_CORE_MODULE)
        {
            continue;
        }

        module = ngx_modules[i]->ctx;

        if (module->create_conf)
        {
            rv = module->create_conf(cycle);

            if (NULL == rv)
            {
                ngx_destory_pool(pool);
                return NULL;
            }

            cycle->conf_ctx[ngx_modules[i]->index] = rv;
        }
    }


    //��ʼ��ģ������
    for (i = 0; ngx_modules[i]; i++)
    {
        if (ngx_modules[i]->type != NGX_CORE_MODULE)
        {
            continue;
        }

        module = ngx_modules[i]->ctx;

        if (module->init_conf)
        {
            if (module->init_conf(cycle, cycle->conf_ctx[ngx_modules[i]->index])  == NGX_CONF_ERROR)
            {
                //environ = senv;
                //ngx_destroy_cycle_pools(&conf);
                return NULL;
            }
        }
    }

    if (ngx_process == NGX_PROCESS_SIGNALLER)
    {
        return cycle;
    }

    PRINT_STACK_OUT("out\n");
    return cycle;
}

