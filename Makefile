CC=g++

TARGET=build
SRCS=src/*.cpp
DEPS=src/*.h

CFLAGS=-Wall
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -llua5.3

$(TARGET): $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LFLAGS)
