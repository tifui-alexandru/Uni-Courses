#ifndef MERGESORT_H
#define MERGESORT_H
#include <bits/stdc++.h>

namespace merge {
	void merge(int* __begin, int* __mid, int* __end) {
		std::vector <int> v;
		int* start1 = __begin;
		int* start2 = __mid;

		while (start1 != __mid and start2 != __end) {
			if (*start1 < *start2) {
				v.emplace_back(*start1);
				++start1;
			}
			else {
				v.emplace_back(*start2);
				++start2;
			}
		}

		for (; start1 != __mid; ++start1) 
			v.emplace_back(*start1);

		for (; start2 != __end; ++start2)
			v.emplace_back(*start2);

		int* idx = __begin;
		for (auto it : v) {
			*idx = it;
			++idx;
		}
	}

	void sort(int* __begin, int* __end) {
		if (__end - __begin == 1) return;

		int* __mid = __begin + (__end - __begin) / 2;
		sort(__begin, __mid);
		sort(__mid, __end);
		merge(__begin, __mid, __end);
	}
}

#endif