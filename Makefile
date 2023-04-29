CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror
TARGET = minibusybox
LIB_PATH = sleep
LIB_NAME = sleep
LIBS = -lsleep
MAIN = minibusybox.c

.PHONY: all install clean
all: $(TARGET)

$(TARGET): main.o lib$(LIB_NAME).so
	$(CC) $(CFLAGS) $< $(LIBS) -L. -o $@
main.o: $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@
lib$(LIB_NAME).so: $(LIB_PATH)/$(LIB_NAME).c $(LIB_PATH)/lib$(LIB_NAME).h
	$(CC) $(CFLAGS) -c -fpic $< -o $(LIB_NAME).o
	$(CC) -shared -o $@ $(LIB_NAME).o
install: lib$(LIB_NAME).so
	sudo cp $< /usr/lib
	sudo cp $(LIB_PATH)/lib$(LIB_NAME).h /usr/include
clean:
	rm *.o *.so $(TARGET)