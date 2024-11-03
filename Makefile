# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -std=c11 -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image

# Directories for source and object files
SRCDIR = src
OBJDIR = build

# Source and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Executable target
TARGET = $(OBJDIR)/space-crusher

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Rule to compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the build directory
clean:
	rm -rf $(OBJDIR)
