#ifndef RADIXSORT_H
#define RADIXSORT_H
#include <bits/stdc++.h>

namespace radix {
	const int base = 256;

	void sort(int* __begin, int* __end) {
		std::vector <int> fr(base + 1), used(base), v(__end - __begin);

		for (int step = 0, bk = 1; step < 4; bk *= base, ++step) {
			fill(fr.begin(), fr.end(), 0); // fr[i + 1] = how many elements are in buckets {0..i}
			fill(used.begin(), used.end(), 0); // used[i] = how many elements from bucket i are already processed

			for (int* idx = __begin; idx != __end; ++idx) {
				int curr_bucket = ((*idx) / bk) % base;
				++fr[curr_bucket + 1];
			}

			for (int i = 1; i <= base; ++i)
				fr[i] += fr[i - 1];

			for (int* idx = __begin; idx != __end; ++idx) {
				int curr_bucket = ((*idx) / bk) % base;
				v[fr[curr_bucket] + used[curr_bucket]] = *idx;
				++used[curr_bucket];
			}

			int* idx = __begin;
			for (auto it : v) {
				*idx = it;
				++idx;
			}
		}
	}
}

#endif