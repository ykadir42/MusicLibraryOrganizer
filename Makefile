CC = gcc -ggdb -std=c99 -Wall -Werror -O3

song.o:
	$(CC) -c song.c

song_node.o: song.o
	$(CC) -c song_node.c

song_library.o: song_node.o
	$(CC) -c song_library.c

main.o: song_library.o
	$(CC) -c main.c

all: main.o song_library.o song_node.o song.o
	$(CC) -o main main.o song_library.o song_node.o song.o

run: all
	./main

clean:
	rm *.o