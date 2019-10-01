#include "scc.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int dfs(
		struct Graph graph,
		int *seen,
		int start,
		int* scc,
		int* leader_aux,
		int* finish_time,
		int* finish_time_aux,
		int backwards
	) {
	/* Compute DFS of Graph. */
	int check, next;

	*(seen + start) = 1;
	*(scc + start) = *leader_aux;

	for (int i = 0; i < graph.m; i++) {
		if (backwards) {
			check = graph.edges[i].to;
			next = graph.edges[i].from;
		} else {
			check = graph.edges[i].from;
			next = graph.edges[i].to;
		}
		if (check == start) if (*(seen + next) == 0) {
			dfs(graph, seen, next, scc, leader_aux, finish_time, finish_time_aux, backwards);
		}
	}

	(*finish_time_aux)++;
	*(finish_time + *finish_time_aux) = start;
	return 0;
}


int get_scc(struct Graph graph, int* scc) {
	/* Compute strongly connected components of directed acyclic graph.

	Returns filled array "scc" of size amount_of_nodes + 1 with integers that act
	as the label of the SCC that the node in that position is part of. This means
	that if:

		*(scc + i) == *(scc + j)  ==> i, j are part of the same SCC

	*/
	int *finish_time;
	int *finish_time_aux;
	int *leader_aux;
	int *seen;
	int i;
	int node;

	leader_aux = (int*)malloc(sizeof(int));
	finish_time_aux = (int*)malloc(sizeof(int));
	finish_time = (int*)malloc(sizeof(int) * (graph.n + 1));
	seen = (int*)malloc(sizeof(int) * (graph.n + 1));

	*finish_time_aux = 0;
	for (i = 0; i < graph.n + 1; i++) *(finish_time + i) = i;

	for (int run = 0; run < 2; run++) {
		for (i = 0; i < graph.n + 1; i++) *(seen + i) = 0;
		for (i = graph.n; i > 0; i--) {
			node = *(finish_time + i);
			if (*(seen + node) == 0) {
				*leader_aux = node;
				dfs(graph, seen, node, scc, leader_aux, finish_time, finish_time_aux, run);
			}
		}
	}
	return 0;
}
