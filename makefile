# This will pick up all the source files in a particular dir
# But you can replace it with a particular filename if you want
SRC=$(wildcard src/*.c)
OUT=huffman
CFLAGS= -pedantic -Wall -Wextra -Wfloat-equal -ansi $(shell pkg-config sdl2 --cflags)
OPT= -O3
DEBUG = -g
LIBS= -lm $(shell pkg-config sdl2 --libs)

all: $(SRC)
	gcc $(SRC) -o $(OUT) $(CFLAGS) $(OPT) $(LIBS)

debug: $(SRC)
	gcc $(SRC) -o $(OUT) $(CFLAGS) $(DEBUG) $(LIBS)
