APP_DIR ?= $(shell pwd)
INC_DIR += $(APP_DIR)/include/
DST_DIR ?= $(APP_DIR)/build/$(ARCH)/
BINARY  ?= $(APP_DIR)/build/$(NAME)-$(ARCH)
BINARY_REL = $(shell realpath $(BINARY) --relative-to .)

## Paste in "Makefile.check" here
include $(AM_HOME)/Makefile.check
$(info # Building $(NAME) [$(ARCH)] with AM_HOME {$(AM_HOME)})

## Default: Build a runnable image
default: image

LIBS    += klib
INC_DIR += $(addsuffix /include/, $(addprefix $(AM_HOME)/libs/, $(LIBS)))

## Paste in "Makefile.compile" here
include $(AM_HOME)/Makefile.compile

## Produce a list of files to be linked: app objects, AM, and libraries
LINK_LIBS  = $(sort $(LIBS))
LINK_FILES = \
  $(OBJS) \
  $(AM_HOME)/am/build/am-$(ARCH).a \
  $(addsuffix -$(ARCH).a, $(join \
    $(addsuffix /build/, $(addprefix $(AM_HOME)/libs/, $(LINK_LIBS))), \
    $(LINK_LIBS) \
))

$(OBJS): $(PREBUILD)
image:   $(OBJS) am $(LIBS) prompt
prompt:  $(OBJS) am $(LIBS)
run:     default

prompt:
	@echo \# Creating binary image [$(ARCH)]

clean: 
	rm -rf $(APP_DIR)/build/

.PHONY: default run image prompt clean
