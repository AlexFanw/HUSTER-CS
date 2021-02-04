include $(NAVY_HOME)/Makefile.check

APPS = coremark dhrystone microbench slider typing litenes

APPS_ALL = $(addprefix $(AM_HOME)/apps/, $(APPS)) $(addprefix $(AM_HOME)/tests/, $(TESTS))

install: $(APPS_ALL)

.PHONY: $(APPS_ALL) clean

$(APPS_ALL): %:
	-$(MAKE) -C $@ ARCH=$(ISA)-navy

clean:
	$(foreach app, $(APPS_ALL), $(MAKE) -C $(app) ARCH=$(ISA)-navy clean ;)
