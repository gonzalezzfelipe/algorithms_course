#ifndef DIJKSTRA_H
#define DIJKSTRA_H


struct Edge {
  int from;
  int to;
  int weight;
};


struct Node {
  int amount_downstream;
  int *downstream;
  int amount_upstream;
  int *upstream;
};


struct Graph {
  struct Edge *edges;
  struct Node *nodes;
  int n;
  int m;
};


int Graph__from_edges_in_file(struct Graph *graph, char *filename, int n);
int dijkstra(struct Graph graph, int start, int *distances);


#endif
