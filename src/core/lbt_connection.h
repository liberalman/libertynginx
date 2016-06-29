#ifndef _LBT_CONNECTION_H_INCLUDED_
#define _LBT_CONNECTION_H_INCLUDED_


#include <lbt_config.h>
#include <lbt_core.h>

/**  TCP连接结构体 */
struct lbt_connection_s
{
    void *data;
    lbt_event_t *read;

    lbt_socket_t fd; /** socket连接描述符 */

    unsigned idle: 1;
    unsigned close: 1;
};

#endif /* _LBT_CONNECTION_H_INCLUDED_ */

