
PWD := $(shell pwd)
KDIR := ../../SourceCode/
CC := arm-linux-gnueabi-gcc

# obj-m = $(target).o 
# $(target)-objs := file1.o file2.o file3.o ...
ko_target = misc_device
obj-m += ${ko_target}.o
${ko_target}-objs := main.o

all: misc_module misc_test

.PHONY: misc_module
misc_module:
	@echo "<------------------->"
	@echo "compile main.c for kernel misc device module"
	$(MAKE) -C $(KDIR) M=$(PWD) modules;

.PHONY: misc_test
misc_test:
	@echo "<------------------->"
	@echo "compile test.c for user test tool"
	${CC} test.c -o misc_device_test --static

clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order *.marker *~ .*.ko.cmd .*.o.cmd .tmp_versions char_device_test

