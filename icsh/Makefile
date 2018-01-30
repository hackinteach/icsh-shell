CC = gcc
CFLAGS = -g -D_POSIX_C_SOURCE -Wall -std=c99
# CFLAGS = -g -Wall -std=c99
TARGET = icsh
LIBS = -lm

.PHONY: default all clean

default: clean $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
