
#ifndef _LBT_PROCESS_CYCLE_H_INCLUDED_
#define _LBT_PROCESS_CYCLE_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

#define LBT_CMD_OPEN_CHANNEL 1


#define LBT_PROCESS_MASTER 1
#define LBT_PROCESS_SIGNALLER  2
#define LBT_PROCESS_WORKER 3

void lbt_master_process_cycle(lbt_cycle_t *cycle);

extern lbt_uint_t      lbt_process;

#endif //  _LBT_PROCESS_CYCLE_H_INCLUDED_


