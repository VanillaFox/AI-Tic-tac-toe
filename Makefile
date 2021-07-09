CC=g++
CFLAGS=-std=c++14 -c -O3
OUTPUT = tictactoe

all: tictactoe

tictactoe: main.o game.o
	$(CC) main.o game.o -o $(OUTPUT)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

game.o: game.cpp
	$(CC) $(CFLAGS) game.cpp

clean:
	rm -rf *.o $(OUTPUT)
