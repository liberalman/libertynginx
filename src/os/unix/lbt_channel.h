#ifndef _LBT_CHANNEL_H_INCLUDED_
#define _LBT_CHANNEL_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

typedef struct {
  lbt_uint_t command;
  lbt_pid_t pid;
  lbt_int_t slot;
  lbt_fd_t fd;
} lbt_channel_t;

#endif /* _LBT_CHANNEL_H_INCLUDED_ */


