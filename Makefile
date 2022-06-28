TARGER_MODULE:=simple-module

ifeq ($(strip $(MODULE)),)
	$(TARGER_MODULE)-objs := src/main.o src/my_simple_module.o
else ifeq ($(MODULE), $(TARGER_MODULE))
	$(TARGER_MODULE)-objs := src/main.o src/my_simple_module.o
else
	TARGER_MODULE:=src/$(MODULE)
endif

obj-m:=$(TARGER_MODULE).o

CLANG_FORMAT=clang-format
FORMAT_SRC=src/my_simple_module.c src/main.c src/my_simple_module.h src/hello_world.c

KERNEL_SRC=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

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
