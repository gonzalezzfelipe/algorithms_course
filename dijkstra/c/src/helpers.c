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


int print_sideways(int* temp, int n) {
  for (int m = 0; m < n; m++) {
    printf("%d,", *(temp + m));
  }
  printf("\n");
  return 0;
}
