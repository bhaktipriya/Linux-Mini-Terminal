CC=gcc
CFLAGS=-I.
DEPS = shell.h
OBJ = io.o handlers.o misc.o parent_exec.o shell.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)
