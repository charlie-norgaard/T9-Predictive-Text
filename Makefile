# Compiler
CC = gcc

# Compiler flags (may need to add flags depending on user system))
CFLAGS = -Wall

# Name of Program
TARGET = t9

# Phony target
all: $(TARGET)

# All the file we need for the executable
OBJECTS = trie.o tnine.o

# The executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o t9 $(OBJECTS)

# Individual Source Files
trie.o: trie.c trienode.h
	$(CC) $(CFLAGS) -c trie.c

tnine.o: tnine.c trienode.h
	$(CC) $(CFLAGS) -c tnine.c

# Phony target to remove built files and backups
clean:
	rm -f *.o t9 *~
