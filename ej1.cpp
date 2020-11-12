#include "head.h"

int main()
{
    automata<char> new_automata;
    new_automata.add_state(0);
    new_automata.add_state(1);
    new_automata.add_state(2);
    new_automata.add_state(3);
    new_automata.add_state(4);
    new_automata.initial_state = new_automata.states[0];
    new_automata.final_states.insert({0,new_automata.states[0]});
    new_automata.final_states.insert({2,new_automata.states[2]});
    new_automata.final_states.insert({4,new_automata.states[4]});
    new_automata.connect_states(0,0,'a');
    new_automata.connect_states(0,1,'b');
    new_automata.connect_states(1,3,'b');
    new_automata.connect_states(3,2,'a');
    new_automata.connect_states(2,2,'a');
    new_automata.connect_states(3,3,'b');
    new_automata.connect_states(1,2,'a');
    new_automata.connect_states(2,4,'b');
    new_automata.connect_states(4,4,'a');
    new_automata.connect_states(4,4,'b');
    new_automata.Brzozowski();
    
}