#include <cstdio>
#include <cstdlib>

extern "C" unsigned calc_expr();

int main() {
	if(sizeof(void *) == 4) {
		printf("\ncompiled: %d\n\n", calc_expr());
	} else {
		printf("\narchitecture not supported\n\n");
	}

	return EXIT_SUCCESS;
}