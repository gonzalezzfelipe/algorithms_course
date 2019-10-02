#ifndef HELPERS_H
#define HELPERS_H

#include "scc.h"

int readfile(char *filenane, struct Graph *graph);
int fill_nodes(struct Graph *graph);
int amount_of_lines(char *filename);
int init_graph(char *filename, struct Graph *graph);

#endif
