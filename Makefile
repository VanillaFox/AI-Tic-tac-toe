CC=g++
CFLAGS=-std=c++14 -c -O3
OUTPUT = tictactoe

all: tictactoe

tictactoe: main.o game.o player.o
	$(CC) main.o game.o player.o -o $(OUTPUT)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

game.o: game.cpp
	$(CC) $(CFLAGS) game.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) player.cpp

clean:
	rm -rf *.o $(OUTPUT)
