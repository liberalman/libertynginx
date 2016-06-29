

#include <lbt_config.h>
#include <lbt_core.h>

// ��ʼ������
lbt_cycle_t *lbt_init_cycle(lbt_cycle_t *old_cycle)
{
    PRINT_STACK_IN("in\n");
    void *rv;
    lbt_cycle_t *cycle = NULL, **old = NULL;
    lbt_log_t *log = NULL;
    lbt_uint_t i = 0;
    lbt_core_module_t *module;
    lbt_pool_t *pool;

    log = old_cycle->log;

    //�����ڴ�أ����ڱ�����޸�������Ϣ��
    pool = lbt_create_pool(LBT_CYCLE_POOL_SIZE, log);

    if (NULL == pool)
    {
        return NULL;
    }

    pool->log = log; //���ڴ����־

    //����һ���������ڴ���з���һ������lbt_cycle_t���ڴ�顣
    cycle = lbt_pcalloc(pool, sizeof(lbt_cycle_t));

    if (cycle == NULL)
    {
        lbt_destory_pool(pool); //�����ڴ��
        return NULL;
    }

    cycle->pool = pool; //�󶨴������ڴ�ص�cycle���ڴ��ָ���ϣ��Ժ����ȫ�ֵ��á�
    cycle->log = log; //��������־
    //cycle->new_log.log_level = LBT_LOG_ERR; //��־������Ϊerr��
    cycle->old_cycle = old_cycle;

    cycle->conf_prefix.len = old_cycle->conf_prefix.len;
    cycle->conf_ctx = (void *)1;
    cycle->free_connection_n = 2;

    //����ģ������
    for (i = 0; lbt_modules[i]; i++)
    {
        if (lbt_modules[i]->type != LBT_CORE_MODULE)
        {
            continue;
        }

        module = lbt_modules[i]->ctx;

        if (module->create_conf)
        {
            rv = module->create_conf(cycle);

            if (NULL == rv)
            {
                lbt_destory_pool(pool);
                return NULL;
            }

            cycle->conf_ctx[lbt_modules[i]->index] = rv;
        }
    }


    //��ʼ��ģ������
    for (i = 0; lbt_modules[i]; i++)
    {
        if (lbt_modules[i]->type != LBT_CORE_MODULE)
        {
            continue;
        }

        module = lbt_modules[i]->ctx;

        if (module->init_conf)
        {
            if (module->init_conf(cycle, cycle->conf_ctx[lbt_modules[i]->index])  == LBT_CONF_ERROR)
            {
                //environ = senv;
                //lbt_destroy_cycle_pools(&conf);
                return NULL;
            }
        }
    }

    if (lbt_process == LBT_PROCESS_SIGNALLER)
    {
        return cycle;
    }

    PRINT_STACK_OUT("out\n");
    return cycle;
}

