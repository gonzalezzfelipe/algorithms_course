#include "mergesort.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>


unsigned long custommergesort(int *in, int n) {
  unsigned long flips = 0;

  if (n > 1) {
    flips += custommergesort(in, n / 2);
    flips += custommergesort(in + n / 2, (n + 1) / 2);
  } else {
    return 0;
  }

  int i, j, k;
  i = 0;
  j = 0;

  int *temp;
  temp = (int*)malloc(n * sizeof(int));

  for (k = 0; k < n; k++) {
    if (i >= n / 2) {
      *(temp + k) = *(in + n / 2 + j);
      j++;
    } else {
      if (j >= (n + 1) / 2) {
        *(temp + k) = *(in + i);
        i++;
      }
      else {
        if (*(in + i) <= *(in + n / 2 + j)) {
          *(temp + k) = *(in + i);
          i++;
        } else {
          *(temp + k) = *(in + n / 2 + j);
          j++;
          flips += n / 2 - i;
        }
      }
    }
  }
  for (i = 0; i < n; i++) *(in + i) = *(temp + i);
  return flips;
}
