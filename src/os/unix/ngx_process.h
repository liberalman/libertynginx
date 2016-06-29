#ifndef _NGX_PROCESS_H_INCLUDED_
#define _NGX_PROCESS_H_INCLUDED_

typedef pid_t ngx_pid_t;

#define NGX_INVALID_PID -1

#define NGX_MAX_PROCESSES         1024

#define NGX_PROCESS_RESPAWN -3
#define NGX_PROCESS_DETACHED -5

typedef void (*ngx_spawn_proc_pt) (ngx_cycle_t *cycle, void *data);

typedef struct {
  ngx_pid_t pid;
  int status;
  ngx_socket_t channel[2];

  ngx_spawn_proc_pt proc;
  void *data;
  char *name;

  unsigned respawn:1;
  unsigned just_spawn:1;
  unsigned detached:1;
  unsigned exiting:1;
  unsigned exited:1;
} ngx_process_t;

ngx_pid_t ngx_spawn_process(ngx_cycle_t *cycle, ngx_spawn_proc_pt proc, void *data, char *name, ngx_int_t respawn);

extern ngx_int_t ngx_process_slot; //process offset in process table.
extern ngx_process_t ngx_processes[NGX_MAX_PROCESSES]; //process table.

#endif /* _NGX_PROCESS_H_INCLUDED_ */


