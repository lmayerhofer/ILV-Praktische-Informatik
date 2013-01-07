all: main

main: main.cpp
	g++ -Wall -g -o $@ main.cpp

test: main
	./main test_data/trace-ls.txt

clean:
	rm -f main