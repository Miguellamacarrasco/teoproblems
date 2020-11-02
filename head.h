#include <iostream>
#include <vector>
#include <unordered_map>
#ifndef head
#define head

//Becouse of the exersize type comments assume vocabulary = bool for complexity


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
    
    void remove_state(int key) //O(4n)
    {
        for (auto & state : states) //O(n)
        {
            int i = 0;
            for (auto & things : state.second->adjacent) //O(2)
            {
                if (things.second == states[key]) //O(1)
                {
                    state.second->adjacent.erase(state.second->adjacent.begin() + i);
                }
            }
        }
        if (initial_state == states[key]) //O(1)
        {
            initial_state = nullptr;
        }
        states.erase(key); //O(n)
        final_states.erase(key); //O(n)
    }

    node<vocabulary>* operator[](int key) //O(1)
    {
        return states[key];
    }

    void Brzozowski()
    {
        //Identify nodes that are unreachable from the intial state and delete them 
        std::vector<node<vocabulary>*> to_visit;
        std::unordered_map<int,bool> found;
        for (auto state : states) //O(n)
        {
            found.insert({state.second->key,false});
        }
        to_visit.push_back(initial_state);
        while (!to_visit.empty()) //O(n)
        {
            for (auto adjacent : to_visit[0]->adjacent) //O(2) 
            {
                if (!found[adjacent.second->key]) //O(1)
                {
                    to_visit.push_back(adjacent.second);
                    found[adjacent.second->key] = true;
                }
            }
            to_visit.erase(to_visit.begin());
        }
        for (auto estado : found)  //O(n) 
        {
            if (!estado.second)
            {
                //This state is unacessible, therefore it should be deleted 
                remove_state(estado.first); //O(4n)
            }
        }
        //Complexity so far O(n + 2n + 4n^2)
        
    
    }


};

#endif