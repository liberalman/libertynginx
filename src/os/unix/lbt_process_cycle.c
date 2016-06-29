

#include <lbt_config.h>
#include <lbt_core.h>
#include <lbt_channel.h>

static void lbt_start_worker_processes(lbt_cycle_t *cycle, lbt_int_t n, lbt_int_t type);
static void lbt_worker_process_cycle(lbt_cycle_t *cycle, void *data); // process function
static void lbt_worker_process_exit(lbt_cycle_t *cycle);
static void lbt_worker_process_init(lbt_cycle_t *cycle, lbt_uint_t priority);

lbt_uint_t lbt_process;
lbt_uint_t lbt_exiting;

sig_atomic_t lbt_quit;
sig_atomic_t lbt_reopen;
sig_atomic_t lbt_terminate;

void lbt_master_process_cycle(lbt_cycle_t *cycle)
{
    PRINT_STACK_IN("\n");
    lbt_int_t i;
    sigset_t set;

    //master设置一些需要处理的信号
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigaddset(&set, SIGALRM);
    sigaddset(&set, SIGIO);
    sigaddset(&set, SIGINT);

    //sigaddset(&set, lbt_signal_value(LBT_RECONFIGURE_SIGNAL));
    //sigaddset(&set, lbt_signal_value(LBT_REOPEN_SIGNAL));
    //sigaddset(&set, lbt_signal_value(LBT_NOACCEPT_SIGNAL));
    //sigaddset(&set, lbt_signal_value(LBT_TERMINATE_SIGNAL));
    //sigaddset(&set, lbt_signal_value(LBT_SHUTDOWN_SIGNAL));
    //sigaddset(&set, lbt_signal_value(LBT_CHANGEBIN_SIGNAL));
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1)
    {
        //lbt_log_error(lbt_LOG_ALERT, cycle->log, lbt_errno, "sigprocmask() failed");
    }

    sigemptyset(&set);

    //启动worker进程
    //lbt_start_worker_processes(cycle, ccf->worker_processes, LBT_PROCESS_RESPAWN);
    lbt_start_worker_processes(cycle, 1, LBT_PROCESS_RESPAWN);
    PRINT_STACK_OUT("\n");
}

//真正创建worker子进程的函数是lbt_start_worker_processes
static void lbt_start_worker_processes(lbt_cycle_t *cycle, lbt_int_t n, lbt_int_t type)
{
    PRINT_STACK_IN("\n");
    lbt_int_t i = 0;
    lbt_channel_t ch;

    //lbt_log_error(LBT_LOG_NOTICE, cycle->log, 0, "start worker processes");

    ch.command = LBT_CMD_OPEN_CHANNEL;

    for (i = 0; i < n; i++)
    {
        //cpu_affinity = lbt_get_cpu_affinity(i);
        // 创建子进程
        lbt_spawn_process(cycle, lbt_worker_process_cycle, NULL, "worker process", type);

        ch.slot = lbt_process_slot;
        ch.pid = lbt_processes[lbt_process_slot].pid;
        ch.fd = lbt_processes[lbt_process_slot].channel[0];

        //lbt_pass_open_channel(cycle, &ch);
    }

    PRINT_STACK_OUT("\n");
}

// worker子进程的执行函数，这里是真正做业务处理的。
static void lbt_worker_process_cycle(lbt_cycle_t *cycle, void *data)
{
    PRINT_STACK_IN("\n");
    lbt_uint_t i;
    lbt_connection_t *c;

    lbt_process = LBT_PROCESS_WORKER;

//全局性的设置，根据全局的配置信息设置执行环境、优先级、限制、setgid、setuid、信号初始化等；
	lbt_worker_process_init(cycle, 1);

    for (;;)
    {
        if (lbt_exiting)
        {
            // 退出状态已设置，关闭所有连接
            c = cycle->connections;

            for (i = 0; i < cycle->connection_n; i++)
            {
                /* THREAD: lock */
                if (c[i].fd != -1 && c[i].idle)
                {
                    c[i].close = 1;
                    //c[i].read->handler(c[i].read);
                }
            }
        }

        if (lbt_terminate)
        {
            // // 收到LBT_CMD_TERMINATE命令
            //lbt_log_error(LBT_LOG_NOTICE, cycle->log, 0, "exiting");
            // 清理后进程退出，会调用所有模块的钩子exit_process
            lbt_worker_process_exit(cycle);
        }

        if (lbt_quit)
        {
            // 收到LBT_CMD_QUIT命令
            lbt_quit = 0;
        }

        if (lbt_reopen)
        {
            // 收到LBT_CMD_REOPEN命令，重新打开log
            lbt_reopen = 0;
            //lbt_log_error(LBT_LOG_NOTICE, cycle->log, 0, "reopening logs");
            //lbt_reopen_files(cycle, -1);
        }
    }

    PRINT_STACK_OUT("\n");
}

void lbt_worker_process_exit(lbt_cycle_t *cycle)
{
}

static void lbt_worker_process_init(lbt_cycle_t *cycle, lbt_uint_t priority)
{

}

