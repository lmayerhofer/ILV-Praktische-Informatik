all: aufgabe1

aufgabe1: aufgabe1.c
	gcc -Wall -g -DCLS=`getconf LEVEL1_DCACHE_LINESIZE` -std=c99 -msse2 -O3 -o $@ aufgabe1.c
	    
clean:
	rm -f aufgabe1

test: aufgabe1
	./aufgabe1
