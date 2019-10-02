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
  int i;
	*(seen + start) = 1;
	*(scc + start) = *leader_aux;

	if (backwards == 1) {
		for (i = 0; i < graph.nodes[start].amount_upstream; i++) {
			if (*(seen + graph.nodes[start].upstream[i]) == 0) {
				dfs(
					graph,
					seen,
					graph.nodes[start].upstream[i],
					scc,
					leader_aux,
					finish_time,
					finish_time_aux,
					backwards
				);
			}
		}
    (*finish_time_aux)++;
  	*(finish_time + *finish_time_aux) = start;
	} else {
		for (i = 0; i < graph.nodes[start].amount_downstream; i++) {
      if (*(seen + graph.nodes[start].downstream[i]) == 0) {
				dfs(
					graph,
					seen,
					graph.nodes[start].downstream[i],
					scc,
					leader_aux,
					finish_time,
					finish_time_aux,
					backwards
				);
      }
		}
	}
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

	leader_aux = malloc(sizeof(int));
	finish_time_aux = malloc(sizeof(int));
	finish_time = malloc(sizeof(int) * (graph.n + 1));
	seen = malloc(sizeof(int) * (graph.n + 1));
  for (i = 0; i < graph.n + 1; i++) *(finish_time + i) = i;

	for (int run = 1; run >= 0; run--) {
    *finish_time_aux = 0;
  	for (i = 0; i < graph.n + 1; i++) *(seen + i) = 0;

		for (i = graph.n; i > 0; i--) {
			node = *(finish_time + i);
			if (*(seen + node) == 0) {
				*leader_aux = node;
				dfs(graph, seen, node, scc, leader_aux, finish_time, finish_time_aux, run);
			}
		}
	}

  free(leader_aux);
  free(finish_time);
  free(finish_time_aux);
  free(seen);
	return 0;
}
