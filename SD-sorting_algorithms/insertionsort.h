#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include <bits/stdc++.h>

namespace insertion {
	void sort(int* __begin, int* __end) {
		for (int* idx = __begin + 1; idx != __end; ++idx) {
			int temp = *idx;
			int* p;
			for (p = idx - 1; p - __begin >= 0 and *p > temp; --p)
				*(p + 1) = *p;
			*(p + 1) = temp;
		}
	}
}

#endif