#ifndef _NGX_LOG_H_INCLUDED_
#define _NGX_LOG_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

#define NGX_LOG_ERR 4

typedef u_char *(*ngx_log_handler_pt) (ngx_log_t *log, u_char *buf, size_t len);

/** 日志结构体*/
struct ngx_log_s
{
    ngx_uint_t log_level;
    //ngx_open_file_t *file;

    //ngx_atomic_uint_t connection;

    ngx_log_handler_pt handler; /**< 写日志内容的回调函数指针，由调用者自行实现日志内容写入。 */
    void *data;

    char *action;
};

#endif /* _NGX_LOG_H_INCLUDED_ */


