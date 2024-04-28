double power(double a, int b) {
  if (b == 0) return 1;
  return (power(a, b - 1)) * a;
}
double multiply(double a, int b) { return ((double)b) * a; }
double divide(double a, int b) { return a / ((double)b); }
