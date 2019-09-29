#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "helpers.h"
#include "undirected_graph.h"


int main(int argc, char *argv[]){
  struct Edge *edges;
  int n;
  int *seed;

  char *filename = argv[1];
  int m = amount_of_lines(filename);

  sscanf(argv[2], "%d", &n);

  seed = (int*)malloc(m * sizeof(int));
  if (argc >= 3) sscanf(argv[2], "%d", &*seed);
  else *seed = 0;

  edges = (struct Edge*)malloc(m * sizeof(struct Edge));

  readfile(filename, edges, m);

  int minimum_cut = min_cut(edges, n, m, seed);
  int aux;
  unsigned long start = get_epoch_in_microseconds();
  int amount_of_times = 10 * n * (n - 1) / 2 * (int)log((double)n);

  printf("Initial minimum cut: %d\n", minimum_cut);
  for (int i = 1; i < amount_of_times; i++) {
    aux = min_cut(edges, n, m, seed);
    progress(i, amount_of_times - 1, start);
    if (aux < minimum_cut) minimum_cut = aux;
  }
  printf("Minimum cut: %d\n", minimum_cut);
  return 0;
}
