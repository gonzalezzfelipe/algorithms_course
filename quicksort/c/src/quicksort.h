#ifndef QUICKSORT_H
#define QUICKSORT_H

enum pivot_kind {first, last, median};
unsigned long customquicksort(int *in, int n, enum pivot_kind pivot);

#endif
