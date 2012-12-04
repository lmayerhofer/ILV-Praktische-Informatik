all: generate

generate: generate.cpp
	$(CXX) -Wall -o $@ generate.cpp

plus: generate
	./generate 1 > calc_expr.s

minus: generate
	./generate 2 > calc_expr.s

mult: generate
	./generate 3 > calc_expr.s

pow: generate
	./generate 4 > calc_expr.s

max: generate
	./generate 5 > calc_expr.s

test:
	as -c -o calc_expr.o calc_expr.s
	$(CXX) -c -o link.o link.cpp
	$(CXX) -o calc link.o calc_expr.o
	./calc

clean:
	rm -f generate
	rm -f calc_expr.s
	rm -f calc_expr.o
	rm -f link.o
	rm -f calc