#ifndef _NGX_HTTP_CONF_FILE_H_INCLUDED_
#define _NGX_HTTP_CONF_FILE_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

#define NGX_CORE_MODULE 0x45524F43 /* "CORE" */

#define NGX_CONF_OK       NULL
#define NGX_CONF_ERROR       (void *) -1

struct ngx_command_s
{
    ngx_str_t name;
    ngx_uint_t type;
    char *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
    ngx_uint_t conf;
    ngx_uint_t offset;
    void *post;
};

#define NGX_MODULE_V1 0, 0, 0, 0, 0, 0, 1
#define NGX_MODULE_V1_PADDING 0, 0, 0, 0, 0, 0, 0, 0

struct ngx_module_s
{
    ngx_uint_t ctx_index;
    ngx_uint_t index;

    ngx_uint_t spare0;
    ngx_uint_t spare1;
    ngx_uint_t spare2;
    ngx_uint_t spare3;

    ngx_uint_t version;

    void *ctx; //ctx是模块的上下文，不同种类的模块有不同的上下文，四类模块就有四种模块上下文，实现为四个不同的结构体，所以ctx是void *。这是一个很重要的字段
    ngx_command_t *commands;
    ngx_uint_t type;

    // 初始化master,回调函数
    ngx_int_t (*init_master)(ngx_log_t *log);
};

typedef struct
{
    ngx_str_t name;
    void *(*create_conf)(ngx_cycle_t *cycle);
    char *(*init_conf)(ngx_cycle_t *cycle, void *conf);
} ngx_core_module_t;

typedef char *(*ngx_conf_handler_pt) (ngx_conf_t *cf, ngx_command_t *dummy, void *conf);

struct ngx_conf_s {
	char *name;
	//ngx_array_t *args;

	ngx_cycle_t *cycle;
	//ngx_pool_t *pool;
	//ngx_pool_t *temp_pool;
	//ngx_conf_file_t *conf_file;
	ngx_log_t log;

	void *ctx;
	ngx_uint_t module_type;
	ngx_uint_t cmd_type;

	ngx_conf_handler_pt handler;
	char *handler_conf;
};

typedef char *(*ngx_conf_post_handler_pt) (ngx_conf_t *cf, void *data, void *conf);


extern ngx_uint_t ngx_max_module;
extern ngx_module_t *ngx_modules[];

#endif // _NGX_HTTP_CONF_FILE_H_INCLUDED_

