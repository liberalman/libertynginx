#ifndef _LBT_CORE_H_INCLUDED_
#define _LBT_CORE_H_INCLUDED_
#include <mydebug.h>

typedef struct lbt_module_s       lbt_module_t;
typedef struct lbt_cycle_s          lbt_cycle_t;
typedef struct lbt_connection_s  lbt_connection_t;
typedef struct lbt_event_s          lbt_event_t;
typedef struct lbt_log_s              lbt_log_t;
typedef struct lbt_command_s    lbt_command_t;
typedef struct lbt_conf_s            lbt_conf_t;
typedef struct lbt_pool_s             lbt_pool_t;
typedef struct lbt_chain_s           lbt_chain_t;

#define  LBT_SUCCESS       0
#define  LBT_ERROR         -1
#define  LBT_AGAIN          -2
#define  LBT_BUSY            -3
#define  LBT_DONE           -4
#define  LBT_DECLINED   -5
#define  LBT_ABORT         -6

#include <lbt_errno.h>
#include <lbt_string.h>
#include <lbt_files.h>
#include <lbt_socket.h>
#include <lbt_log.h>
#include <lbt_process.h>
#include <lbt_conf_file.h>
#include <lbt_cycle.h>
#include <lbt_process_cycle.h>
#include <lbt_connection.h>
#include <lbt_palloc.h>
#include <lbt_buf.h>

#endif // _LBT_CORE_H_INCLUDED_

