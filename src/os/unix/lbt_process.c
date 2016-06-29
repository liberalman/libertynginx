

#include <lbt_config.h>
#include <lbt_core.h>
#include <lbt_channel.h>

lbt_int_t           lbt_process_slot; //offset of current process in processes table.
lbt_socket_t     lbt_channel;
lbt_process_t   lbt_processes[LBT_MAX_PROCESSES]; // processes table.
lbt_int_t           lbt_last_process = 0; // the last one of processes table.

// proc是子进程的执行函数，data是其参数，name是子进程的名字
lbt_pid_t lbt_spawn_process(lbt_cycle_t *cycle, lbt_spawn_proc_pt proc, void *data, char *name, lbt_int_t respawn)
{
    PRINT_STACK_IN("in\n");
    u_long on;
    lbt_pid_t pid;
    lbt_int_t s; // 将要创建的子进程在进程表中的位置

    if (respawn >= 0)
    {
        // 替换进程lbt_processes[respawn]，可安全重用该进程表项
        s = respawn;
    }
    else
    {
        for (s = 0; s < lbt_last_process; s++)
        {
            if (-1 == lbt_processes[s].pid)
            {
                // 先找到一个被回收的进程表项
                break;
            }
        }

        if (LBT_MAX_PROCESSES == s)
        {
            // 进程表已满，直接退出。
            //lbt_log_error(LBT_LOG_ALERT, cycle->log, 0, "no more than %d processes can be spawned", LBT_MAX_PROCESSES);
            return LBT_INVALID_PID;
        }
    }

    if ( LBT_PROCESS_DETACHED != respawn)
    {
        // 不是分离的子进程
    }
    else
    {
        // 分离的子进程
        //初始化进程通信的socket为-1
        lbt_processes[s].channel[0] = -1;
        lbt_processes[s].channel[1] = -1;
    }

    // 设置当前子进程的进程表项索引,保存当前进程标识在进程表中的偏移量到全局变量上。
    lbt_process_slot = s;

    pid = fork();

    switch (pid)
    {
        case -1:
            //lbt_log_error(LBT_LOG_ALERT, cycle->log, lbt_errno, "fork() failed while spawning \"%s\"", name); lbt_close_channel(lbt_processes[s].channel, cycle->log);
            return LBT_INVALID_PID;

        case 0:
            // pid == 0 ,chaild process, 设置当前子进程的进程id
            //lbt_pid = lbt_getpid();
            // 子进程运行执行函数
            proc(cycle, data);
            break;

        default:
            //pid > 0 parent process
            break;
    }

    // 设置一些进程表项字段
    lbt_processes[s].pid = pid;
    lbt_processes[s].exited = 0;

    if (respawn >= 0)
    {
        // 对于替换进程lbt_processes[respawn]，不用设置其他进程表项字段了
        return pid;
    }

    // 设置其他的进程表项字段

    lbt_processes[s].proc = proc;
    lbt_processes[s].data = data;
    lbt_processes[s].exiting = 0;

    if (lbt_last_process == s)
    {
        lbt_last_process++;
    }

    PRINT_STACK_OUT("out\n");
    return pid;
}

