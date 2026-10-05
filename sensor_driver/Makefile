ifneq ($(KERNELRELEASE),)

obj-m += dht11driver.o


else

CROSS_COMPILE ?= arm-buildroot-linux-gnueabihf-
KERN_DIR ?= /home/book/100ask_imx6ull-sdk/Linux-4.9.88

.PHONY: all clean

all:
	$(MAKE) -C $(KERN_DIR) M=$(CURDIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KERN_DIR) M=$(CURDIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) clean

endif
