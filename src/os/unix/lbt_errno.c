/*
 * Copyright (C) socho
 */
#include <lbt_config.h>
#include <lbt_core.h>

/**
 * ��Ҫ��ʼ��ϵͳ�д����Ŷ�Ӧ������������������ʼ���н��ж�Ӧ�ĺô��ǣ������ִ���
 * ������ȥ����strerror()��������ȡ����ԭ�򣬶�ֱ�ӿ��Ը��ݴ������ҵ���Ӧ�Ĵ���ԭ��
 * �������ַ�����ַ�������������ʱ��ִ��Ч�ʡ�
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