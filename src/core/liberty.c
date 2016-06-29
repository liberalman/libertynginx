/*
 * Copyright (C) socho
 */
#include <lbt_config.h>
#include <lbt_core.h>
#include <liberty.h>

int stack_ = -1;

lbt_module_t  lbt_core_module = {
  //  lbt_MODULE_V1,
  //  &lbt_core_module_ctx,                  /* module context */
  //  lbt_core_commands,                     /* module directives */
  //  lbt_CORE_MODULE,                       /* module type */
  NULL,                                  /* init master */
  NULL,                                  /* init module */
  NULL,                                  /* init process */
  NULL,                                  /* init thread */
  NULL,                                  /* exit thread */
  NULL,                                  /* exit process */
  NULL,                                  /* exit master */
  //  lbt_MODULE_V1_PADDING
};

static lbt_uint_t   lbt_show_help; /**< �Ƿ���ʾ���� */
static lbt_uint_t   lbt_show_version; /**< �Ƿ���ʾ�汾 */
lbt_uint_t lbt_max_module; /**< ģ��������� */

static lbt_int_t lbt_get_options(int argc, char *const *argv);

////////////////////////////////////
// test
void cycle_info(lbt_cycle_t *cycle);
////////////////////////////////////

int main(int argc, char *argv[])
{
  PRINT_STACK_IN("\n");
  lbt_int_t i = 0;
  lbt_cycle_t *cycle, init_cycle;

  // ����ģʽ��ʼ��
  lbt_debug_init();

  // ��ʼ���Զ���Ĵ����ź���
  if (LBT_SUCCESS != lbt_strerror_init()){
      return LBT_ERROR;
  }

  // ��ȡ��������
  if (LBT_SUCCESS != lbt_get_options(argc, argv)){
      return LBT_ERROR;
  }
  
  // ��ʾ�汾�ţ�������Ϣ��
  if (lbt_show_version) {
      lbt_log_stderr(0, "version:" LIBERTY_VER "\n");
  }
  if (lbt_show_help) {
  }

  // ��ʼ��ʱ��ؼ�
  lbt_time_init();

  // ��ʼ��������ʽ
  //ngx_regex_init();

  // ����ģ��
  lbt_max_module = 0;
  for (i = 0; lbt_modules[i]; i++)
  {
	lbt_modules[i]->index = lbt_max_module++;
	//DEBUG("%d\n", lbt_modules[i]->index);
  }

  /* 
   * ϵͳ��ʼ�������ｫ���������ļ�������ģ��������ע�ṳ�ӵ��ã�ģ���ʼ��
   * module �� : ģ��
   * commands  : ģ��ָ���������������ļ���ѡ�һ��ָ���Ӧһ������ѡ��
   * conf      : ģ�����ýṹ�壬ָ��������ֵ���Ǵ洢��������棬ÿ��ģ�鶼�����ѵ�һ��conf 
   * ctx       : ģ�������ģ������֣�core, event, http, mail����ע�ṳ�ӹ��ܡ�����create conf, init conf 
   */
  cycle = lbt_init_cycle(&init_cycle);
  if (NULL == cycle)
  {
	DEBUG("lbt_init_cycle return NULL\n");
	return LBT_ERROR;
  }
  //cycle_info(cycle);

  lbt_master_process_cycle(cycle);

  PRINT_STACK_OUT("\n");
  return 0;
}


//////////////////////// test function////////////////////////////////
void cycle_info(lbt_cycle_t *cycle)
{
  DEBUG("\ncycle info:\n"
	  "\tconf_ctx %8X\n"
	  "\tfree_connection_n %8X\n",
	  cycle->conf_ctx,
	  cycle->free_connection_n);
}

/**
 * ��ȡ��������
 * @param argc
 * @param argv
 * @return
 */
static lbt_int_t lbt_get_options(int argc, char *const *argv) {
    u_char   *p;
    lbt_int_t   i;
    for ( i = 1; i < argc; i++){
        p = (u_char *) argv[i];
        if('-' != *p++){ // ����'-'�ŵĲ�������Ȼ��ָ����Ƶ�'-'��ĵ����ַ���
            lbt_log_stderr(0, "���������ã�%c\n", argv[i]);
            DEBUG("���������ã�%c\n", argv[i]);
            return LBT_ERROR;
        }
        while(*p){ // ��ǰ�ַ��ǺϷ�����������ͽ�������Ȼ��ָ�����
            switch(*p++){
            case 'h':
                    lbt_show_version = 1;
                    lbt_show_help = 1;
                    break;
            default:
                lbt_log_stderr(0, "���������ã�%c\n", *(p-1));
                DEBUG("���������ã�%c\n", *(p-1));
                return LBT_ERROR;
            }
        }
    }
    return LBT_SUCCESS;
}