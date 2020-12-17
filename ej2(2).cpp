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

std::string discover(std::vector<std::vector<int>> & tabla, std::vector<std::vector<std::string>> & tabla_de_equivalencias, int A, int B)
{
   
   print(tabla_de_equivalencias);
   
   if (A == B)
   {
       return "1";
   }        
   if (A > B)
   {
        //A -= 1;
        
        if (tabla_de_equivalencias[A-1][B] == "0" || tabla_de_equivalencias[A-1][B] == "1")
        {
            return tabla_de_equivalencias[A-1][B];
        }
        tabla_de_equivalencias[A-1][B] = "1";
        if (discover(tabla, tabla_de_equivalencias, tabla[0][A], tabla[0][B]) == "0")
        {  
            tabla_de_equivalencias[A-1][B] = "0";
            return "0";
        }
        
         
        if (discover(tabla, tabla_de_equivalencias, tabla[1][A], tabla[1][B]) == "0")
        {
            tabla_de_equivalencias[A-1][B] = "0";
            return "0";
        }
        tabla_de_equivalencias[A-1][B] = "1";
        return "1";
   }
   else
   {
        //B -= 1;
        if (tabla_de_equivalencias[B-1][A] == "0" || tabla_de_equivalencias[B-1][A] == "1")
        {
            return tabla_de_equivalencias[B-1][A];
        }
        tabla_de_equivalencias[B-1][A] = "1";
        if (discover(tabla, tabla_de_equivalencias, tabla[0][A], tabla[0][B]) == "0")
        {
            tabla_de_equivalencias[B-1][A] = "0";
            return "0";
        }
        if (discover(tabla, tabla_de_equivalencias, tabla[1][A], tabla[1][B]) == "0")
        {
            tabla_de_equivalencias[B-1][A] = "0";
            return "0";
        }
        tabla_de_equivalencias[B-1][B] = "1";
        return "1";
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
    std::vector<std::vector<std::string>> tabla_de_equivalencias;
        
    int l = 1;
    for (int i = 0; i < n_states - 1; i++)
    {
        tabla_de_equivalencias.push_back(std::vector<std::string>());
        for (int m = 0; m < l; m++)
        {   
            tabla_de_equivalencias[i].push_back("?");    
            for (auto f : finales)
            {
                if (f == i+1 || f == m)
                {
                    tabla_de_equivalencias[i][m] = "0";
                }
            }     
        }
        l++;
    }
    for (auto n : finales)
    {
        for (auto l : finales)
        {
            if (n != l)
            {
                if (n > l)
                {
                    tabla_de_equivalencias[n-1][l] = "?";
                }
                else
                {
                    tabla_de_equivalencias[l-1][n] = "?";
                }
                
            }
        }
    }
    for (int f = 0; f < n_states; f++)
    {
        for (int l = 0; l < tabla_de_equivalencias[f].size(); l++)
        {
            auto same = tabla_de_equivalencias;
            discover(tabla, tabla_de_equivalencias, f+1,l);
        }
    }
    

}