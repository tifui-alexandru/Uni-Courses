#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <bits/stdc++.h>

namespace quick {
	std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution <int> _random(0, INT_MAX);
	void sort(int* __begin, int* __end) {
	    int pivot = *(__begin + (_random(rnd) % (__end - __begin)));
	    int *start = __begin;
	    int *stop = __end - 1;

	    while (stop - start >= 0) {
	    	while (*start < pivot) ++start;
	    	while (*stop > pivot) --stop;

	    	if (stop - start >= 0) {
	    		std::swap(*start, *stop);
	    		++start;
	    		--stop;
	    	}
	    }

	    if (stop - __begin > 0)
	    	sort(__begin, stop + 1);
	    if (__end - start - 1 > 0)
	    	sort(start, __end);
	}
}

#endif