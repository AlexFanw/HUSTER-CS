NAME := litenes
SRCS := $(shell find -L ./src/ -name "*.c")
ROMS := $(shell find -L ./src/ -name "*.nes")
PREBUILD := rom
include $(AM_HOME)/Makefile.app

.PHONY: rom
rom: $(ROMS)
	@cd src/roms && python3 build-roms.py
