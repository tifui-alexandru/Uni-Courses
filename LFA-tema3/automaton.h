#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <bits/stdc++.h>

class Automaton {
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

    inline void construct_edge(const int &node1, const int &node2, const std::string &ch) {
        ++no_trans;
        int max = std::max(node1, node2);
        if (max >= no_states) {
            no_states = max + 1;
            G.resize(no_states);
        }
        add_edge(node1, node2, ch);
    }

    inline int get_no_states() const{
        return no_states;
    }

    inline void set_initial_state(const int& node) {
        initial_state = node;
    }

    inline void set_final_state(const int& node) {
        if (final_states.find(node) == final_states.end()) {
            ++no_final_states;
            final_states.emplace(node);
        }
    }

    Automaton(int noStates = 0) : no_states(noStates), no_trans(0), type("Lambda-NFA"), no_final_states(0), initial_state(0) {
        G.resize(no_states);
    }

    friend std::istream& operator >> (std::istream &in, Automaton &obj);
    friend std::ostream& operator << (std::ostream &out, const Automaton &obj);

    void transform();
};

#endif