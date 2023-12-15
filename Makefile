# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Executable name
EXEC = scout

# Source files
SRC = ./src/main.c ./src/readers/dir_reader.c ./src/readers/file_reader.c ./src/printers/colours.c ./src/printers/printer.c ./src/helpers/num_cores.c ./src/helpers/terminal_width.c ./src/helpers/path_type.c

# Object files
OBJ = $(notdir $(SRC:.c=.o))

# Default target
all: $(EXEC)

# Rule to create executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to create object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependency rule to find the .c files
vpath %.c $(sort $(dir $(SRC)))

# Phony target for cleaning up
.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJ)
