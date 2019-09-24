#include "quicksort.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>


int choose_pivot(int *in, int n, enum pivot_kind pivot) {
  if (pivot == first) return 0;
  else if (pivot == last) return n - 1;
  else {
    int a, b, c;
    a = *in;
    b = *(in + (n - 1) / 2);
    c = *(in + n - 1);
    if (a < b) {
      if (b < c) return (n - 1) / 2;
      else {
        if (a < c) return n - 1;
        else return 0;
      }
    } else {
      if (b > c) return (n - 1) / 2;
      else {
        if (a > c) return n - 1;
        else return 0;
      }
    }
  }
}


int swap(int *in, int i, int j) {
  /* Swap values between indexes i and j */
  if (i == j) return 0;
  *(in + i) = *(in + i) + *(in + j);
  *(in + j) = *(in + i) - *(in + j);
  *(in + i) = *(in + i) - *(in + j);
  return 0;
}


unsigned long customquicksort(int *in, int n, enum pivot_kind pivot) {
  unsigned long comparisons = 0;
  if (n <= 1) return 0;

  swap(in, 0, choose_pivot(in, n, pivot));  // Pivot always goes first.
  int i, j;
  i = 1;

  for (j = 1; j < n; j++) {
    if (*(in + j) < *in) {
      swap(in, i, j);
      i++;
    }
  }
  swap(in, 0, i - 1);

  comparisons += customquicksort(in, i - 1, pivot);
  comparisons += customquicksort(in + i, n - i, pivot);
  comparisons += n - 1;
  return comparisons;
}
