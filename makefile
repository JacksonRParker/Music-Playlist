CC = g++
CPPFLAGS = -std=c++11 -g -Wall

main: main.o song.o songlist.o

main.o: util.h song.h

song.o: util.h song.h

songlist.o: util.h song.h songlist.h

clean:
	rm *.o main

leak:
	valgrind --leak-check=full ./main
