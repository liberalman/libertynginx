#ifndef _NGX_CONNECTION_H_INCLUDED_
#define _NGX_CONNECTION_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

/**  TCP连接结构体 */
struct ngx_connection_s
{
    void *data;
    ngx_event_t *read;

    ngx_socket_t fd; /** socket连接描述符 */

    unsigned idle: 1;
    unsigned close: 1;
};

#endif /* _NGX_CONNECTION_H_INCLUDED_ */

