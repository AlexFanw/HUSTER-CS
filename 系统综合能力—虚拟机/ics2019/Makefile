include nemu/Makefile.git

default:
	@echo "Please run 'make' under any subprojects to compile."
 
clean:
	-$(MAKE) -C nemu clean
	-$(MAKE) -C nexus-am clean
	-$(MAKE) -C nanos-lite clean
	-$(MAKE) -C navy-apps clean

submit: 
	STUID=$(STUID) STUNAME=$(STUNAME) bash -c "$$(curl -s https://course.cunok.cn/pa/scripts/submit.sh)"

info: 
	STUID=$(STUID) STUNAME=$(STUNAME) bash -c "$$(curl -s https://course.cunok.cn/pa/scripts/info.sh)"

setup: 
	STUID=$(STUID) STUNAME=$(STUNAME) bash -c "$$(curl -s https://course.cunok.cn/pa/scripts/setup.sh)"

password: 
	STUID=$(STUID) STUNAME=$(STUNAME) bash -c "$$(curl -s https://course.cunok.cn/pa/scripts/password.sh)"


.PHONY: default clean submit
