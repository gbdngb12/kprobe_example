obj-m += kprobe.o
KDIR = /lib/modules/$(shell uname -r)/build
all: 
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules
clean: 
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
