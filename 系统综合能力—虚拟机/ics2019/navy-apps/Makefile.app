ifeq (run, $(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

include $(NAVY_HOME)/Makefile.check

APP_DIR ?= $(shell pwd)
INC_DIR += $(APP_DIR)/include/
DST_DIR ?= $(APP_DIR)/build/$(ISA)/
APP ?= $(APP_DIR)/build/$(NAME)-$(ISA)

.DEFAULT_GOAL = $(APP)

$(shell mkdir -p $(DST_DIR))

ifneq ($(ISA), native)
LIBS += libc libos
endif

.PHONY: $(LIBS)

$(LIBS): %:
	$(MAKE) -C $(NAVY_HOME)/libs/$@

INC_DIR += $(addsuffix /include/, $(addprefix $(NAVY_HOME)/libs/, $(LIBS)))

include $(NAVY_HOME)/Makefile.compile

LIB_FILES += $(addsuffix -$(ISA).a, $(join \
  $(addsuffix /build/, $(addprefix $(NAVY_HOME)/libs/, $(LIBS))), \
  $(LIBS) \
))

$(APP): $(LIBS) $(OBJS)
	@echo + LD $@
ifeq ($(ISA), native)
	@g++ -o $(APP) $(OBJS) $(LIB_FILES)
else
	@$(LD) $(LDFLAGS) -o $(APP) --start-group $(OBJS) $(LIB_FILES) --end-group
endif

.PHONY: install run clean

install: $(APP)
	cp $(APP) $(NAVY_HOME)/fsimg/bin/$(NAME)

run: $(APP)
ifeq ($(ISA), native)
	$(MAKE) -C $(NAVY_HOME)/libs/libos ISA=native
	@LD_PRELOAD=$(NAVY_HOME)/libs/libos/build/native.so $(APP) $(RUN_ARGS)
else
	$(error Cannot run: should be loaded by an OS)
endif

clean:
	rm -rf $(APP_DIR)/build/
