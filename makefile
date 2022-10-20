# Makrodefinitions
CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -Wno-implicit-fallthrough -O2 -std=c17
LDFLAGS  =

.PHONY: all clean

# Executable file
all: labyrinth

# Rules for linking
labyrinth: bit_array.o multiple_usage.o queue.o creating_labyrinth_representation.o input_line123.o input_line45.o looking_for_path.o main.o
	$(CC) -o labyrinth $^

# Rules for compiling
bit_array.o: bit_array.h
multiple_usage.o: multiple_usage.h
queue.o: queue.h structures.h
creating_labyrinth_representation.o: creating_labyrinth_representation.h bit_array.h structures.h multiple_usage.h
input_line123.o: input_line123.h structures.h
input_line45.o: creating_labyrinth_representation.h input_line45.h structures.h multiple_usage.h
looking_for_path.o: queue.h looking_for_path.h input_line123.h bit_array.h structures.h
main.o: input_line123.h creating_labyrinth_representation.h looking_for_path.h input_line45.h bit_array.h structures.h

clean:
	rm -f *.o labyrinth
