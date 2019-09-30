#include "undirected_graph.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int choose_random_from_history(int *history, int amount_of_nodes, int *seed) {
	int a = -1;
	int i;
	while (a < 0) {
		i = (int)(random_numb(seed) * (amount_of_nodes + 1)) + 1;
		a = *(history + i);
	}
	return i;
}


int true_node(int j, int *history) {
	while (*(history + j) < 0) j = - *(history + j);
	return j;
}


int update_history(int *history, int amount_of_nodes) {
	int real_value;
	for (int i = 1; i < amount_of_nodes + 1; i++) {
		real_value = *(history + i);
		while (real_value < 0) real_value = *(history - real_value);
		*(history + i) = real_value;
	}
	return 0;
}


int min_cut(struct Edge *edges, int amount_of_nodes, int amount_of_edges, int *seed) {
	/* Scroll through graph to find min cut. */
	int *history;
	int i, j;

	// Create history vector.
	history = (int*)malloc((amount_of_nodes + 1) * sizeof(int));
	for (int n = 0; n < amount_of_nodes + 1; n++) *(history + n) = n;

	// Populate history vector, making negative the nodes that are to be merged.
	for (int k = 0; k < amount_of_nodes - 1; k++) {
		i = choose_random_from_history(history, amount_of_nodes, seed);
		j = i;
		while (j == i) j = choose_random_from_history(history, amount_of_nodes, seed);
		*(history + j) = -i;
	}

	update_history(history, amount_of_nodes);

	// Count all the edges that are between two different nodes.
	int cut = 0;
	for (int k = 0; k < amount_of_edges; k++) {
		if (history[edges[k].from] != history[edges[k].to]) cut++;
	}
	return cut;
}
