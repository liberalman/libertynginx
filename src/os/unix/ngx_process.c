

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_channel.h>

ngx_int_t        ngx_process_slot; //offset of current process in processes table.
ngx_socket_t     ngx_channel;
ngx_process_t    ngx_processes[NGX_MAX_PROCESSES]; // processes table.
ngx_int_t ngx_last_process = 0; // the last one of processes table.

// proc是子进程的执行函数，data是其参数，name是子进程的名字
ngx_pid_t ngx_spawn_process(ngx_cycle_t *cycle, ngx_spawn_proc_pt proc, void *data, char *name, ngx_int_t respawn)
{
    PRINT_STACK_IN("in\n");
    u_long on;
    ngx_pid_t pid;
    ngx_int_t s; // 将要创建的子进程在进程表中的位置

    if (respawn >= 0)
    {
        // 替换进程ngx_processes[respawn]，可安全重用该进程表项
        s = respawn;
    }
    else
    {
        for (s = 0; s < ngx_last_process; s++)
        {
            if (-1 == ngx_processes[s].pid)
            {
                // 先找到一个被回收的进程表项
                break;
            }
        }

        if (NGX_MAX_PROCESSES == s)
        {
            // 进程表已满，直接退出。
            //ngx_log_error(NGX_LOG_ALERT, cycle->log, 0, "no more than %d processes can be spawned", NGX_MAX_PROCESSES);
            return NGX_INVALID_PID;
        }
    }

    if ( NGX_PROCESS_DETACHED != respawn)
    {
        // 不是分离的子进程
    }
    else
    {
        // 分离的子进程
        //初始化进程通信的socket为-1
        ngx_processes[s].channel[0] = -1;
        ngx_processes[s].channel[1] = -1;
    }

    // 设置当前子进程的进程表项索引,保存当前进程标识在进程表中的偏移量到全局变量上。
    ngx_process_slot = s;

    pid = fork();

    switch (pid)
    {
        case -1:
            //ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno, "fork() failed while spawning \"%s\"", name); ngx_close_channel(ngx_processes[s].channel, cycle->log);
            return NGX_INVALID_PID;

        case 0:
            // pid == 0 ,chaild process, 设置当前子进程的进程id
            //ngx_pid = ngx_getpid();
            // 子进程运行执行函数
            proc(cycle, data);
            break;

        default:
            //pid > 0 parent process
            break;
    }

    // 设置一些进程表项字段
    ngx_processes[s].pid = pid;
    ngx_processes[s].exited = 0;

    if (respawn >= 0)
    {
        // 对于替换进程ngx_processes[respawn]，不用设置其他进程表项字段了
        return pid;
    }

    // 设置其他的进程表项字段

    ngx_processes[s].proc = proc;
    ngx_processes[s].data = data;
    ngx_processes[s].exiting = 0;

    if (ngx_last_process == s)
    {
        ngx_last_process++;
    }

    PRINT_STACK_OUT("out\n");
    return pid;
}

