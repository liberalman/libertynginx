

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_channel.h>

static void ngx_start_worker_processes(ngx_cycle_t *cycle, ngx_int_t n, ngx_int_t type);
static void ngx_worker_process_cycle(ngx_cycle_t *cycle, void *data); // process function
static void ngx_worker_process_exit(ngx_cycle_t *cycle);
static void ngx_worker_process_init(ngx_cycle_t *cycle, ngx_uint_t priority);

ngx_uint_t ngx_process;
ngx_uint_t ngx_exiting;

sig_atomic_t ngx_quit;
sig_atomic_t ngx_reopen;
sig_atomic_t ngx_terminate;

void ngx_master_process_cycle(ngx_cycle_t *cycle)
{
    PRINT_STACK_IN("in\n");
    ngx_int_t i;
    sigset_t set;

    //master设置一些需要处理的信号
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigaddset(&set, SIGALRM);
    sigaddset(&set, SIGIO);
    sigaddset(&set, SIGINT);

    //sigaddset(&set, ngx_signal_value(NGX_RECONFIGURE_SIGNAL));
    //sigaddset(&set, ngx_signal_value(NGX_REOPEN_SIGNAL));
    //sigaddset(&set, ngx_signal_value(NGX_NOACCEPT_SIGNAL));
    //sigaddset(&set, ngx_signal_value(NGX_TERMINATE_SIGNAL));
    //sigaddset(&set, ngx_signal_value(NGX_SHUTDOWN_SIGNAL));
    //sigaddset(&set, ngx_signal_value(NGX_CHANGEBIN_SIGNAL));
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1)
    {
        //ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno, "sigprocmask() failed");
    }

    sigemptyset(&set);

    //启动worker进程
    //ngx_start_worker_processes(cycle, ccf->worker_processes, NGX_PROCESS_RESPAWN);
    ngx_start_worker_processes(cycle, 1, NGX_PROCESS_RESPAWN);
    PRINT_STACK_OUT("out\n");
}

//真正创建worker子进程的函数是ngx_start_worker_processes
static void ngx_start_worker_processes(ngx_cycle_t *cycle, ngx_int_t n, ngx_int_t type)
{
    PRINT_STACK_IN("in\n");
    ngx_int_t i = 0;
    ngx_channel_t ch;

    //ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "start worker processes");

    ch.command = NGX_CMD_OPEN_CHANNEL;

    for (i = 0; i < n; i++)
    {
        //cpu_affinity = ngx_get_cpu_affinity(i);

        ngx_spawn_process(cycle, ngx_worker_process_cycle, NULL, "worker process", type);

        ch.slot = ngx_process_slot;
        ch.pid = ngx_processes[ngx_process_slot].pid;
        ch.fd = ngx_processes[ngx_process_slot].channel[0];

        //ngx_pass_open_channel(cycle, &ch);
    }

    PRINT_STACK_OUT("out\n");
}

// worker子进程的执行函数，这里是真正做业务处理的。
static void ngx_worker_process_cycle(ngx_cycle_t *cycle, void *data)
{
    PRINT_STACK_IN("in\n");
    ngx_uint_t i;
    ngx_connection_t *c;

    ngx_process = NGX_PROCESS_WORKER;

//全局性的设置，根据全局的配置信息设置执行环境、优先级、限制、setgid、setuid、信号初始化等；
	ngx_worker_process_init(cycle, 1);

    for (;;)
    {
        if (ngx_exiting)
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

        if (ngx_terminate)
        {
            // // 收到NGX_CMD_TERMINATE命令
            //ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "exiting");
            // 清理后进程退出，会调用所有模块的钩子exit_process
            ngx_worker_process_exit(cycle);
        }

        if (ngx_quit)
        {
            // 收到NGX_CMD_QUIT命令
            ngx_quit = 0;
        }

        if (ngx_reopen)
        {
            // 收到NGX_CMD_REOPEN命令，重新打开log
            ngx_reopen = 0;
            //ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "reopening logs");
            //ngx_reopen_files(cycle, -1);
        }
    }

    PRINT_STACK_OUT("out\n");
}

void ngx_worker_process_exit(ngx_cycle_t *cycle)
{
}

static void ngx_worker_process_init(ngx_cycle_t *cycle, ngx_uint_t priority)
{

}

