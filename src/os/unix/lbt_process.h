#ifndef _LBT_PROCESS_H_INCLUDED_
#define _LBT_PROCESS_H_INCLUDED_

typedef pid_t lbt_pid_t;

#define LBT_INVALID_PID -1

#define LBT_MAX_PROCESSES         1024

#define LBT_PROCESS_RESPAWN -3
#define LBT_PROCESS_DETACHED -5

typedef void (*lbt_spawn_proc_pt) (lbt_cycle_t *cycle, void *data);

typedef struct {
  lbt_pid_t pid;
  int status;
  lbt_socket_t channel[2];

  lbt_spawn_proc_pt proc;
  void *data;
  char *name;

  unsigned respawn:1;
  unsigned just_spawn:1;
  unsigned detached:1;
  unsigned exiting:1;
  unsigned exited:1;
} lbt_process_t;

lbt_pid_t lbt_spawn_process(lbt_cycle_t *cycle, lbt_spawn_proc_pt proc, void *data, char *name, lbt_int_t respawn);

extern lbt_int_t lbt_process_slot; //process offset in process table.
extern lbt_process_t lbt_processes[LBT_MAX_PROCESSES]; //process table.

#endif /* _LBT_PROCESS_H_INCLUDED_ */


