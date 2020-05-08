#include "automaton.h"

void Automaton::lambdaNFA_to_NFA() {
    type = "NFA";

     // Completion
    bool new_transitions = true;
    while (new_transitions) {
        new_transitions = false;
        for (int i = 0; i < no_states; ++i) {
            for (auto& nxt: G[i].T[SIGMA - 1]) {
                for (auto& it : G[nxt].T[SIGMA - 1])
                    if (G[i].T[SIGMA - 1].find(it) == G[i].T[SIGMA - 1].end()) {
                        new_transitions = true;
                        G[i].T[SIGMA - 1].emplace(it);
                    }
            }
        }
    }

    // Transition removal
    for (int i = 0; i < no_states; ++i) {
        for (auto& nxt : G[i].T[SIGMA - 1]) {
            for (int letter = 0; letter < SIGMA - 1; ++letter)
                for (auto& it : G[nxt].T[letter])
                    G[i].T[letter].emplace(it);

            if (final_states.find(nxt) != final_states.end())
                final_states.emplace(i);
        }
        G[i].T[SIGMA - 1].clear();
    }

    no_final_states = final_states.size();
    no_trans = 0;
    for (int i = 0; i < no_states; ++i)
        for (int j = 0; j < SIGMA; ++j)
            no_trans += G[i].T[j].size();
}

void Automaton::NFA_to_DFA() {
    int new_no_states = 0, new_no_trans = 0;
    std::map < std::vector <int>, int> new_states;
    std::vector <node> new_G;
    std::unordered_set <int> new_final_states;

    new_states[{initial_state}] = new_no_states++;
    if (final_states.find(initial_state) != final_states.end())
        new_final_states.emplace(new_no_states - 1);    

    std::queue <std::vector <int> > q;
    std::vector <int> top, temp;
    std::unordered_set <int> temp_set;
    q.push({initial_state});

    while (!q.empty()) {
        top = q.front(); q.pop();

        for (int letter = 0; letter < SIGMA; ++letter) {
            temp.clear();
            temp_set.clear();

            for (auto& idx : top) 
                for (auto& nxt : G[idx].T[letter]) {
                    if (temp_set.find(nxt) == temp_set.end()) {
                        temp_set.emplace(nxt);
                        temp.push_back(nxt);
                    }
                }

            if (temp.empty()) continue;

            sort(temp.begin(), temp.end());
            if (new_states.find(temp) == new_states.end()) {
                new_states[temp] = new_no_states++;
                
                bool final = false;
                for (auto& idx : temp)
                    if (final_states.find(idx) != final_states.end()) {
                        final = true;
                        break;
                    }
                if (final) new_final_states.emplace(new_no_states - 1);

                q.push(temp);
            }

            ++new_no_trans;
            int pos = new_states[top];
            if (pos >= new_G.size()) new_G.resize(pos + 1);
            new_G[pos].T[letter].emplace(new_states[temp]);
        }
    }

    type = "DFA";
    no_states = new_no_states; no_trans = new_no_trans; initial_state = 0;
    final_states.clear(); final_states = new_final_states; new_final_states.clear();
    no_final_states = final_states.size();
    G.clear(); G = new_G; new_G.clear();
}

// need some global structures
std::vector < std::vector <int> > adj;
std::unordered_set <int> vis;
std::vector <int> root;

bool BFS(const int &crt_node, int &new_no_states, const std::unordered_set <int> &final_states) {
    if (vis.find(crt_node) != vis.end()) return 0;
    ++new_no_states;
    bool ans = false;
    std::queue <int> q;
    q.push(crt_node); vis.emplace(crt_node);

    while (!q.empty()) {
        int top = q.front(); q.pop();
        root[top] = new_no_states - 1;
        if (final_states.find(top) != final_states.end())
            ans = true;

        for (auto& nxt : adj[top])
            if (vis.find(nxt) == vis.end()) {
                vis.emplace(nxt);
                q.push(nxt);
            }
    }

    return ans;
}

void Automaton::DFA_to_minimalDFA() {
    int new_no_states = 0, new_no_trans = 0;
    std::unordered_set <int> new_final_states;
    std::vector <node> new_G;

    // Eliminate 'dead' nodes
    std::vector <node> Gt(no_states);
    for (int i = 0; i < no_states; ++i)
        for (int letter = 0; letter < SIGMA; ++letter) {
            for (auto& nxt : G[i].T[letter])
                Gt[nxt].T[letter].emplace(i);
        }

    std::unordered_set <int> vis1, vis2;
    std::queue <int> q;

    // Eliminate states not reachable from the initial state
    q.push(initial_state);
    vis1.emplace(initial_state);
    while (!q.empty()) {
        int top = q.front(); q.pop();
        for (int letter = 0; letter < SIGMA; ++letter) {
            for (auto& nxt : G[top].T[letter])
                if (vis1.find(nxt) == vis1.end()) {
                    vis1.emplace(nxt);
                    q.push(nxt);
                }
        }
    }

    // Eliminate states from which one can't reach a final state
    for (auto& st : final_states) {
        q.push(st);
        vis2.emplace(st);
    }
    while (!q.empty()) {
        int top = q.front(); q.pop();
        for (int letter = 0; letter < SIGMA; ++letter) {
            for (auto& nxt : Gt[top].T[letter])
                if (vis2.find(nxt) == vis2.end()) {
                    vis2.emplace(nxt);
                    q.push(nxt);
                }
        }
    }

    // Check if the minimal DFA is null
    bool null_DFA = false;
    if (vis2.find(initial_state) == vis2.end()) null_DFA = true;
    int cnt = 0;
    for (auto& st : final_states)
        if (vis1.find(st) != vis1.end()) ++cnt;
    if (cnt == 0) null_DFA = true;

    if (null_DFA) {
        no_states = no_trans = no_final_states = 0;
        initial_state = -1;
        final_states.clear();
        G.clear();
        type = "Minimal-DFA";
        Gt.clear(); vis1.clear(); vis2.clear();
        return;
    }

    // Actually eliminate the states
    std::vector <int> new_state_corespondent(no_states, 0);
    for (int i = 0; i < no_states; ++i)
        if (vis1.find(i) == vis1.end() or vis2.find(i) == vis2.end())
            new_state_corespondent[i] = -1; // to be eliminated

    Gt.clear(); vis1.clear(); vis2.clear();

    new_no_states = no_states;

    int curr_corespondent = -1;
    for (int i = 0; i < no_states; ++i)
        if (new_state_corespondent[i] != -1) 
            new_state_corespondent[i] = ++curr_corespondent;
        else 
            --new_no_states;
    
    new_G.resize(new_no_states);
    for (int i = 0; i < no_states; ++i) {
        if (new_state_corespondent[i] == -1) continue; // eliminated

        if (final_states.find(i) != final_states.end())
            new_final_states.emplace(i);

        for (int letter = 0; letter < SIGMA; ++letter)
            for (auto& nxt : G[i].T[letter]) {
                if (new_state_corespondent[nxt] == -1) continue; // eliminated
                ++new_no_trans;
                new_G[new_state_corespondent[i]].T[letter].emplace(new_state_corespondent[nxt]); // add new transition
            }
    }

    no_states = new_no_states; no_trans = new_no_trans; initial_state = new_state_corespondent[initial_state];
    final_states.clear(); final_states = new_final_states; new_final_states.clear();
    no_final_states = final_states.size();
    G.clear(); G = new_G; new_G.clear();
    new_state_corespondent.clear();
    new_no_trans = new_no_states = 0;

    // Mark pairs of nodes
    std::set < std::pair <int, int> > unmarked;
    for (int i = 0; i < no_states; ++i)
        for (int j = i + 1; j < no_states; ++j){
            bool _ = (bool)(final_states.find(i) != final_states.end());
            bool __ = (bool)(final_states.find(j) != final_states.end());
            if (!(_ ^ __)) unmarked.emplace(std::make_pair(i, j));
        }

    bool new_mark = true;
    while (new_mark) {
        new_mark = false;
        std::vector < std::pair <int, int> > temp;
        for (auto& p : unmarked)
            for (int letter = 0; letter < SIGMA; ++letter) {
                if (G[p.first].T[letter].empty() or G[p.second].T[letter].empty()) continue;
                int x = *G[p.first].T[letter].begin(), y = *G[p.second].T[letter].begin();
                if (x > y) std::swap(x, y);

                if (unmarked.find(std::make_pair(x, y)) == unmarked.end()) {
                    temp.push_back(p);
                    break;
                }
            }
        
        if (!temp.empty()) new_mark = true;
        for (auto& it : temp)
            unmarked.erase(it);
        temp.clear();
    }

    std::cerr << unmarked.size() << '\n';
    for (auto& it : unmarked)
        std::cerr << it.first << ' ' << it.second << '\n';

    // Combine all unmarked nodes
    adj.resize(no_states);
    for (auto& it : unmarked) {
        adj[it.first].push_back(it.second);
        adj[it.second].push_back(it.first);
    }

    root.resize(no_states);
    for (int i = 0; i < no_states; ++i)
        root[i] = i;

    for (int i = 0; i < no_states; ++i) {
        bool final = BFS(i, new_no_states, final_states);
        if (final) 
            new_final_states.emplace(new_no_states - 1);
    }

    // Construct the new DFA
    new_G.resize(new_no_states);
    for (int i = 0; i < no_states; ++i)
        for (int letter = 0; letter < SIGMA; ++letter) {
            if (G[i].T[letter].empty()) continue;
            int from = root[i], to = root[*G[i].T[letter].begin()];

            if (!new_G[from].T[letter].empty()) continue;
            ++new_no_trans;
            new_G[from].T[letter].emplace(to);
        }
    
    type = "Minimal-DFA";
    no_states = new_no_states; no_trans = new_no_trans; initial_state = root[initial_state];
    final_states.clear(); final_states = new_final_states; new_final_states.clear();
    no_final_states = final_states.size();
    G.clear(); G = new_G; new_G.clear();
    adj.clear(); root.clear(); unmarked.clear(); vis.clear();
}

void Automaton::transform() {
    lambdaNFA_to_NFA();
    NFA_to_DFA();
    // DFA_to_minimalDFA();
}

std::istream& operator >> (std::istream &in, Automaton &obj) {
    in >> obj.type;
    in >> obj.no_states >> obj.no_trans;
    obj.G.resize(obj.no_states);

    for (int idx = 0; idx < obj.no_trans; ++idx) {
        int x, y; std::string str;
        in >> x >> y >> str;
        obj.add_edge(x, y, str);
    }

    in >> obj.initial_state;
    
    in >> obj.no_final_states;
    for (int idx = 0; idx < obj.no_final_states; ++idx) {
        int x; in >> x;
        obj.final_states.emplace(x);
    }

    return in;
}

std::ostream& operator << (std::ostream &out, const Automaton &obj) {
    out << "Type = " << obj.type << '\n';
    out << obj.no_states << " states\n";
    out << obj.no_trans << " transitions\n";

    out << "The transitions are:\n";
    for (int idx = 0; idx < obj.no_states; ++idx) 
       for (int trans = 0; trans < Automaton::SIGMA; ++trans)
            for (auto& it : obj.G[idx].T[trans])
            out << idx << ' ' << it << ' ' << Automaton::get_str(trans) << '\n';

    out << "Initial state: " << obj.initial_state << '\n';
    
    out << obj.no_final_states << " final states:\n";
    for (auto& it : obj.final_states)
        out << it << ' ' << '\n';

    return out;
}