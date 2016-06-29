#ifndef _NGX_CYCLE_H_INCLUDED_
#define _NGX_CYCLE_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

#ifndef NGX_CYCLE_POOL_SIZE
#define NGX_CYCLE_POOL_SIZE     16384
#endif

/** ngx_cycle_t是一个重要的数据结构，它是一个很重要的容器，保存了一些全局性质的数据，在整个系统内都会被使用到*/
struct ngx_cycle_s
{
    void ** **conf_ctx; //配置上下文数组(含所有模块)
    ngx_pool_t *pool;

    ngx_log_t *log;
    ngx_log_t *new_log;

    ngx_connection_t **files; //连接文件
    ngx_uint_t files_n; /**< 打开文件个数 */

    ngx_connection_t *connections; //连接
    ngx_uint_t connection_n; /**< 连接个数*/

    ngx_connection_t *free_connections; //空闲连接
    ngx_uint_t free_connection_n; //空闲连接个数

    ngx_event_t *read_events; //读事件
    ngx_event_t *write_events; //写事件

    ngx_cycle_t *old_cycle; //old cycle指针

    ngx_str_t conf_file; //配置文件
    ngx_str_t conf_param; //配置参数
    ngx_str_t conf_prefix; //配置前缀
    ngx_str_t prefix; //前缀
    ngx_str_t lock_file; //锁文件
    ngx_str_t hostname; //主机名
};

ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle);

#endif //  _NGX_CYCLE_H_INCLUDED_

