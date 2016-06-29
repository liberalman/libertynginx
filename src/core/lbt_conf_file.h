#ifndef _LBT_HTTP_CONF_FILE_H_INCLUDED_
#define _LBT_HTTP_CONF_FILE_H_INCLUDED_

#include <lbt_config.h>
#include <lbt_core.h>

#define LBT_CORE_MODULE 0x45524F43 /* "CORE" */

#define LBT_CONF_OK       NULL
#define LBT_CONF_ERROR       (void *) -1

/**
 * 模块的指令
 */
struct lbt_command_s
{
    lbt_str_t name;
    lbt_uint_t type;
    char *(*set)(lbt_conf_t *cf, lbt_command_t *cmd, void *conf);
    lbt_uint_t conf;
    lbt_uint_t offset;
    void *post;
};

#define lbt_MODULE_V1 0, 0, 0, 0, 0, 0, 1
#define lbt_MODULE_V1_PADDING 0, 0, 0, 0, 0, 0, 0, 0

struct lbt_module_s
{
    lbt_uint_t ctx_index;
    lbt_uint_t index;

    lbt_uint_t spare0;
    lbt_uint_t spare1;
    lbt_uint_t spare2;
    lbt_uint_t spare3;

    lbt_uint_t version;

    void *ctx; //ctx是模块的上下文，不同种类的模块有不同的上下文，四类模块就有四种模块上下文，实现为四个不同的结构体，所以ctx是void *。这是一个很重要的字段
    lbt_command_t *commands;
    lbt_uint_t type;

    // 初始化master,回调函数
    lbt_int_t (*init_master)(lbt_log_t *log);
};

typedef struct
{
    lbt_str_t name;
    void *(*create_conf)(lbt_cycle_t *cycle);
    char *(*init_conf)(lbt_cycle_t *cycle, void *conf);
} lbt_core_module_t;

typedef char *(*lbt_conf_handler_pt) (lbt_conf_t *cf, lbt_command_t *dummy, void *conf);

struct lbt_conf_s {
	char *name;
	//lbt_array_t *args;

	lbt_cycle_t *cycle;
	//lbt_pool_t *pool;
	//lbt_pool_t *temp_pool;
	//lbt_conf_file_t *conf_file;
	lbt_log_t log;

	void *ctx;
	lbt_uint_t module_type;
	lbt_uint_t cmd_type;

	lbt_conf_handler_pt handler;
	char *handler_conf;
};

typedef char *(*lbt_conf_post_handler_pt) (lbt_conf_t *cf, void *data, void *conf);


extern lbt_uint_t lbt_max_module;
extern lbt_module_t *lbt_modules[];

#endif // _LBT_HTTP_CONF_FILE_H_INCLUDED_

