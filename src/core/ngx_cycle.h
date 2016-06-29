#ifndef _NGX_CYCLE_H_INCLUDED_
#define _NGX_CYCLE_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

#ifndef NGX_CYCLE_POOL_SIZE
#define NGX_CYCLE_POOL_SIZE     16384
#endif

/** ngx_cycle_t��һ����Ҫ�����ݽṹ������һ������Ҫ��������������һЩȫ�����ʵ����ݣ�������ϵͳ�ڶ��ᱻʹ�õ�*/
struct ngx_cycle_s
{
    void ** **conf_ctx; //��������������(������ģ��)
    ngx_pool_t *pool;

    ngx_log_t *log;
    ngx_log_t *new_log;

    ngx_connection_t **files; //�����ļ�
    ngx_uint_t files_n; /**< ���ļ����� */

    ngx_connection_t *connections; //����
    ngx_uint_t connection_n; /**< ���Ӹ���*/

    ngx_connection_t *free_connections; //��������
    ngx_uint_t free_connection_n; //�������Ӹ���

    ngx_event_t *read_events; //���¼�
    ngx_event_t *write_events; //д�¼�

    ngx_cycle_t *old_cycle; //old cycleָ��

    ngx_str_t conf_file; //�����ļ�
    ngx_str_t conf_param; //���ò���
    ngx_str_t conf_prefix; //����ǰ׺
    ngx_str_t prefix; //ǰ׺
    ngx_str_t lock_file; //���ļ�
    ngx_str_t hostname; //������
};

ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle);

#endif //  _NGX_CYCLE_H_INCLUDED_

