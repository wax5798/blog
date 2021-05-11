KERNEL_DIR := ../linux-3.18.6
BUSYBOX_DIR := ../busybox-1.33.0

kernel_build:
	cp config/kernel.config $(KERNEL_DIR)/.config
	cd $(KERNEL_DIR) && make CC=gcc-4.7

busybox_build:
	cp config/busybox.config $(BUSYBOX_DIR)/.config
	cd $(BUSYBOX_DIR) && make CC="gcc -m32" && make CC="gcc -m32" install

rootfs_build:
	cp $(BUSYBOX_DIR)/_install/* ./rootfs/ -r
	cd ./rootfs && mkdir -p proc sys dev
	cd ./myPro && make all
	- cd ./rootfs && sudo mknod dev/ttyAMA0 c 204 64 ; sudo mknod dev/null c 1 3 ; sudo mknod dev/console c 5 1
	cd ./rootfs && find . | cpio -o --format=newc > ../rootfs.img

all: kernel_build busybox_build rootfs_build


run: 
	qemu-system-i386 -kernel $(KERNEL_DIR)/arch/i386/boot/bzImage -initrd ./rootfs.img -append "root=/dev/ram rdinit=/sbin/init console=ttyS0" -nographic -smp 2

dbg_run:
	qemu-system-i386 -kernel $(KERNEL_DIR)/arch/i386/boot/bzImage -initrd ./rootfs.img -append "root=/dev/ram rdinit=/sbin/init console=ttyS0" -nographic -S -s -smp 2

# 说明
# kernel.config 文件是上一次正确配置 kernel 之后得到的 .config 文件，需要选择 i386 并开启调试功能
# busybox.config 文件是上一次正确配置 busybox 之后得到的 .config 文件，需要开启静态编译
# rcS 文件需要有可执行权限

