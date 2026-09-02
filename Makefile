CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lncurses
TARGET = game

all: $(TARGET)

$(TARGET): game.c game1.c game.h
        $(CC) $(CFLAGS) game.c game1.c -o $(TARGET) $(LIBS)

run: $(TARGET)
        ./$(TARGET)

clean:
        rm -f $(TARGET) *.o

.PHONY: all run clean