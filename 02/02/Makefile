CC=g++

all: main

main.o: main.cpp LinearAllocator.hpp LinearAllocator.cpp
	$(CC) -c main.cpp

LinearAllocator.o: LinearAllocator.cpp LinearAllocator.hpp
	$(CC) -c LinearAllocator.cpp

main: main.o LinearAllocator.o
	$(CC) -o main main.o LinearAllocator.o

test: LinearAllocator.o main.o
	$(CC) -o main main.o LinearAllocator.o
	python test.py
run: LinearAllocator.o main.o
	$(CC) -o main main.o LinearAllocator.o
	./main
clean:
	rm -rf *.o main
