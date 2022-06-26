TARGER_MODULE:=my_module

CLANG_FORMAT=clang-format
FORMAT_SRC=src/my_module.c

KERNEL_SRC=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

obj-m:=src/$(TARGER_MODULE).o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
load:
	insmod ./src/$(TARGER_MODULE).ko
unload:
	rmmod ./src/$(TARGER_MODULE).ko
format:
	$(CLANG_FORMAT) -i $(FORMAT_SRC)
