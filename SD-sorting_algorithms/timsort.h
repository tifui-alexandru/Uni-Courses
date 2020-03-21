#ifndef TIMSORT_H
#define TIMSORT_H
#include <bits/stdc++.h>
#include "mergesort.h"
#include "selectionsort.h"

namespace tim {
	void sort(int* __begin, int* __end) {
		const int run = 32;
		int *start, *stop, *mid;

		for (start = __begin; __end - start > 0; start += run) {
			stop = start + run;
			if (__end - stop < 0) stop = __end;
			selection::sort(start, stop);
		}

		for (int sz = run; sz < __end - __begin; sz <<= 1)
			for (start = __begin; __end - start > 0; start += (sz << 1)) {
				mid = start + sz;
				if (__end - mid < 0) continue;
				stop = start + (sz << 1);
				if (__end - stop < 0) stop = __end;

				merge::merge(start, mid, stop);
			}
	}
}

#endif