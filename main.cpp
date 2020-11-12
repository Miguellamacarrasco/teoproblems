#include "head.h"

int main()
{
    automata<char> new_automata;
    new_automata.add_state(0);
    new_automata.add_state(1);
    new_automata.add_state(2);
    new_automata.initial_state = new_automata.states[0];
    new_automata.final_states.insert({1,new_automata.states[1]});
    new_automata.connect_states(0,1,'1');
    new_automata.connect_states(0,1,'0');
    new_automata.connect_states(1,0, '1');
    new_automata.connect_states(1,0, '0');
    new_automata.connect_states(2,2,'1');
    new_automata.connect_states(0,2,'0');
    new_automata.Brzozowski();
    new_automata.print();
}