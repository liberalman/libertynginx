#ifndef _LBT_CYCLE_H_INCLUDED_
#define _LBT_CYCLE_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

#ifndef LBT_CYCLE_POOL_SIZE
#define LBT_CYCLE_POOL_SIZE     16384
#endif

/** lbt_cycle_t��һ����Ҫ�����ݽṹ������һ������Ҫ��������������һЩȫ�����ʵ����ݣ�������ϵͳ�ڶ��ᱻʹ�õ�*/
struct lbt_cycle_s
{
    void ** **conf_ctx; //��������������(������ģ��)
    lbt_pool_t *pool;

    lbt_log_t *log;
    lbt_log_t *new_log;

    lbt_connection_t **files; //�����ļ�
    lbt_uint_t files_n; /**< ���ļ����� */

    lbt_connection_t *connections; //����
    lbt_uint_t connection_n; /**< ���Ӹ���*/

    lbt_connection_t *free_connections; //��������
    lbt_uint_t free_connection_n; //�������Ӹ���

    lbt_event_t *read_events; //���¼�
    lbt_event_t *write_events; //д�¼�

    lbt_cycle_t *old_cycle; //old cycleָ��

    lbt_str_t conf_file; //�����ļ�
    lbt_str_t conf_param; //���ò���
    lbt_str_t conf_prefix; //����ǰ׺
    lbt_str_t prefix; //ǰ׺
    lbt_str_t lock_file; //���ļ�
    lbt_str_t hostname; //������
};

lbt_cycle_t *lbt_init_cycle(lbt_cycle_t *old_cycle);

#endif //  _LBT_CYCLE_H_INCLUDED_

