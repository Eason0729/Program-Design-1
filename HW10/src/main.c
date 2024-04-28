#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

typedef double (*F)(double, int, int);

double powerpower(F call, double x, int n, int m) {
  return call(x, n, m);
}

double type_a(double a, int b, int c) { return power(a, b * c); }

double type_b(double a, int b, int c) { return power(multiply(a, b), c); }

double type_c(double a, int b, int c) { return power(divide(a, b), c); }

int main(int argc, char** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
    return 1;
  }
  F fns[] = {&type_a, &type_b, &type_c};
  for (size_t i = 0; i < 3; i++) {
    printf("fns[%zu](%s, %s, %s) = %lf\n", i, argv[1], argv[2], argv[3],
           powerpower(fns[i], atof(argv[1]), atoi(argv[2]), atoi(argv[3])));
  }
  return 0;
}