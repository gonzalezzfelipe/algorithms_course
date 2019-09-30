#ifndef HELPERS_H
#define HELPERS_H

#include "undirected_graph.h"

int readfile(char *filenane, struct Edge *edges, int n);
int amount_of_lines(char *filename);
int progress(int done, int total, unsigned long start);
unsigned long get_epoch_in_microseconds();
float random_numb(int *semilla);

#endif
