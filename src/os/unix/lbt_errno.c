/*
 * Copyright (C) socho
 */
#include <lbt_config.h>
#include <lbt_core.h>

/**
 * 主要初始化系统中错误编号对应的文字描述，这样初始化中进行对应的好处是，当出现错误，
 * 不用再去调用strerror()函数来获取错误原因，而直接可以根据错误编号找到对应的错误原因
 * 描述的字符串地址，可以提高运行时的执行效率。
 */
lbt_uint_t lbt_strerror_init(void){
    char         *msg;
    u_char     *p;
    size_t       len;
    lbt_err_t   err;
    PRINT_STACK_IN("\n");
    PRINT_STACK_OUT("\n");
    return LBT_SUCCESS;
}