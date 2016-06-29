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

static lbt_uint_t   lbt_show_help; /**< 是否显示帮助 */
static lbt_uint_t   lbt_show_version; /**< 是否显示版本 */
lbt_uint_t lbt_max_module; /**< 模块最大数量 */

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

  // 调试模式初始化
  lbt_debug_init();

  // 初始化自定义的错误编号函数
  if (LBT_SUCCESS != lbt_strerror_init()){
      return LBT_ERROR;
  }

  // 获取启动参数
  if (LBT_SUCCESS != lbt_get_options(argc, argv)){
      return LBT_ERROR;
  }
  
  // 显示版本号，帮助信息等
  if (lbt_show_version) {
      lbt_log_stderr(0, "version:" LIBERTY_VER "\n");
  }
  if (lbt_show_help) {
  }

  // 初始化时间控件
  lbt_time_init();

  // 初始化正则表达式
  //ngx_regex_init();

  // 载入模块
  lbt_max_module = 0;
  for (i = 0; lbt_modules[i]; i++)
  {
	lbt_modules[i]->index = lbt_max_module++;
	//DEBUG("%d\n", lbt_modules[i]->index);
  }

  /* 
   * 系统初始化，这里将发生配置文件解析，模块上下文注册钩子调用，模块初始化
   * module 　 : 模块
   * commands  : 模块指令集，负责解析配置文件的选项，一个指令对应一个配置选项
   * conf      : 模块配置结构体，指令解析后的值就是存储在这个里面，每个模块都有自已的一个conf 
   * ctx       : 模块上下文，有四种，core, event, http, mail，有注册钩子功能。比如create conf, init conf 
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
 * 获取启动参数
 * @param argc
 * @param argv
 * @return
 */
static lbt_int_t lbt_get_options(int argc, char *const *argv) {
    u_char   *p;
    lbt_int_t   i;
    for ( i = 1; i < argc; i++){
        p = (u_char *) argv[i];
        if('-' != *p++){ // 不是'-'号的参数报错，然后指针后移到'-'后的单个字符上
            lbt_log_stderr(0, "参数不可用：%c\n", argv[i]);
            DEBUG("参数不可用：%c\n", argv[i]);
            return LBT_ERROR;
        }
        while(*p){ // 当前字符是合法参数则下面就解析它，然后指针后移
            switch(*p++){
            case 'h':
                    lbt_show_version = 1;
                    lbt_show_help = 1;
                    break;
            default:
                lbt_log_stderr(0, "参数不可用：%c\n", *(p-1));
                DEBUG("参数不可用：%c\n", *(p-1));
                return LBT_ERROR;
            }
        }
    }
    return LBT_SUCCESS;
}