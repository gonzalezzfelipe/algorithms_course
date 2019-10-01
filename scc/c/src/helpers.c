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
  for (int i = 0; i < graph->m; i++) fscanf(fp, "%d %d \n", &graph->edges[i].from, &graph->edges[i].to);
  fclose(fp);
  return 0;
}
