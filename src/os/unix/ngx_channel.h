#ifndef _NGX_CHANNEL_H_INCLUDED_
#define _NGX_CHANNEL_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

typedef struct {
  ngx_uint_t command;
  ngx_pid_t pid;
  ngx_int_t slot;
  ngx_fd_t fd;
} ngx_channel_t;

#endif /* _NGX_CHANNEL_H_INCLUDED_ */


