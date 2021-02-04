AM_SRCS := nemu-common/trm.c \
           nemu-common/ioe.c \
           nemu-common/nemu-input.c \
           nemu-common/nemu-timer.c \
           nemu-common/nemu-video.c \
           $(ISA)/nemu/cte.c \
           $(ISA)/nemu/trap.S \
           $(ISA)/nemu/vme.c \
           dummy/mpe.c \
           $(ISA)/nemu/boot/start.S

LD_SCRIPT := $(AM_HOME)/am/src/$(ISA)/nemu/boot/loader.ld

ifdef mainargs
MAINARGS = -a $(mainargs)
endif
NEMU_ARGS = -b $(MAINARGS) -l $(shell dirname $(BINARY))/nemu-log.txt $(BINARY).bin

image:
	@echo + LD "->" $(BINARY_REL).elf
	@$(LD) $(LDFLAGS) --gc-sections -T $(LD_SCRIPT) -e _start -o $(BINARY).elf $(LINK_FILES)
	@$(OBJDUMP) -d $(BINARY).elf > $(BINARY).txt
	@echo + OBJCOPY "->" $(BINARY_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(BINARY).elf $(BINARY).bin

run:
	$(MAKE) -C $(NEMU_HOME) ISA=$(ISA) run ARGS="$(NEMU_ARGS)"

gdb: image
	$(MAKE) -C $(NEMU_HOME) ISA=$(ISA) gdb ARGS="$(NEMU_ARGS)"
