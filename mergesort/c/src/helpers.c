#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


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


int readfile(char *filename, int *vector, int n){
  /* Load numbers in file into vector.*/
  FILE *fp = fopen(filename, "r");
  for (int i = 0; i < n; i++) fscanf(fp, "%d\n", vector + i);
  fclose(fp);
  return 0;
}


int print_vector(int *vector, int n) {
  for (int i = 0; i < n; i++) printf("%d\n", *(vector + i));
  return 0;
}


int print_sideways(int* temp, int n) {
  for (int m = 0; m < n; m++) {
    printf("%d,", *(temp + m));
  }
  printf("\n");
  return 0;
}
