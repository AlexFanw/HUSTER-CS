AM_SRCS := native/trm.c \
           native/ioe.c \
           native/cte.c \
           native/trap.S \
           native/vme.c \
           native/mpe.c \
           native/platform.c \
           native/devices/input.c \
           native/devices/timer.c \
           native/devices/video.c \

CFLAGS  += -fpie
ASFLAGS += -fpie -pie

image:
	@echo + LD "->" $(BINARY_REL)
	@g++ -pie -o $(BINARY) -Wl,--whole-archive $(LINK_FILES) -Wl,-no-whole-archive -lSDL2 -lGL -lrt

run:
	$(BINARY)
