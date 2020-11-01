#include <iostream>
#include <vector>
#ifndef head
#define head


template<typename T>
class node
{
    T data;
    std::vector<std::pair<int w, node*>> adjacent;
    node() {}
    node(T n_data) {data = n_data;}    
};

template<typename T>
class automata
{
    node* initial_state;
    std::<node*> final_states;
    std::vector<node*> states;

    void add_state(T data)
    {
        node<T>* n_node = new node<T>(data);
        states.push_back(n_node);
    }
    void connect_states()
    {

    }
};

#endif