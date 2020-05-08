#include "regularGrammar.h"

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    RegularGrammar Grammar;
    fin >> Grammar;
    fout << Grammar.convert_to_automaton();

    return 0;
}