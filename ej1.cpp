#include "head.h"

int main()
{
    automata<char> new_automata;
    int number_of_states = 0;
    std::cin >> number_of_states;
    for (int i = 0 ; i < number_of_states; i++)
    {
        new_automata.add_state(i);
    }
    int l = 0;
    int final_states = 0;
    std::cin >> l;
    new_automata.initial_state = new_automata.states[l];
    std::cin >> final_states;
    for (int i = 0; i < final_states; i++)
    {
        int temp = 0;
        std::cin >> temp;
        new_automata.final_states.insert({temp,new_automata.states[temp]});
    }
    for (int i = 0; i < 2*number_of_states; i++)
    {
        int x, y, t;
        std::cin >> x;
        std::cin >> t;
        std::cin >> y;
        new_automata.connect_states(x,y,char(t + 'a'));

    }
    new_automata.Brzozowski();
    
}