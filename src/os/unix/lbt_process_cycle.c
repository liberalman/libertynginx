

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

    //master����һЩ��Ҫ������ź�
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

    //����worker����
    //lbt_start_worker_processes(cycle, ccf->worker_processes, LBT_PROCESS_RESPAWN);
    lbt_start_worker_processes(cycle, 1, LBT_PROCESS_RESPAWN);
    PRINT_STACK_OUT("\n");
}

//��������worker�ӽ��̵ĺ�����lbt_start_worker_processes
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
        // �����ӽ���
        lbt_spawn_process(cycle, lbt_worker_process_cycle, NULL, "worker process", type);

        ch.slot = lbt_process_slot;
        ch.pid = lbt_processes[lbt_process_slot].pid;
        ch.fd = lbt_processes[lbt_process_slot].channel[0];

        //lbt_pass_open_channel(cycle, &ch);
    }

    PRINT_STACK_OUT("\n");
}

// worker�ӽ��̵�ִ�к�����������������ҵ����ġ�
static void lbt_worker_process_cycle(lbt_cycle_t *cycle, void *data)
{
    PRINT_STACK_IN("\n");
    lbt_uint_t i;
    lbt_connection_t *c;

    lbt_process = LBT_PROCESS_WORKER;

//ȫ���Ե����ã�����ȫ�ֵ�������Ϣ����ִ�л��������ȼ������ơ�setgid��setuid���źų�ʼ���ȣ�
	lbt_worker_process_init(cycle, 1);

    for (;;)
    {
        if (lbt_exiting)
        {
            // �˳�״̬�����ã��ر���������
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
            // // �յ�LBT_CMD_TERMINATE����
            //lbt_log_error(LBT_LOG_NOTICE, cycle->log, 0, "exiting");
            // ���������˳������������ģ��Ĺ���exit_process
            lbt_worker_process_exit(cycle);
        }

        if (lbt_quit)
        {
            // �յ�LBT_CMD_QUIT����
            lbt_quit = 0;
        }

        if (lbt_reopen)
        {
            // �յ�LBT_CMD_REOPEN������´�log
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

