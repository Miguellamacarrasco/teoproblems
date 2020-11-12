#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <set>
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
struct meta_node
{
    int key;
    std::set<node<vocabulary>*> identity;
    std::unordered_map<vocabulary,std::set<node<vocabulary>*>> adjacent;
    std::unordered_map<vocabulary,int> adjacent_key;
};

template<typename vocabulary>
struct automata
{
    node<vocabulary>* initial_state;
    std::unordered_map<int, node<vocabulary>*> final_states;
    std::unordered_map<int, node<vocabulary>*> states;
    std::vector<vocabulary> possible_inputs = {'a','b','e'};

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
        for (auto & state : states)
        {
            int i = 0;
            for (auto & things : state.second->adjacent) 
            {
                if (things.second == states[key])
                {
                    state.second->adjacent.erase(state.second->adjacent.begin() + i);
                }
                else
                {
                    i++;
                }
                
            }
        }
        if (initial_state == states[key]) 
        {
            initial_state = nullptr;
        }
        states.erase(key); 
        final_states.erase(key);
    }

    node<vocabulary>* operator[](int key) 
    {
        return states[key];
    }

    void nfa_to_dfa(std::vector<vocabulary> possible)
    {

        std::cout << '\n';
        std::vector<meta_node<vocabulary>*> tabla;
        std::vector<meta_node<vocabulary>*> needs_to_be_declared;
        meta_node<vocabulary>* zero_meta = new meta_node<vocabulary>;
        zero_meta->identity.insert(initial_state);
        zero_meta->key = 0;
        for (auto change : possible)
        {
            std::set<node<vocabulary>*> vector_of_change;
            for (auto node : states[-1]->adjacent)
            {
                if (node.first == change) //This is bad code
                {
                    vector_of_change.insert(node.second);
                }
            }
            zero_meta->adjacent.insert({change,vector_of_change});
        }
        
        needs_to_be_declared.push_back(zero_meta);
        int new_key = 1;
        while (!needs_to_be_declared.empty())
        {
            meta_node<vocabulary>* meta = needs_to_be_declared.front();
            //Search Adjacent
            for (auto possible_change : possible)
            {
                bool needs_to_be_declared_bool = true;
                for (auto identity_elements : meta->identity)
                {
                    
                    for (auto elments_adjacent : identity_elements->adjacent) //Search possible coincidences
                    {
                        if (elments_adjacent.first == possible_change)
                        {
                            meta->adjacent[possible_change].insert(elments_adjacent.second);
                        }
                    }
                }



                //Look of its adjacent needs to be declared
                    for (auto meta_in_table : tabla)
                    {
                        if (meta_in_table->identity == meta->adjacent[possible_change])
                        {
                            needs_to_be_declared_bool = false;
                        }
                    }
                    //Look if its already been added to the Needs_to_be_declared
                    for (auto meta_in_needs_to_be_declared : needs_to_be_declared)
                    {
                        if (meta_in_needs_to_be_declared->identity == meta->adjacent[possible_change])
                        {
                            needs_to_be_declared_bool = false;
                        }
                    }

                    //Adds it to the list of things that need declaration
                    if (needs_to_be_declared_bool)
                    {
                        meta_node<vocabulary>* new_declaration = new meta_node<vocabulary>;
                        new_declaration->identity =  meta->adjacent[possible_change];
                        new_declaration->key = new_key;
                        new_key++;
                        needs_to_be_declared.push_back(new_declaration);
                    }

            }
            
            tabla.push_back(meta);
            needs_to_be_declared.erase(needs_to_be_declared.begin());
        }
        //So now I need to convert the meta nodes to normal nodes
        std::unordered_map<int,node<vocabulary>*> new_nodos;
        std::unordered_map<int,node<vocabulary>*> new_finales;
        node<vocabulary>* new_inicial;
        for (auto meta_nodo : tabla)
        {
            node<vocabulary>* nuevo_nodo_normal = new node<vocabulary>;
            nuevo_nodo_normal->key = meta_nodo->key;
            for (auto nodos_finales : final_states)
            {
                if (std::find(meta_nodo->identity.begin(), meta_nodo->identity.end(), nodos_finales.second) != meta_nodo->identity.end())
                {
                    new_finales.insert({nuevo_nodo_normal->key, nuevo_nodo_normal});
                }
            }
            new_nodos.insert({nuevo_nodo_normal->key, nuevo_nodo_normal});
        }

        for (auto meta_nodo : tabla)
        {
            for (auto adj : possible)
            {
                for (auto nodos : tabla)
                {
                    if (nodos->identity == meta_nodo->adjacent[adj])
                    {
                        new_nodos[meta_nodo->key]->adjacent.push_back({adj,new_nodos[nodos->key]});
                    }
                }
            }
            
        }
        states = new_nodos;
        final_states  = new_finales;
        for (auto adj : new_nodos[0]->adjacent)
        {
            if (adj.first == 'e')
            {
                initial_state = adj.second;
            }
        }

        

        //Finally delete the new zero state and the void state
        remove_state(0);
        remove_state(1);
    }
    void Brzozowski()
    {
        print();
        std::cout << "Original" << '\n';
        invert();
        print();
        std::cout << "Inverted" << '\n';
        add_state(-1);
        for (auto final : final_states)
        {
            connect_states(-1,final.second->key,'e');
        }
        final_states.clear();
        final_states.insert({initial_state->key,initial_state});
        initial_state = states[-1];
         
        print();
        std::cout << "Added extra new state" << '\n';
        nfa_to_dfa(possible_inputs);
        
        print();
        std::cout << "nfa_to_dfa" << '\n';
        invert();
        print();
        std::cout << "Inverted" << '\n';
        add_state(-1);
        for (auto final : final_states)
        {
            connect_states(-1,final.second->key,'e');
        }
        final_states.clear();
        final_states.insert({initial_state->key,initial_state});
        initial_state = states[-1];
        print();
        std::cout << "Added extra new state" << '\n';
        nfa_to_dfa(possible_inputs);
        print();
        std::cout << "Final result" << '\n';
    }
    void invert()
    {
        std::unordered_map<int, std::vector<std::pair<vocabulary,node<vocabulary>*>>> temp_states; 
        for (auto vector_data: states)
        {
            std::vector<std::pair<vocabulary,node<vocabulary>*>> new_vector;
            temp_states.insert({vector_data.second->key,new_vector});
        }
        for (auto estado : states)
        {
            for (auto adj : estado.second->adjacent)
            {
                temp_states[adj.second->key].push_back({adj.first,estado.second}); 
            }
        }
        for (auto state: states)
        {
            state.second->adjacent = temp_states[state.second->key];
        }

    }

    void print()
    {
        for (auto estados : states)
        {
            if (final_states.find(estados.second->key) != states.end())
            {
                std::cout << "*";
            }
            if (initial_state == estados.second)
            {
                std::cout << "->";
            }
            std::cout << estados.second->key << " ";
            std::cout << "{";
            for (auto adj : estados.second->adjacent)
            {
                std::cout << adj.second->key << " " << adj.first << ", ";
            }
            std::cout << "} ";
        }
    }

};

#endif