TARGET := test

all: build install

build: test.c
	gcc test.c -o $(TARGET) $(EXTRA_CFLAGS)

install: $(TARGET)
	cp $(TARGET) $(INSTALL_DIR)

clean:
	rm -f $(TARGET)

