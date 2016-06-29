
#ifndef _NGX_PROCESS_CYCLE_H_INCLUDED_
#define _NGX_PROCESS_CYCLE_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

#define NGX_CMD_OPEN_CHANNEL 1


#define NGX_PROCESS_MASTER 1
#define NGX_PROCESS_SIGNALLER  2
#define NGX_PROCESS_WORKER 3

void ngx_master_process_cycle(ngx_cycle_t *cycle);

extern ngx_uint_t      ngx_process;

#endif //  _NGX_PROCESS_CYCLE_H_INCLUDED_


