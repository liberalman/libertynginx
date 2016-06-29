#ifndef _NGX_CORE_H_INCLUDED_
#define _NGX_CORE_H_INCLUDED_
#include <mydebug.h>

typedef struct ngx_module_s ngx_module_t;
typedef struct ngx_cycle_s ngx_cycle_t;
typedef struct ngx_connection_s ngx_connection_t;
typedef struct ngx_event_s ngx_event_t;
typedef struct ngx_log_s ngx_log_t;
typedef struct ngx_command_s ngx_command_t;
typedef struct ngx_conf_s ngx_conf_t;
typedef struct ngx_pool_s ngx_pool_t;
typedef struct ngx_chain_s ngx_chain_t;

#define  NGX_OK          0
#define  NGX_ERROR      -1
#define  NGX_AGAIN      -2
#define  NGX_BUSY       -3
#define  NGX_DONE       -4
#define  NGX_DECLINED   -5
#define  NGX_ABORT      -6

#include <ngx_string.h>
#include <ngx_files.h>
#include <ngx_socket.h>
#include <ngx_log.h>
#include <ngx_process.h>
#include <ngx_conf_file.h>
#include <ngx_cycle.h>
#include <ngx_process_cycle.h>
#include <ngx_connection.h>
#include <ngx_palloc.h>
#include <ngx_buf.h>

#endif // _NGX_CORE_H_INCLUDED_

