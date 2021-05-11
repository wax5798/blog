export EXTRA_CFLAGS := -m32 -static -Wall -Werror
export INSTALL_DIR = $(PWD)/../rootfs/bin

all: 
	make -C ./test 

build:
	make -C ./test build

clean: 
	make -C ./test clean

install:
	make -C ./test install
