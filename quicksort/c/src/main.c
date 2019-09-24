#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "helpers.h"
#include "quicksort.h"


int main(int argc, char *argv[]){
  int *vector;
  int n;
  unsigned long comparisons;

  char *filename = argv[1];
  int pivot;
  sscanf(argv[2], "%d", &pivot);
  n = amount_of_lines(filename);

  vector = (int*)malloc(n * sizeof(int));

  readfile(filename, vector, n);

  comparisons = customquicksort(vector, n, pivot);
  printf("Amount of comparisons: %lu\n", comparisons);
  return 0;
}
