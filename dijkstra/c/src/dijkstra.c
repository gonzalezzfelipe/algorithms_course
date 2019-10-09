#include "dijkstra.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#define _INFINITY 100000000


int Graph__from_edges_in_file(struct Graph *graph, char *filename, int n) {
  int i, from, to;
  int m = amount_of_lines(filename);

  graph->m = m;
  graph->n = n;

  graph->edges = malloc(m * sizeof(struct Edge));
  graph->nodes = malloc((n + 1) * sizeof(struct Node));

  // Read all edges from file
  FILE *fp = fopen(filename, "r");
  for (i = 0; i < graph->m; i++) {
		fscanf(
      fp, "%d,%d,%d\n",
      &graph->edges[i].from,
      &graph->edges[i].to,
      &graph->edges[i].weight
    );
	}
  fclose(fp);

  // Set all amounts to zero
  for (i = 0; i < graph->n; i++) {
		graph->nodes[i].amount_downstream = 0;
		graph->nodes[i].amount_upstream = 0;
	}

  // Check memory needed.
	for (i = 0; i < graph->m; i++) {
		// If the node is in "from" of an edge, then that means that it should have
		// another extra downstream. Same if "to" and "upstream".
		graph->nodes[graph->edges[i].from].amount_downstream++;
		graph->nodes[graph->edges[i].to].amount_upstream++;
	}

  // Allocate memory.
	for (i = 1; i < graph->n + 1; i++) {
		graph->nodes[i].downstream = malloc(sizeof(int) * graph->nodes[i].amount_downstream);
		graph->nodes[i].upstream = malloc(sizeof(int) * graph->nodes[i].amount_upstream);
	}

  // Finally fill the nones "from" and "to" vectors
	int *temp_downstream;
	int *temp_upstream;

  temp_upstream = malloc(sizeof(int) * (graph->n + 1));
	temp_downstream = malloc(sizeof(int) * (graph->n + 1));

  for (i = 0; i < graph->n + 1; i++) temp_upstream[i] = 0;
	for (i = 0; i < graph->n + 1; i++) temp_downstream[i] = 0;

  for (i = 0; i < graph->m; i++) {
		from = graph->edges[i].from;
		to = graph->edges[i].to;
		graph->nodes[from].downstream[temp_downstream[from]] = to;
		graph->nodes[to].upstream[temp_upstream[to]] = from;
		temp_downstream[from]++;
		temp_upstream[to]++;
	}

  free(temp_upstream);
	free(temp_downstream);

  return 0;
}


int dijkstra(struct Graph graph, int start, int *distances) {
  int meassured[graph.n + 1];
  int value;
  int min_value;
  int min_from;
  int min_to;

  for (int i = 0; i < graph.n + 1; i++) meassured[i] = 0;

  meassured[start] = 1;
  distances[start] = 0;

  for (int i = 1; i < graph.n; i++) {

    min_value = _INFINITY;
    min_from = -1;
    min_to = -1;

    for (int edge = 0; edge < graph.m; edge++) {
      if (meassured[graph.edges[edge].from] == 1) {
        if (meassured[graph.edges[edge].to] == 0) {
          value = distances[graph.edges[edge].from] + graph.edges[edge].weight;
          if (value <= min_value) {
            min_value = value;
            min_from = graph.edges[edge].from;
            min_to = graph.edges[edge].to;
          }
        }
      }
    }

    if (min_from > 0) {
      meassured[min_to] = 1;
      distances[min_to] = min_value;
    }
    else return 1;
  }

  return 0;
}
