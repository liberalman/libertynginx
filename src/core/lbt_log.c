/*
 * Copyright (C) socho
 */
#include <lbt_config.h>
#include <lbt_core.h>

void lbt_log_stderr(lbt_err_t err, const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    printf(fmt, args);
    va_end(args);
}

