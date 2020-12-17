#include <iostream>
#include <vector>

template<typename T>
void print(std::vector<std::vector<T>> input)
{
    for (auto first : input)
    {
        for (auto second : first)
        {
            std::cout << second << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <typename T>
class node
{
    public:
    std::vector<std::pair<T, T>> connects_into;
    void push(T incoming, T connection)
    {
        connects_into.push_back(std::pair<T,T>(incoming, connection));
    }

};


void dfs (std::vector<std::vector<int>> tabla, int i, int l, std::vector<std::vector<std::string>> tabla_de_equivalencia, std::vector<node<int>*> mapa_de_nodos)
{
    for (auto things : mapa_de_nodos[l]->connects_into)
    {
        for (int x = 0; x < tabla[0].size(); x++)
        if (x > things.second)
        {
            tabla_de_equivalencia[x-1][things.second] = "x";
            dfs(tabla, x, things.second, tabla_de_equivalencia, mapa_de_nodos);
        }
        else
        {
            tabla_de_equivalencia[things.second-1][x] = "x";
            dfs(tabla, things.second, x, tabla_de_equivalencia, mapa_de_nodos);
        }
        
        
    }
}



int main()
{
    int n_states, inicio, n_finales, input;
    std::vector<int> finales;
    
    std::cin >> n_states;
    std::cin >> inicio;
    std::cin >> n_finales;
    for (int l = 0; l < n_finales; l++)
    {
        std::cin >> input;
        finales.push_back(input);
    }
    std::vector<std::vector<int>> tabla (2,std::vector<int>(n_states,-2));
    int recorrer = 2*n_states;
    int m = 0;
    for (int l = 0; l<recorrer; l++)
    {
        int estado_de_entrada, transicion, estado_de_salida;
        //Switch may be more efficient but who cares
        if (m == 0)
        {
            std::cin >> estado_de_entrada;
            m++;
        }
        if (m == 1)
        {
            std::cin >> transicion;
            m++;
        }
        if (m == 2)
        {
            std::cin >> estado_de_salida;
            tabla[transicion][estado_de_entrada] = estado_de_salida;
            m = 0;
        }
    }

    std::vector<node<int>*> mapa_de_nodos;
    std::vector<std::vector<std::string>> tabla_de_equivalencia;
    for (int i = 0; i < tabla.size(); i++)
    {
        mapa_de_nodos.push_back(new node<int>);
    }
    m = 1;
    for (int i = 0; i < tabla.size(); i++)
    {
        tabla_de_equivalencia.push_back(std::vector<std::string>());
        for (int l= 0; l < tabla[i].size(); l++)
        {
            mapa_de_nodos[tabla[i][l]]->push(i, l);
        }
        for (int k = 0; k < m; k++)
        {
            tabla_de_equivalencia[i].push_back("?");
            for (auto f : finales)
            {
                if (f == i + 1 || f == k )
                {
                    tabla_de_equivalencia[i][k] = "0";
                }
            }
        }
        for (auto n : finales)
        {
            for (auto l : finales)
            {
                if (n != l)
                {
                    if (n>l)
                    {
                        tabla_de_equivalencia[n-1][l] = "?";
                    }
                    else
                    {
                        tabla_de_equivalencia[l-1][n] = "?";
                    }
                    
                }
            }
        }
        m++;
    }
    for (int f = 0; f < n_states; f++)
    {
        for (int l = 0; l < tabla_de_equivalencia[f].size(); l++)
        {
            if (tabla_de_equivalencia[f][l] == "0")
            {
                std::cout << f << " " << l;
                dfs(tabla, f,l, tabla_de_equivalencia, mapa_de_nodos);
            }   
            
        }
    }
    print(tabla_de_equivalencia);

    

    
}