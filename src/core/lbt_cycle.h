#ifndef _LBT_CYCLE_H_INCLUDED_
#define _LBT_CYCLE_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

#ifndef LBT_CYCLE_POOL_SIZE
#define LBT_CYCLE_POOL_SIZE     16384
#endif

/** lbt_cycle_t是一个重要的数据结构，它是一个很重要的容器，保存了一些全局性质的数据，在整个系统内都会被使用到*/
struct lbt_cycle_s
{
    void ** **conf_ctx; //配置上下文数组(含所有模块)
    lbt_pool_t *pool;

    lbt_log_t *log;
    lbt_log_t *new_log;

    lbt_connection_t **files; //连接文件
    lbt_uint_t files_n; /**< 打开文件个数 */

    lbt_connection_t *connections; //连接
    lbt_uint_t connection_n; /**< 连接个数*/

    lbt_connection_t *free_connections; //空闲连接
    lbt_uint_t free_connection_n; //空闲连接个数

    lbt_event_t *read_events; //读事件
    lbt_event_t *write_events; //写事件

    lbt_cycle_t *old_cycle; //old cycle指针

    lbt_str_t conf_file; //配置文件
    lbt_str_t conf_param; //配置参数
    lbt_str_t conf_prefix; //配置前缀
    lbt_str_t prefix; //前缀
    lbt_str_t lock_file; //锁文件
    lbt_str_t hostname; //主机名
};

lbt_cycle_t *lbt_init_cycle(lbt_cycle_t *old_cycle);

#endif //  _LBT_CYCLE_H_INCLUDED_

