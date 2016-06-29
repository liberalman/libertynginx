

#include <lbt_config.h>
#include <lbt_core.h>
#include <lbt_channel.h>

lbt_int_t           lbt_process_slot; //offset of current process in processes table.
lbt_socket_t     lbt_channel;
lbt_process_t   lbt_processes[LBT_MAX_PROCESSES]; // processes table.
lbt_int_t           lbt_last_process = 0; // the last one of processes table.

// proc���ӽ��̵�ִ�к�����data���������name���ӽ��̵�����
lbt_pid_t lbt_spawn_process(lbt_cycle_t *cycle, lbt_spawn_proc_pt proc, void *data, char *name, lbt_int_t respawn)
{
    PRINT_STACK_IN("in\n");
    u_long on;
    lbt_pid_t pid;
    lbt_int_t s; // ��Ҫ�������ӽ����ڽ��̱��е�λ��

    if (respawn >= 0)
    {
        // �滻����lbt_processes[respawn]���ɰ�ȫ���øý��̱���
        s = respawn;
    }
    else
    {
        for (s = 0; s < lbt_last_process; s++)
        {
            if (-1 == lbt_processes[s].pid)
            {
                // ���ҵ�һ�������յĽ��̱���
                break;
            }
        }

        if (LBT_MAX_PROCESSES == s)
        {
            // ���̱�������ֱ���˳���
            //lbt_log_error(LBT_LOG_ALERT, cycle->log, 0, "no more than %d processes can be spawned", LBT_MAX_PROCESSES);
            return LBT_INVALID_PID;
        }
    }

    if ( LBT_PROCESS_DETACHED != respawn)
    {
        // ���Ƿ�����ӽ���
    }
    else
    {
        // ������ӽ���
        //��ʼ������ͨ�ŵ�socketΪ-1
        lbt_processes[s].channel[0] = -1;
        lbt_processes[s].channel[1] = -1;
    }

    // ���õ�ǰ�ӽ��̵Ľ��̱�������,���浱ǰ���̱�ʶ�ڽ��̱��е�ƫ������ȫ�ֱ����ϡ�
    lbt_process_slot = s;

    pid = fork();

    switch (pid)
    {
        case -1:
            //lbt_log_error(LBT_LOG_ALERT, cycle->log, lbt_errno, "fork() failed while spawning \"%s\"", name); lbt_close_channel(lbt_processes[s].channel, cycle->log);
            return LBT_INVALID_PID;

        case 0:
            // pid == 0 ,chaild process, ���õ�ǰ�ӽ��̵Ľ���id
            //lbt_pid = lbt_getpid();
            // �ӽ�������ִ�к���
            proc(cycle, data);
            break;

        default:
            //pid > 0 parent process
            break;
    }

    // ����һЩ���̱����ֶ�
    lbt_processes[s].pid = pid;
    lbt_processes[s].exited = 0;

    if (respawn >= 0)
    {
        // �����滻����lbt_processes[respawn]�����������������̱����ֶ���
        return pid;
    }

    // ���������Ľ��̱����ֶ�

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

