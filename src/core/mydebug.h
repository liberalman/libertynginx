#ifndef _MYDEBUG_H_
#define _MYDEBUG_H_

extern int stack_;

#ifdef _DEBUG
#define DEBUG(format, argc...) printf("[%s:%d][%s()]" format , __FILE__, __LINE__, __FUNCTION__, ##argc)
#else
#define DEBUG(format, argc...)
#endif

#ifdef _PRINT_STACK
#define PRINT_STACK_IN(format, argc...) \
    ++stack_; \
    printf("#in #%d[%s()\t\t:%s:%d]" format , stack_, __FUNCTION__, __FILE__, __LINE__, ##argc);
#define PRINT_STACK_OUT(format, argc...)  \
    printf("#out#%d[%s()\t\t:%s:%d]" format , stack_, __FUNCTION__, __FILE__, __LINE__, ##argc); \
    stack_--;
#else
#define PRINT_STACK_OUT(format, argc...)
#define PRINT_STACK_IN(format, argc...)
#endif

#endif // _MYDEBUG_H_

