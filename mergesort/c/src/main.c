#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "helpers.h"
#include "mergesort.h"


int main(int argc, char *argv[]){
  int *vector;
  int *out;
  int n;
  unsigned long flips;

  char *filename = argv[1];
  n = amount_of_lines(filename);

  vector = (int*)malloc(n * sizeof(int));
  out = (int*)malloc(n * sizeof(int));

  readfile(filename, vector, n);

  flips = custommergesort(vector, out, n);
  printf("Amount of flips: %lu\n", flips);
  return 0;
}
