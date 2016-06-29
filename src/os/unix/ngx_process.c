

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_channel.h>

ngx_int_t        ngx_process_slot; //offset of current process in processes table.
ngx_socket_t     ngx_channel;
ngx_process_t    ngx_processes[NGX_MAX_PROCESSES]; // processes table.
ngx_int_t ngx_last_process = 0; // the last one of processes table.

// proc���ӽ��̵�ִ�к�����data���������name���ӽ��̵�����
ngx_pid_t ngx_spawn_process(ngx_cycle_t *cycle, ngx_spawn_proc_pt proc, void *data, char *name, ngx_int_t respawn)
{
    PRINT_STACK_IN("in\n");
    u_long on;
    ngx_pid_t pid;
    ngx_int_t s; // ��Ҫ�������ӽ����ڽ��̱��е�λ��

    if (respawn >= 0)
    {
        // �滻����ngx_processes[respawn]���ɰ�ȫ���øý��̱���
        s = respawn;
    }
    else
    {
        for (s = 0; s < ngx_last_process; s++)
        {
            if (-1 == ngx_processes[s].pid)
            {
                // ���ҵ�һ�������յĽ��̱���
                break;
            }
        }

        if (NGX_MAX_PROCESSES == s)
        {
            // ���̱�������ֱ���˳���
            //ngx_log_error(NGX_LOG_ALERT, cycle->log, 0, "no more than %d processes can be spawned", NGX_MAX_PROCESSES);
            return NGX_INVALID_PID;
        }
    }

    if ( NGX_PROCESS_DETACHED != respawn)
    {
        // ���Ƿ�����ӽ���
    }
    else
    {
        // ������ӽ���
        //��ʼ������ͨ�ŵ�socketΪ-1
        ngx_processes[s].channel[0] = -1;
        ngx_processes[s].channel[1] = -1;
    }

    // ���õ�ǰ�ӽ��̵Ľ��̱�������,���浱ǰ���̱�ʶ�ڽ��̱��е�ƫ������ȫ�ֱ����ϡ�
    ngx_process_slot = s;

    pid = fork();

    switch (pid)
    {
        case -1:
            //ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno, "fork() failed while spawning \"%s\"", name); ngx_close_channel(ngx_processes[s].channel, cycle->log);
            return NGX_INVALID_PID;

        case 0:
            // pid == 0 ,chaild process, ���õ�ǰ�ӽ��̵Ľ���id
            //ngx_pid = ngx_getpid();
            // �ӽ�������ִ�к���
            proc(cycle, data);
            break;

        default:
            //pid > 0 parent process
            break;
    }

    // ����һЩ���̱����ֶ�
    ngx_processes[s].pid = pid;
    ngx_processes[s].exited = 0;

    if (respawn >= 0)
    {
        // �����滻����ngx_processes[respawn]�����������������̱����ֶ���
        return pid;
    }

    // ���������Ľ��̱����ֶ�

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

