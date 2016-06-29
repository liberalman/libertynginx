CC = gcc
CFLAGS = -g -D_DEBUG -D_PRINT_STACK
LINK = $(CC)

ALL_INCS = -I src/core \
    -I src/objs
    
CORE_DEPS = src/core/nginx.h \
	src/core/ngx_config.h \
	src/core/ngx_core.h \
	src/core/ngx_cycle.h \
	src/core/ngx_palloc.h \
	src/core/ngx_buf.h \
	src/core/ngx_log.h \
	src/os/unix/ngx_linux_config.h \
	src/os/unix/ngx_process_cycle.h \
	src/os/unix/ngx_channel.h \
	src/os/unix/ngx_files.h \
	src/os/unix/ngx_socket.h \
	src/os/unix/ngx_process.h \
	src/event/ngx_event.h

CORE_INCS = -I src/core \
	-I src/os/unix \
	-I src/event \
	-I objs

objs/ngx: objs/ngx_modules.o \
	objs/src/core/nginx.o \
	objs/src/core/ngx_cycle.o \
	objs/src/core/ngx_palloc.o \
	objs/src/core/ngx_buf.o \
	objs/src/os/unix/ngx_process.o \
	objs/src/os/unix/ngx_process_cycle.o \
	objs/src/event/ngx_event.o
	$(LINK) -o $@ $^

objs/ngx_modules.o: $(CORE_DEPS) objs/ngx_modules.c
	$(CC) -o $@  -c $(CFLAGS) $(CORE_INCS) objs/ngx_modules.c
    
objs/src/core/nginx.o:	$(CORE_DEPS) src/core/nginx.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/nginx.c

objs/src/core/ngx_cycle.o:	$(CORE_DEPS) src/core/ngx_cycle.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/ngx_cycle.c

objs/src/os/unix/ngx_process_cycle.o:	$(CORE_DEPS) src/os/unix/ngx_process_cycle.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/os/unix/ngx_process_cycle.c

objs/src/os/unix/ngx_process.o:	$(CORE_DEPS) src/os/unix/ngx_process.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/os/unix/ngx_process.c

objs/src/event/ngx_event.o:	$(CORE_DEPS) src/event/ngx_event.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/event/ngx_event.c

objs/src/core/ngx_palloc.o: $(CORE_DEPS) src/core/ngx_palloc.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/ngx_palloc.c

objs/src/core/ngx_buf.o: $(CORE_DEPS) src/core/ngx_buf.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/ngx_buf.c
