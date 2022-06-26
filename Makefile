TARGER_MODULE:=simple-module

CLANG_FORMAT=clang-format
FORMAT_SRC=src/my_simple_module.c src/main.c src/my_simple_module.h

KERNEL_SRC=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

$(TARGER_MODULE)-objs := src/main.o src/my_simple_module.o
obj-m:=$(TARGER_MODULE).o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
load:
	insmod $(TARGER_MODULE).ko
unload:
	rmmod $(TARGER_MODULE).ko
format:
	$(CLANG_FORMAT) -i $(FORMAT_SRC)
