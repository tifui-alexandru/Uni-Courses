#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution <int> _random(0, INT_MAX);

const int Nmax = 1e7 + 5;
string test_type[] = {"numere generate random", "ordine descrescatoare", "ordine aproape crescatoare", "distributie neuniforma"};
int v[Nmax];

void gen_test_type0(const int &N, const int &V) {
	for (int i = 1; i <= N; ++i) 
		v[i] = _random(rnd) % (V + 1);
}

void gen_test_type1(const int &N, const int &V) {
	gen_test_type0(N, V);
	sort(v + 1, v + N + 1, greater <int>());
}

void gen_test_type2(const int &N, const int &V) {
	gen_test_type0(N, V);
	sort(v + 1, v + N + 1);
	int start, stop;
	while (true) {
		start = _random(rnd) % N + 1;
		stop = start + N / 5;
		if (stop <= N) break;
	}
	random_shuffle(v + start, v + stop + 1);
}

void gen_test_type3(const int &N, const int &V) {
	int dist = N / 10; // 10% distribution
	vector <int> values(dist);
	unordered_set <int> taken_values;
	for (auto &it : values) {
		it = _random(rnd) % (dist + 1);
		while (taken_values.find(it) != taken_values.end())
			it = _random(rnd) % (dist + 1);
	}

	for (int i = 1; i <= N; ++i)
		v[i] = values[_random(rnd) % dist];
}

void print_test(const int &N, const int &V, const int &t) {
	cout << N << ' ' << V << '\n' << test_type[t] << '\n';

	switch (t) {
		case 0:
			gen_test_type0(N, V);
			break;
		case 1:
			gen_test_type1(N, V);
			break;
		case 2:
			gen_test_type2(N, V);
			break;
		case 3:
			gen_test_type3(N, V);
			break;
	}

	for (int i = 1; i <= N; ++i)
		cout << v[i] << ' ';
	cout << '\n';
} 

int main() {
	freopen("input.txt", "w", stdout);
	int N, V;

	cout << 20 << '\n'; // number of tests

	// for (int t = 0; t < 4; ++t) {
	// 	print_test(20, 20, t);
	// 	print_test(1e3, 1e3, t);
	// 	print_test(1e4, 1e7, t);
	// 	print_test(1e5, 1e9, t);
	// 	print_test(5e5, INT_MAX, t);
	// }

	print_test(5e6, INT_MAX, 0);

	return 0;
}