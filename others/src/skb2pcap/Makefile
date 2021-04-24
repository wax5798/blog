# 如果已定义 KERNELRELEASE，则说明是从内核构造系统调用的，因此可利用其内建语句
ifneq ($(KERNELRELEASE), )
	obj-m := skb2pcap.o
	skb2pcap-objs := main.o
# 否则，是直接从命令行调用的，这时要用内核构造系统
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CC) pcap_parser.c -o pcap_parser

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -f pcap_parser
endif
