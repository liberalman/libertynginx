/*
 * Copyright (C) socho
 */
#include <ngx_config.h>
#include <ngx_core.h>
//#include <nginx.h>

int stack_ = -1;

ngx_module_t  ngx_core_module = {
  //  NGX_MODULE_V1,
  //  &ngx_core_module_ctx,                  /* module context */
  //  ngx_core_commands,                     /* module directives */
  //  NGX_CORE_MODULE,                       /* module type */
  NULL,                                  /* init master */
  NULL,                                  /* init module */
  NULL,                                  /* init process */
  NULL,                                  /* init thread */
  NULL,                                  /* exit thread */
  NULL,                                  /* exit process */
  NULL,                                  /* exit master */
  //  NGX_MODULE_V1_PADDING
};

ngx_uint_t ngx_max_module;

////////////////////////////////////
// test
void cycle_info(ngx_cycle_t *cycle);
////////////////////////////////////

int main(int argc, char *argv[])
{
  PRINT_STACK_IN("in\n");
  ngx_int_t i = 0;
  ngx_cycle_t *cycle, init_cycle;

  ngx_max_module = 0;
  for (i = 0; ngx_modules[i]; i++)
  {
	ngx_modules[i]->index = ngx_max_module++;
	//DEBUG("%d\n", ngx_modules[i]->index);
  }

  /* 
   * ϵͳ��ʼ�������ｫ���������ļ�������ģ��������ע�ṳ�ӵ��ã�ģ���ʼ��
   * module �� : ģ��
   * commands  : ģ��ָ���������������ļ���ѡ�һ��ָ���Ӧһ������ѡ��
   * conf      : ģ�����ýṹ�壬ָ��������ֵ���Ǵ洢��������棬ÿ��ģ�鶼�����ѵ�һ��conf 
   * ctx       : ģ�������ģ������֣�core, event, http, mail����ע�ṳ�ӹ��ܡ�����create conf, init conf 
   */
  cycle = ngx_init_cycle(&init_cycle);
  if (NULL == cycle)
  {
	DEBUG("ngx_init_cycle return NULL\n");
	return 1;
  }
  //cycle_info(cycle);

  ngx_master_process_cycle(cycle);

  PRINT_STACK_OUT("out\n");
  return 0;
}


//////////////////////// test function////////////////////////////////
void cycle_info(ngx_cycle_t *cycle)
{
  DEBUG("\ncycle info:\n"
	  "\tconf_ctx %8X\n"
	  "\tfree_connection_n %8X\n",
	  cycle->conf_ctx,
	  cycle->free_connection_n);
}

