
#include <ngx_config.h>
#include <ngx_core.h>

extern ngx_module_t ngx_core_module;

ngx_module_t *ngx_modules[] = {
  &ngx_core_module,
  NULL
};

