all: main

main: main.cpp
	g++ -Wall -g -o $@ main.cpp

test: main
	./main test_data/trace-ex1.txt

clean:
	rm -f main