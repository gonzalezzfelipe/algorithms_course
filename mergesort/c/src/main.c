#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "helpers.h"
#include "mergesort.h"


int main(int argc, char *argv[]){
  int *vector;
  int n;
  unsigned long flips;

  char *filename = argv[1];
  n = amount_of_lines(filename);

  vector = (int*)malloc(n * sizeof(int));

  readfile(filename, vector, n);

  flips = custommergesort(vector, n);
  printf("Amount of flips: %lu\n", flips);
  return 0;
}
