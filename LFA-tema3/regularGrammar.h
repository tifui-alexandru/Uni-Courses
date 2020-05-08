#ifndef REGULARGRAMMAR_H
#define REGULARGRAMMAR_H

#include "automaton.h"

class RegularGrammar {
private:
    std::unordered_map <std::string, std::vector <std::string> > production_rules;

public:
    friend std::istream& operator >> (std::istream& in, RegularGrammar& obj);
    Automaton convert_to_automaton() const;
};

#endif