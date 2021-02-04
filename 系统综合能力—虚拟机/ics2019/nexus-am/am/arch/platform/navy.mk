AM_SRCS := navy/trm.c

NAVY_MAKEFILE = Makefile.navy
NAVY_MAKEFILE_CONTENT = "NAME = $(NAME)-am\nAPP = $(BINARY)\nOBJS = $(LINK_FILES)\nLIBS += libndl\ninclude $${NAVY_HOME}/Makefile.app"

NAVY_LIBS = libndl libos libc
INC_DIR  += $(addsuffix /include/, $(addprefix $(NAVY_HOME)/libs/, $(NAVY_LIBS)))


image:
	@/bin/echo -e $(NAVY_MAKEFILE_CONTENT) > $(NAVY_MAKEFILE)
	$(MAKE) install -f $(NAVY_MAKEFILE) ISA=$(ISA)
	rm $(NAVY_MAKEFILE)

run:
	echo "Cannot run: should be loaded by an OS"
