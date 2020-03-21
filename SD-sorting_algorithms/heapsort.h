#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <bits/stdc++.h>

namespace heap {
	#define ls(node) ((node << 1) + 1)
	#define rs(node) (ls(node) + 1)

	void shift(std::vector <int> &H, int idx, int sz) {
		while (true) {
			int min_son = ls(idx);

			if (min_son >= sz) break;
			if (rs(idx) < sz and H[rs(idx)] < H[ls(idx)]) min_son = rs(idx);
			if (H[min_son] >= H[idx]) break;

			std::swap(H[idx], H[min_son]);
			idx = min_son;
		}
	}

	void make_min_heap(std::vector <int> &H) {
		for (int idx = (H.size() >> 1) - 1; idx >= 0; --idx)
			shift(H, idx, H.size());
	}

	int erase_min(std::vector <int> &H, int sz) {
		std::swap(H[0], H[sz - 1]);
		shift(H, 0, sz - 1);
		return H[sz - 1];
	}

	void sort(int* __begin, int* __end) {
		std::vector <int> H;
		for (int* idx = __begin; idx != __end; ++idx) 
			H.emplace_back(*idx);

		make_min_heap(H);
		for (int* idx = __begin; idx != __end; ++idx)
			*idx = erase_min(H, H.size() - (idx - __begin));
	}
}

#endif