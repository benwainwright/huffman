# This will pick up all the source files in a particular dir
# But you can replace it with a particular filename if you want
SRC=$(wildcard src/*.c)
OUT=huffman
CFLAGS= -pedantic -Wall -Wextra -Wfloat-equal -ansi
OPT= -O3
DEBUG = -g -Og
LIBS= -lm

all: $(SRC)
	gcc $(SRC) -o $(OUT) $(CFLAGS) $(OPT) $(LIBS)

debug: $(SRC)
	gcc $(SRC) -o $(OUT) $(CFLAGS) $(DEBUG) $(LIBS)
