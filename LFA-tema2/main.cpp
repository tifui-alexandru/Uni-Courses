#include <bits/stdc++.h>
#include "automation.cpp"

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    Automation A;
    fin >> A;
    A.transform();
    fout << A;

    return 0;
}