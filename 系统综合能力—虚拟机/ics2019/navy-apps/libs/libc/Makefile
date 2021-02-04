NAME = libc
SRCS = $(shell find src/ -name "*.c" -o -name "*.S" -o -name "*.cpp")

# fix compilation in ubuntu 16.04
CFLAGS = -U_FORTIFY_SOURCE

include $(NAVY_HOME)/Makefile.lib
