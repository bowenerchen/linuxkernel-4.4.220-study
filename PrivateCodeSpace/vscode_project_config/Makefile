# obj-m = $(target).o 
# $(target)-objs := file1.o file2.o file3.o ...

ifneq ($(KERNELRELEASE),)
	obj-m += helloworld.o
	helloworld-objs := helloworld_module.o

else
	PWD := $(shell pwd)
    KVER := $(shell uname -r)
    KDIR := ../../SourceCode/

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules;

clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order *.marker *~ .*.ko.cmd .*.o.cmd .tmp_versions

endif
