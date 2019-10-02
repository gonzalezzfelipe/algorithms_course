#ifndef SCC_H
#define SCC_H


struct Edge {
  int from;
  int to;
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


int get_scc(struct Graph graph, int* scc);


#endif
