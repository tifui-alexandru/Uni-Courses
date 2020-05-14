#include "regularGrammar.h"

std::istream& operator >> (std::istream& in, RegularGrammar& obj) {
    std::string s1, s2;
    while (in >> s1 >> s2) {
        obj.production_rules[s1].emplace_back(s2);
    }
    return in;
}

Automaton RegularGrammar::convert_to_automaton() const {
    int automaton_states = 0;
    std::unordered_map <std::string, int> state_number;

    for (auto& it : production_rules) {
        if (state_number.find(it.first) == state_number.end()) {
            state_number[it.first] = automaton_states;
            ++automaton_states;
        }

        for (auto& itt : it.second) {
            if (itt == "lambda") continue;

            std::string temp = itt;
            if (islower(temp[0])) {
                temp = itt.substr(1);
            }

            if (temp.size() == 0) continue;

            if (state_number.find(temp) == state_number.end()) {
                state_number[temp] = automaton_states;
                ++automaton_states;
            }
        }
    }

    ++automaton_states; // the final state

    Automaton ret(automaton_states);

    for (auto& it : production_rules) 
        for (auto& itt : it.second) {
            if (itt == "lambda") ret.construct_edge(state_number[it.first], automaton_states - 1, "lambda");
            else if (islower(itt[0])) {
                std::string s1, s2;
                s1.push_back(itt[0]);
                s2 = itt.substr(1);

                if (s2.size() > 0) {
                    ret.construct_edge(state_number[it.first], state_number[s2], s1);
                }
                else {
                    ret.construct_edge(state_number[it.first], automaton_states - 1, s1);
                }
            }
            else {
                ret.construct_edge(state_number[it.first], state_number[itt], "lambda");
            }
        }

    ret.set_initial_state(state_number["S"]);
    ret.set_final_state(automaton_states - 1);
    ret.transform();
    return ret;
}