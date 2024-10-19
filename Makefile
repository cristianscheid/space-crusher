# Compiler and flags
CC = gcc
CFLAGS = -Wall -I$(INCDIR) -g
LDFLAGS = -lSDL2 -lSDL2_image

# Source directories
SRCDIR = src
OBJDIR = build
INCDIR = include

# Source and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Executable name
TARGET = $(OBJDIR)/space-crusher

# Default rule to build the project
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and binary
clean:
	rm -rf $(OBJDIR)

# Debug mode
debug: CFLAGS += -g
debug: $(TARGET)

# Release mode with optimizations
release: CFLAGS += -O2
release: clean $(TARGET)
