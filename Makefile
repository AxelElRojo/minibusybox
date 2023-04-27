CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror
TARGET = minibusybox
LIB_PATH = lib
INCLUDE_PATH = include
LIBS = -lmkdir
MAIN = minibusybox.c

.PHONY: all install clean
all: $(TARGET)

$(TARGET): main.o libmkdir.so
	$(CC) $(CFLAGS) $< $(LIBS) -L. -o $@
main.o: $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@
libmkdir.so: $(LIB_PATH)/mkdir.c $(INCLUDE_PATH)/libmkdir.h
	$(CC) $(CFLAGS) -c -fpic $< -o mkdir.o
	$(CC) -shared -o $@ mkdir.o
install: libmkdir.so
	sudo cp $< /usr/lib
	sudo cp $(INCLUDE_PATH)/libmkdir.h /usr/include
clean:
	rm *.o *.so $(TARGET)