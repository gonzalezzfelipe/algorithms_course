#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "helpers.h"
#include "scc.h"


int main(int argc, char *argv[]){
  struct Graph *_graph;
  struct Graph graph;
  int n;
  int *scc;

  char *filename = argv[1];
  int m = amount_of_lines(filename);

  sscanf(argv[2], "%d", &n);

  _graph = (struct Graph*)malloc(sizeof(struct Graph));
  _graph->edges = (struct Edge*)malloc(m * sizeof(struct Edge));
  _graph->n = n;
  _graph->m = amount_of_lines(filename);
  readfile(filename, _graph);
  graph = *_graph;

  scc = (int*)malloc((n + 1) * sizeof(int));
  get_scc(graph, scc);

  int *counter;
  counter = (int*)malloc(sizeof(int) * (n + 1));
  for (int i = 0; i < n + 1; i++) counter[i] = 0;
  for (int i = 1; i < n + 1; i++) counter[scc[i]]++;

  // print sizes
  for (int i = 0; i < n + 1; i++) if (counter[i] != 0) printf("Size: %d\n", counter[i]);
  return 0;
}
