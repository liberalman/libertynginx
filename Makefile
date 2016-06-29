default:	build

clean:
	rm -rf objs/src/core/*.o
	rm -rf objs/src/os/nginx/*.o
	rm -rf objs/*.o
#rm -rf Makefile  

build:
	make -f objs/Makefile
