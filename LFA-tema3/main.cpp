#include "regularGrammar.h"

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    Automaton DFA;
    fin >> DFA;
    fout << DFA.getRegEx() << "\n\n";

    RegularGrammar Grammar;
    fin >> Grammar;
    fout << Grammar.convert_to_automaton();

    return 0;
}