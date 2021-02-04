NAME = libos
SRCS = src/nanos.c

ifeq ($(ISA), native)
build/native.so: src/native.cpp
	mkdir -p build/
	g++ -std=c++11 -O1 -fPIC -shared -o build/native.so src/native.cpp -ldl -lSDL2

else
include $(NAVY_HOME)/Makefile.lib
endif

