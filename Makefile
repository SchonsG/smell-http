# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -Iinclude

# List of source files
SRC = $(wildcard src/*.c src/handlers/*.c src/utils/*.c src/cache/*.c src/network/*.c)

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXEC = smell-http

# Default target
all: $(EXEC)

# Linking step
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)
