CFLAGS = -g -Wall -Wextra -pedantic

all: main

main: main.o board.o pieces.o environment.o
	g++ main.o board.o pieces.o environment.o -o main

main.o: main.cpp
	g++ -c main.cpp -g

board.o: board.cpp board.h
	g++ -c board.cpp -g

pieces.o: pieces.cpp pieces.h
	g++ -c pieces.cpp -g

environment.o: environment.cpp environment.h
	g++ -c environment.cpp -g

# Test target
test: tests/test_runner
	./tests/test_runner

tests/test.o: tests/testPieces.cpp environment.h
	g++ -c tests/testPieces.cpp -o tests/test.o -g

tests/test_runner: tests/test.o board.o pieces.o environment.o
	g++ tests/test.o board.o pieces.o environment.o -o test_runner

clean:
	rm -f *.o main