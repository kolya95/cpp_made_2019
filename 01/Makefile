CC=g++

all: main

main.o: main.cpp lexeme_parser.h
	$(CC) -c main.cpp

lexeme_parser.o: lexeme_parser.cpp lexeme_parser.h
	$(CC) -c lexeme_parser.cpp

main: main.o lexeme_parser.o
	$(CC) -o main main.o lexeme_parser.o

test: lexeme_parser.o main.o
	$(CC) -o main main.o lexeme_parser.o
	python test.py
run: lexeme_parser.o main.o
	$(CC) -o main main.o lexeme_parser.o
	./main
clean:
	rm -rf *.o main
