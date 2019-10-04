#include "scc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>


int amount_of_lines(char *filename) {
	FILE *fp;
	int count;
	char c; // To store a character read from file

	fp = fopen(filename, "r");
	count = 0;
	for (c = getc(fp); c != EOF; c = getc(fp)) if (c == '\n') count++;
	fclose(fp);
	return count;
}


int readfile(char *filename, struct Graph *graph){
  /* Load numbers in file into vector.*/
  FILE *fp = fopen(filename, "r");
  for (int i = 0; i < graph->m; i++) {
		fscanf(fp, "%d %d \n", &graph->edges[i].from, &graph->edges[i].to);
	}
  fclose(fp);
  return 0;
}


int fill_nodes(struct Graph *graph) {
	int i, from, to;
	// Init.
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


int init_graph(char *filename, struct Graph *graph) {
	readfile(filename, graph);
	fill_nodes(graph);
	return 0;
}


int print_sideways(int* temp, int n) {
  for (int m = 0; m < n; m++) {
    printf("%d,", *(temp + m));
  }
  printf("\n");
  return 0;
}
