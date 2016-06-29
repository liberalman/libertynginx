CC = gcc
CFLAGS = -g -D_DEBUG

#-D_PRINT_STACK
LINK = $(CC)

ALL_INCS = -I src/core \
    -I src/objs
    
CORE_DEPS = src/core/liberty.h \
	src/core/lbt_config.h \
	src/core/lbt_core.h \
    src/core/lbt_config.h \
	src/core/lbt_core.h \
	src/core/lbt_cycle.h \
	src/core/lbt_palloc.h \
	src/core/lbt_buf.h \
	src/core/lbt_log.h \
	src/os/unix/lbt_linux_config.h \
	src/os/unix/lbt_process_cycle.h \
	src/os/unix/lbt_channel.h \
	src/os/unix/lbt_files.h \
	src/os/unix/lbt_socket.h \
	src/os/unix/lbt_process.h \
	src/event/lbt_event.h

CORE_INCS = -I src/core \
	-I src/os/unix \
	-I src/event \
	-I objs

objs/liberty: objs/lbt_modules.o \
    objs/src/core/liberty.o \
    objs/src/core/lbt_log.o \
    objs/src/core/lbt_times.o \
    objs/src/core/lbt_cycle.o \
	objs/src/core/lbt_palloc.o \
	objs/src/core/lbt_buf.o \
	objs/src/os/unix/lbt_process.o \
	objs/src/os/unix/lbt_process_cycle.o \
    objs/src/os/unix/lbt_errno.o \
	objs/src/event/lbt_event.o
	$(LINK) -o $@ $^

objs/lbt_modules.o: $(CORE_DEPS) objs/lbt_modules.c
	$(CC) -o $@  -c $(CFLAGS) $(CORE_INCS) objs/lbt_modules.c
    

objs/src/core/liberty.o:	$(CORE_DEPS) src/core/liberty.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/liberty.c
objs/src/core/lbt_log.o:	$(CORE_DEPS) src/core/lbt_log.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/lbt_log.c
objs/src/core/lbt_times.o:	$(CORE_DEPS) src/core/lbt_times.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/lbt_times.c
objs/src/core/lbt_cycle.o:	$(CORE_DEPS) src/core/lbt_cycle.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/lbt_cycle.c
objs/src/core/lbt_palloc.o: $(CORE_DEPS) src/core/lbt_palloc.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/lbt_palloc.c
objs/src/core/lbt_buf.o: $(CORE_DEPS) src/core/lbt_buf.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/core/lbt_buf.c

objs/src/os/unix/lbt_process_cycle.o:	$(CORE_DEPS) src/os/unix/lbt_process_cycle.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/os/unix/lbt_process_cycle.c
objs/src/os/unix/lbt_process.o:	$(CORE_DEPS) src/os/unix/lbt_process.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/os/unix/lbt_process.c
objs/src/os/unix/lbt_errno.o:	$(CORE_DEPS) src/os/unix/lbt_errno.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/os/unix/lbt_errno.c

objs/src/event/lbt_event.o:	$(CORE_DEPS) src/event/lbt_event.c
	$(CC) -o $@ -c $(CFLAGS) $(CORE_INCS) src/event/lbt_event.c


