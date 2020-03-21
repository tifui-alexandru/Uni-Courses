#include <bits/stdc++.h>
#include "mergesort.h"
#include "quicksort.h"
#include "heapsort.h"
#include "radixsort.h"
#include "timsort.h"
#include "selectionsort.h"

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const std::string sorting_alg[] = {"selection-sort", "mergesort", "timsort", "quicksort", "heapsort", "radixsort", "STL sort"};
double sorting_time[7];

void get_sorted_arr(int* __begin1, int* __end1, int* __begin2, int* __end2) {
	for (int* p2 = __begin2, *p1 = __begin1; p1 != __end1; ++p1, ++p2)
		*p2 = *p1;
	std::sort(__begin2, __end2);
}

bool check(int* __begin1, int* __end1, int* __begin2, int* __end2) {
	for (int* p2 = __begin2, *p1 = __begin1; p1 != __end1; ++p1, ++p2)
		if (*p1 != *p2) return false;
	return true;
}

void test_sort_alg(int idx, int* v, int N, int* sorted_arr) {
	clock_t start, stop;
	switch (idx) {
		case 0:
			start = clock();
			selection::sort(v, v + N);
			stop = clock();
			break;
		case 1:
			start = clock();
			merge::sort(v, v + N);
			stop = clock();
			break;
		case 2:
			start = clock();
			tim::sort(v, v + N);
			stop = clock();
			break;
		case 3:
			start = clock();
			quick::sort(v, v + N);
			stop = clock();
			break;
		case 4:
			start = clock();
			heap::sort(v, v + N);
			stop = clock();
			break;
		case 5:
			start = clock();
			radix::sort(v, v + N);
			stop = clock();
			break;
		case 6:
			start = clock();
			std::sort(v, v + N);
			stop = clock();
			break;
	}
	if (!check(v, v + N, sorted_arr, sorted_arr + N)) {
		fout << "SORTARE GRESITA!!!\n";
		return;
	}
	sorting_time[idx] = (double)(stop - start) / CLOCKS_PER_SEC;
	fout << std::fixed << std::setprecision(6);
	fout << sorting_alg[idx] << " sorteaza in " << sorting_time[idx] << " secunde\n";
}

int main() {
	int no_tests, Vmax, N;
	int *v, *w, *sorted_arr;
	std::string test_type;

	fin >> no_tests;
	while (no_tests--) {
		fin >> N >> Vmax;
		fin.get();
		std::getline(fin, test_type);
		v = new int[N + 5]();
		w = new int[N + 5]();
		sorted_arr = new int[N + 5]();

		for (int i = 0; i < N; ++i)
			fin >> v[i];
		get_sorted_arr(v, v + N, sorted_arr, sorted_arr + N);

		double minn = INT_MAX;
		int pos_min;
		fout << "Tipul testului: " << test_type << "\nDimensiunea vectorului: " << N << "\nValoarea maxima: " << Vmax << "\n";
		for (int i = 0; i < 7; ++i) {
			std::copy(v, v + N, w);
			test_sort_alg(i, w, N, sorted_arr);
			if (i < 6 and sorting_time[i] < minn) {
				minn = sorting_time[i];
				pos_min = i;
			}
		}
		fout << "Cea mai rapida sortare manuala este " << sorting_alg[pos_min] << "\n\n";

		delete v;
		delete w;
		delete sorted_arr;
	}

	fin.close();
	fout.close();

	return 0;
}