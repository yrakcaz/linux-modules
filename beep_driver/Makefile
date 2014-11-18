NAME=beep
SRC=beep.c
OBJ=$(SRC:.c=.o)

ifneq ($(KERNELRELEASE),)
	obj-m := $(NAME).o
	$(Name)-objs := $(OBJ)
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

load: all
	sudo /sbin/insmod $(NAME).ko

unload:
	sudo /sbin/rmmod $(NAME)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif
