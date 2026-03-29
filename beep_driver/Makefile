NAME=beep

ifneq ($(KERNELRELEASE),)
	obj-m := $(NAME).o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

load:
	/sbin/insmod $(NAME).ko

unload:
	/sbin/rmmod $(NAME)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif
