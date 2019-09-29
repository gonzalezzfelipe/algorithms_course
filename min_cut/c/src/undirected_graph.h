#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

struct Edge {
  int from;
  int to;
};

int min_cut(struct Edge *edges, int amount_of_nodes, int amount_of_edges, int *seed);

#endif
