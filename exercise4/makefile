main: main.o braille.o
	g++ -Wall -g main.o braille.o -o main

main.o: main.cpp braille.h
	g++ -Wall -g -c main.cpp

braille.o : braille.cpp braille.h
	g++ -Wall -g -c braille.cpp
