#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class NFA {
private:
	static const int SIGMA = 26;
	int no_states, no_trans, no_final_states, initial_state;
	unordered_set <int> final_states;
	struct node {
		vector <int> T[SIGMA];
	};
	vector <node> G;

	static inline bool cmp(const string &lsh, const string &rsh) {
		if (lsh.size() == rsh.size())
			return lsh < rsh;
		return lsh.size() < rsh.size();
	}

public:
	void add_edge(const int &node1, const int &node2, const char &ch) {
		G[node1].T[ch - 'a'].push_back(node2);
	}

	friend istream& operator >> (istream &in, NFA &obj) {
		in >> obj.no_states >> obj.no_trans;
		obj.G.resize(obj.no_states);

		for (int idx = 0; idx < obj.no_trans; ++idx) {
			int x, y; char ch;
			in >> x >> y >> ch;
			obj.add_edge(x, y, ch);
		}

		in >> obj.initial_state >> obj.no_final_states;
		for (int idx = 0; idx < obj.no_final_states; ++idx) {
			int x; in >> x;
			obj.final_states.emplace(x);
		}

		return in;
	}

	bool check(const string &s) {
		queue < pair <int, int> > q;
		set < pair <int, int> > in_queue;
		q.push({initial_state, 0});
		in_queue.emplace(make_pair(initial_state, 0));

		while (!q.empty()) {
			int node = q.front().first;
			int letter = q.front().second;
			q.pop();
			in_queue.erase(make_pair(node, letter));

			if (letter == s.size()) {
				if (final_states.find(node) != final_states.end()) return true;
				continue;
			}

			for (auto &it : G[node].T[s[letter] - 'a'])
				if (in_queue.find(make_pair(it, letter + 1)) == in_queue.end()) {
					in_queue.emplace(make_pair(it, letter + 1));
					q.push({it, letter + 1});
				}
		}
		return false;
	}

	void get_words() {
		queue < pair <int, string> > q;
		set < pair <int, string> > in_queue;
		q.push({initial_state, ""});
		in_queue.emplace(make_pair(initial_state, ""));
		unordered_set <string> words;

		while (!q.empty() and words.size() < 100) {
			int node = q.front().first;
			string word = q.front().second;
			q.pop();
			in_queue.erase(make_pair(node, word));

			if (final_states.find(node) != final_states.end())
				words.emplace(word);
			if (words.size() >= 100) break;

			for (int i = 0; i < SIGMA; ++i)
				for (auto& it : G[node].T[i]) {
					word.push_back(char(i + 'a'));
					if (in_queue.find(make_pair(it, word)) == in_queue.end()) {
						in_queue.emplace(make_pair(it, word));
						q.push({it, word});
					}
					word.pop_back();
				}
		}

		vector <string> ans;
		for (auto& it : words)
			ans.emplace_back(it);
		sort(ans.begin(), ans.end(), cmp);

		fout << "Cele mai mici " << ans.size() << " de cuvinte acceptate sunt:\n"; // ans.size() < 100 => automtul nu accepta 100 de cuvinte
		for (auto &it : ans)
			fout << it << '\n';
	}
};

int main() {
	NFA A;
	fin >> A;
	int Q; fin >> Q;
	string s;
	while (Q--) {
		fin >> s;
		fout << A.check(s) << '\n';
	}
	A.get_words();

	return 0;
}