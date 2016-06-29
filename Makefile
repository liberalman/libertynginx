default:	build

clean:
	rm -rf objs/src/core/*.o
	rm -rf objs/src/event/*.o
	rm -rf objs/src/os/unix/*.o
	rm -rf objs/*.o

build:
	make -f objs/Makefile
