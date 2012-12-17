all: aufgabe3

aufgabe4: aufgabe3.cpp
	$(CXX) -Wall -g -o $@ aufgabe3.cpp

test: aufgabe3
	./aufgabe3
	valgrind --leak-check=full ./aufgabe3

clean:
	rm -f aufgabe3
	
