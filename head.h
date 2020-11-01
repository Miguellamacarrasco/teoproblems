#include <iostream>
#include <vector>
#include <unordered_map>
#ifndef head
#define head


template<typename vocabulary>
struct node
{
    int key;
    std::vector<std::pair<vocabulary, node<vocabulary>*>> adjacent;
    node() {}
    node(int n_key) {key = n_key;}    
};

template<typename vocabulary>
struct automata
{
    node<vocabulary>* initial_state;
    std::unordered_map<int, node<vocabulary>*> final_states;
    std::unordered_map<int, node<vocabulary>*> states;

    void add_state(int key)
    {
        node<vocabulary>* n_node = new node<vocabulary>(key);
        states.insert({key, n_node});
    }

    void connect_states(int key1, int key2, vocabulary t_input)
    {
        states[key1]->adjacent.push_back(std::pair<vocabulary,node<vocabulary>*>(t_input,states[key2]));
    }
    
    void remove_state(int key)
    {
    
    }
};

#endif