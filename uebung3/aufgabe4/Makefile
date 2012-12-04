all: aufgabe4

aufgabe4: aufgabe4.cpp
	$(CXX) -Wall -g -o $@ aufgabe4.cpp

test: aufgabe4
	./aufgabe4
	valgrind --leak-check=full ./aufgabe4

clean:
	rm -f aufgabe4
	
