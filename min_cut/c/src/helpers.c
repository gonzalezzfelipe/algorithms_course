#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#define A 16807
#define M 2147483647
#define Q 127773
#define R 2836
#define S 260572
#define T 10000
#define B 10

#define _EMPTY '_'
#define _FULL '#'
#define _TOTAL 70


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


int readfile(char *filename, struct Edge *edges, int m){
  /* Load numbers in file into vector.*/
  FILE *fp = fopen(filename, "r");
  for (int i = 0; i < m; i++) fscanf(fp, "%d,%d\n", &edges[i].from, &edges[i].to);
  fclose(fp);
  return 0;
}


unsigned long get_epoch_in_microseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  unsigned long ret = tv.tv_usec;
  ret += (tv.tv_sec * 1000000);
  return ret;
}


int progress(int done, int total, unsigned long start) {
  /* Print progressbar to console. */
  char _progress[_TOTAL];

  float lapsed = (float)(get_epoch_in_microseconds() - start);
  int eta = (int)(lapsed * (total / 1.0 / done - 1) / 1000000);
  if (eta < 0) eta = 0;

  int covered = (int)(_TOTAL * done / 1.0 / total);
  for (int i = 0; i < _TOTAL; i++) {
    if (i < covered) _progress[i] = _FULL;
    else _progress[i] = _EMPTY;
  }
  printf(
    "\rProgress: |%s| (%.2f %%) ETA: %02d:%02d:%02d ",
    _progress, 100 * done / 1.0 / total,
    eta / 3600,  // Hours
    (eta % 3600) / 60,  // Minutes
    eta % 60  // Seconds
  );
  fflush(stdout);
  if (done == total) printf("\n");
  return 0;
}


float random_numb(int *semilla) {
   /*
   Devuelve un numero aleatorio entre 0.0 y 1.0
   a partir de una semilla dada. Se usa el metodo
   de Park y Miller
   */

  int k;
  float x;

  k = (*semilla) / Q;
  *semilla = A * (*semilla - k * Q) - R * k;
  if (*semilla < 0) *semilla += M;

  x = (*semilla)*(1.0 / M);

  return x;
}
