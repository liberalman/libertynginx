#ifndef _NGX_CONNECTION_H_INCLUDED_
#define _NGX_CONNECTION_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

/**  TCP���ӽṹ�� */
struct ngx_connection_s
{
    void *data;
    ngx_event_t *read;

    ngx_socket_t fd; /** socket���������� */

    unsigned idle: 1;
    unsigned close: 1;
};

#endif /* _NGX_CONNECTION_H_INCLUDED_ */

