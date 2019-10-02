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

  _graph = malloc(sizeof(struct Graph));
  _graph->edges = malloc(m * sizeof(struct Edge));
  _graph->nodes = malloc(m * sizeof(struct Node));
  _graph->n = n;
  _graph->m = amount_of_lines(filename);
  init_graph(filename, _graph);
  graph = *_graph;

  scc = (int*)malloc((n + 1) * sizeof(int));
  for (int i = 0; i < n + 1; i++) scc[i] = 0;
  get_scc(graph, scc);

  int *counter;
	counter = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i < n + 1; i++) counter[i] = 0;
	for (int i = 1; i < n + 1; i++) counter[scc[i]]++;

	// Print sizes
	for (int i = 1; i < n + 1; i++) if (counter[i] >= 100) printf("Size: %d\n", counter[i]);

  free(_graph);
  free(counter);
  return 0;
}
