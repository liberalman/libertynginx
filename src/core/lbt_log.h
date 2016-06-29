#ifndef _LBT_LOG_H_INCLUDED_
#define _LBT_LOG_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

#define LBT_LOG_ERR 4

typedef u_char *(*lbt_log_handler_pt) (lbt_log_t *log, u_char *buf, size_t len);

/** ��־�ṹ��*/
struct lbt_log_s
{
    lbt_uint_t log_level;
    //lbt_open_file_t *file;

    //lbt_atomic_uint_t connection;

    lbt_log_handler_pt handler; /**< д��־���ݵĻص�����ָ�룬�ɵ���������ʵ����־����д�롣 */
    void *data;

    char *action;
};

void lbt_log_stderr(lbt_err_t err, const char *fmt, ...);

#endif /* _LBT_LOG_H_INCLUDED_ */


