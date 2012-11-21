all: aufgabe2_server aufgabe2_client

aufgabe2_server: aufgabe2_server.c
	$(CXX) -Wall -g -o $@ aufgabe2_server.c

aufgabe2_client: aufgabe2_client.c
	$(CXX) -Wall -g -o $@ aufgabe2_client.c
	    
clean:
	rm -f aufgabe2_server
	rm -f aufgabe2_client

test: aufgabe2_server aufgabe2_client
	./aufgabe2_server
	./aufgabe2_client
	
