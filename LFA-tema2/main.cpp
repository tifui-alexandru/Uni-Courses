#include <bits/stdc++.h>
#include "automaton.cpp"

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    Automaton A;
    fin >> A;
    A.transform();
    fout << A;

    return 0;
}