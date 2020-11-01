#include "head.h"

int main()
{
    automata<bool> new_automata;
    new_automata.add_state(0);
    new_automata.add_state(1);
    new_automata.connect_states(0,1,true);
}