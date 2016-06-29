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
   * 系统初始化，这里将发生配置文件解析，模块上下文注册钩子调用，模块初始化
   * module 　 : 模块
   * commands  : 模块指令集，负责解析配置文件的选项，一个指令对应一个配置选项
   * conf      : 模块配置结构体，指令解析后的值就是存储在这个里面，每个模块都有自已的一个conf 
   * ctx       : 模块上下文，有四种，core, event, http, mail，有注册钩子功能。比如create conf, init conf 
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

