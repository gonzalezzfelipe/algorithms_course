#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "helpers.h"
#include "dijkstra.h"


int main(int argc, char *argv[]){
  struct Graph *_graph;
  struct Graph graph;
  int n;
  int *distances;

  char *filename = argv[1];

  sscanf(argv[2], "%d", &n);

  _graph = malloc(sizeof(struct Graph));
  Graph__from_edges_in_file(_graph, filename, n);
  graph = *_graph;

  distances = (int*)malloc((n + 1) * sizeof(int));
  for (int i = 0; i < n + 1; i++) distances[i] = 0;
  printf("%d\n", dijkstra(graph, 1, distances));

	// Print distances
  printf("Distance 7: %d\n", distances[7]);
  printf("Distance 37: %d\n", distances[37]);
  printf("Distance 59: %d\n", distances[59]);
  printf("Distance 82: %d\n", distances[82]);
  printf("Distance 99: %d\n", distances[99]);
  printf("Distance 115: %d\n", distances[115]);
  printf("Distance 133: %d\n", distances[133]);
  printf("Distance 165: %d\n", distances[165]);
  printf("Distance 188: %d\n", distances[188]);
  printf("Distance 197: %d\n", distances[197]);

  free(_graph);
  return 0;
}
