NAME = nanos-lite
SRCS = $(shell find -L ./src/ -name "*.c" -o -name "*.cpp" -o -name "*.S")
LIBS = klib
PREBUILD = update

include $(AM_HOME)/Makefile.app

ifeq ($(ARCH),native)
ISA = am_native
endif

FSIMG_PATH = $(NAVY_HOME)/fsimg
RAMDISK_FILE = build/ramdisk.img

SINGLE_APP = $(NAVY_HOME)/tests/dummy
SINGLE_APP_FILE = $(FSIMG_PATH)/bin/$(notdir $(SINGLE_APP))

.PHONY: update update-ramdisk-single update-ramdisk-fsimg update-fsimg

update-ramdisk-single:
	$(MAKE) -s -C $(SINGLE_APP) install ISA=$(ISA)
	cp $(SINGLE_APP_FILE) $(RAMDISK_FILE)
	touch src/files.h

update-fsimg:
	$(MAKE) -s -C $(NAVY_HOME) ISA=$(ISA)

update-ramdisk-fsimg: update-fsimg
	$(eval FSIMG_FILES := $(shell find $(FSIMG_PATH) -type f))
	@cat $(FSIMG_FILES) > $(RAMDISK_FILE)
	@wc -c $(FSIMG_FILES) | grep -v 'total$$' | sed -e 's+ $(FSIMG_PATH)+ +' | awk -v sum=0 '{print "\x7b\x22" $$2 "\x22\x2c " $$1 "\x2c " sum "\x7d\x2c";sum += $$1}' > src/files.h

src/syscall.h: $(NAVY_HOME)/libs/libos/src/syscall.h
	ln -sf $^ $@

update: update-ramdisk-fsimg src/syscall.h
	@touch src/initrd.S
