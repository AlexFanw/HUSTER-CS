include Makefile.check

APPS = init pal litenes
TESTS = bmp dummy events hello text

APPS_ALL = $(addprefix $(NAVY_HOME)/apps/, $(APPS)) $(addprefix $(NAVY_HOME)/tests/, $(TESTS))

.PHONY: fsimg $(APPS_ALL) clean

fsimg: $(APPS_ALL)

$(APPS_ALL): %:
	-$(MAKE) -C $@ install

clean:
	$(foreach app, $(APPS_ALL), $(MAKE) -C $(app) clean ;)
	$(foreach lib, $(shell ls libs/), $(MAKE) -C $(NAVY_HOME)/libs/$(lib) clean ;)
	rm -f fsimg/bin/*
