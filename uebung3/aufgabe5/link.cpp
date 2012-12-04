#include <cstdio>
#include <cstdlib>

extern "C" unsigned calc_expr();

int main() {
  printf("architecture %s\n", sizeof(void *) == 8 ? "64bit" : "32bit");
  printf("expr(compiled) = %d\n", calc_expr());

  return EXIT_SUCCESS;
}