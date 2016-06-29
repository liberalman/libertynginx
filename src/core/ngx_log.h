#ifndef _NGX_LOG_H_INCLUDED_
#define _NGX_LOG_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

#define NGX_LOG_ERR 4

typedef u_char *(*ngx_log_handler_pt) (ngx_log_t *log, u_char *buf, size_t len);

/** ��־�ṹ��*/
struct ngx_log_s
{
    ngx_uint_t log_level;
    //ngx_open_file_t *file;

    //ngx_atomic_uint_t connection;

    ngx_log_handler_pt handler; /**< д��־���ݵĻص�����ָ�룬�ɵ���������ʵ����־����д�롣 */
    void *data;

    char *action;
};

#endif /* _NGX_LOG_H_INCLUDED_ */


