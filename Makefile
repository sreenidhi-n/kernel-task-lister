obj-m += OS_project.o
VERSION = $(shell uname -r)
PWD = $(shell pwd)
default:
	$(MAKE) -C /lib/modules/$(VERSION)/build M=$(PWD) modules
clean:
	$(MAKE) -C /lib/modules/$(VERSION)/build M=$(PWD) clean
