CC = gcc
CFLAGS = -Wall -Werror
OBJ = minibusybox
SYMLINKS = touch mkdir sleep cat
.PHONY = all clean 

all: $(OBJ)

$(OBJ): minibusybox.c
	$(CC) $(CFLAGS) $< -o $(OBJ)
	for name in $(SYMLINKS); do \
		ln -s $(OBJ) $$name; \
	done
clean:
	rm $(OBJ)
	for name in $(SYMLINKS); do \
		rm $$name; \
	done
