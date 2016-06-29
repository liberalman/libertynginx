#ifndef _LBT_LOG_H_INCLUDED_
#define _LBT_LOG_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

#define LBT_LOG_ERR 4

typedef u_char *(*lbt_log_handler_pt) (lbt_log_t *log, u_char *buf, size_t len);

/** 日志结构体*/
struct lbt_log_s
{
    lbt_uint_t log_level;
    //lbt_open_file_t *file;

    //lbt_atomic_uint_t connection;

    lbt_log_handler_pt handler; /**< 写日志内容的回调函数指针，由调用者自行实现日志内容写入。 */
    void *data;

    char *action;
};

void lbt_log_stderr(lbt_err_t err, const char *fmt, ...);

#endif /* _LBT_LOG_H_INCLUDED_ */


