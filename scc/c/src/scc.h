#ifndef SCC_H
#define SCC_H


struct Edge {
  int from;
  int to;
};

struct Graph {
  struct Edge *edges;
  int n;
  int m;
};


int get_scc(struct Graph graph, int* scc);


#endif
