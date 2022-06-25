KERNEL_SRC=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

obj-m+=src/module.o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean