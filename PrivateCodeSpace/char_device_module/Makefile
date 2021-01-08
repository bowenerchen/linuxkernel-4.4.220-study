# obj-m = $(target).o 
# $(target)-objs := file1.o file2.o file3.o ...

obj-m += char_device.o
char_device-objs := main.o
PWD := $(shell pwd)
KDIR := ../../SourceCode/
CC := arm-linux-gnueabi-gcc

all: char_module char_test

.PHONY: char_module
char_module:
	@echo "<------------------->"
	@echo "compile main.c for kernel char device module"
	$(MAKE) -C $(KDIR) M=$(PWD) modules;

.PHONY: char_test
char_test:
	@echo "<------------------->"
	@echo "compile test.c for user test tool"
	${CC} test.c -o char_device_test --static

clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order *.marker *~ .*.ko.cmd .*.o.cmd .tmp_versions cham_device_test

