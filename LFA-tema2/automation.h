#ifndef AUTOMATION_H
#define AUTOMATIN_H
#include <bits/stdc++.h>

class Automation {
private:
    static const int SIGMA = 27;// T[26] -> lambda transitions, T[0..25] -> normal transitions
    std::string type;
    int no_states, no_trans, no_final_states, initial_state;
    std::unordered_set <int> final_states;
    struct node {
        std::unordered_set <int> T[SIGMA];
        ~node() {
            for (int i = 0; i < SIGMA; ++i)
                T[i].clear();
        }
        void operator = (const node& obj) {
            for (int i = 0; i < SIGMA; ++i)
                T[i] = obj.T[i];
        }
    };
    std::vector <node> G;

    static inline char get_ch(const std::string &s) {
        return (s == "lambda" ? char('z' + 1) : s[0]);
    } 

    static inline std::string get_str(const int &x) {
        return (x == 26 ? "lambda" : std::string(1, char(x + 'a')));
    }

    void lambdaNFA_to_NFA();
    void NFA_to_DFA();
    void DFA_to_minimalDFA();

public:
    inline void add_edge(const int &node1, const int &node2, const std::string &ch) {
        G[node1].T[get_ch(ch) - 'a'].emplace(node2);
    }

    friend std::istream& operator >> (std::istream &in, Automation &obj);
    friend std::ostream& operator << (std::ostream &out, const Automation &obj);

    void transform();
};

#endif